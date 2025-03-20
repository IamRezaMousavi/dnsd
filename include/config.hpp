#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

class Config {
private:
  struct DNSRecord {
    std::optional<int> ttl;
    std::string recordclass;
    std::string type;
    std::string value;
  };
  std::map<std::string, std::vector<DNSRecord>> records;

public:
  Config(std::string filename);
};

inline std::string removeComment(const std::string &line) {
  size_t pos = line.find(';');
  return (pos != std::string::npos) ? line.substr(0, pos) : line;
}

Config::Config(std::string filename) {
  std::string line;
  std::ifstream configFile(filename);

  while (std::getline(configFile, line)) {
    line = removeComment(line);
    std::stringstream ss(line);
    std::string domain;
    DNSRecord dnsrecord;

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

#endif /* __CONFIG_HPP__ */
