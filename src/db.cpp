#include "db.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "logger.hpp"

DB &DB::getInstance(std::string filename) {
  static DB instance(filename);
  return instance;
}

std::optional<DB::DNSRecord> DB::get(DNSQuery dnsquery) {
  auto it = records.find(dnsquery.name);
  if (it != records.end()) {
    auto values = it->second;
    for (auto &v : values)
      if (v.type == to_string(dnsquery.type, dns_type_vals) && v.recordclass == to_string(dnsquery.qclass, dns_class_vals))
        return v;

    return std::nullopt;
  }
  return std::nullopt;
}

inline std::string removeComment(const std::string &line) {
  size_t pos = line.find(';');
  return (pos != std::string::npos) ? line.substr(0, pos) : line;
}

DB::DB(std::string filename) {
  Logger &logger = Logger::getInstance();

  std::string   line;
  std::ifstream configFile(filename);

  if (!configFile.is_open()) {
    logger.error("Cann't reading config file: " + std::string(strerror(errno)));
    exit(EXIT_FAILURE);
  }

  while (std::getline(configFile, line)) {
    line = removeComment(line);
    std::stringstream ss(line);
    std::string       domain;
    DNSRecord         dnsrecord;

    if (!(ss >> domain))
      continue;

    int tempTTL;
    if (ss >> tempTTL) {
      dnsrecord.ttl = tempTTL;
    } else {
      ss.clear();
    }

    if (!(ss >> dnsrecord.recordclass >> dnsrecord.type >> dnsrecord.value))
      continue;

    records[domain].push_back(dnsrecord);
  }

  //   for (const auto &[domain, record] : records) {
  //     std::cout << "Domain: " << domain << std::endl;
  //     for (const auto &r : record) {
  //       std::cout << "    TTL: " << (r.ttl ? std::to_string(*r.ttl) : "N/A")
  //                 << std::endl
  //                 << "  Class: " << r.recordclass << std::endl
  //                 << "   Type: " << r.type << std::endl
  //                 << "  Value: " << r.value << std::endl;
  //     }
  //   }

  configFile.close();
}
