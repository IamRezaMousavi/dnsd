#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <map>
#include <optional>
#include <string>
#include <vector>

class Config {
public:
  Config(std::string filename);

private:
  struct DNSRecord {
    std::optional<int> ttl;
    std::string        recordclass;
    std::string        type;
    std::string        value;
  };

  std::map<std::string, std::vector<DNSRecord>> records;
};

#endif /* __CONFIG_HPP__ */
