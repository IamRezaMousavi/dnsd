#ifndef __DB_HPP__
#define __DB_HPP__

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "dns.hpp"

class DB {
public:
  struct DNSRecord {
    std::optional<uint32_t> ttl;
    std::string             recordclass;
    std::string             type;
    std::string             value;
  };

  static DB               &getInstance(std::string filename);
  std::optional<DNSRecord> get(DNSQuery dnsquery);

private:
  std::map<std::string, std::vector<DNSRecord>> records;

  DB(std::string filename);
  DB(const DB &)            = delete;
  DB &operator=(const DB &) = delete;
};

#endif /* __DB_HPP__ */
