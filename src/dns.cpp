#include "dns.hpp"

#include <iomanip>
#include <netinet/in.h>
#include <sstream>

inline std::string to_string(int value, std::unordered_map<int, std::string> values) {
  auto it = values.find(value);
  if (it != values.end()) {
    return it->second;
  }
  return "UNKNOWN";
}

DNS::DNS() {}

DNS::DNS(const uint8_t *data) {
  parseDNS(data);
}

void DNS::parseDNS(const uint8_t *data) {
  int offset = 0;

  const DNSHeader *dnsHeader = (DNSHeader *)data;
  this->header.transactionId = ntohs(dnsHeader->transactionId);
  this->header.flags         = ntohs(dnsHeader->flags);
  this->header.qdcount       = ntohs(dnsHeader->qdcount);
  this->header.ancount       = ntohs(dnsHeader->ancount);
  this->header.nscount       = ntohs(dnsHeader->nscount);
  this->header.arcount       = ntohs(dnsHeader->arcount);

  offset += sizeof(DNSHeader);
  for (int i = 0; i < header.qdcount; ++i) {
    queries.push_back(parseDNSQuery(data, offset));
  }
}

std::vector<uint8_t> DNS::buildDNSResponse() {
  std::vector<uint8_t> response;

  std::string rdata = "ns1.cloud99p.org";
  appendDNSName(response, "ns1.cloud99p.org");

  answers.push_back(
      {.name = queries.front().name, .type = T_NS, .qclass = C_IN, .ttl = 86400, .rdlength = (uint16_t)response.size(), .rdata = response}
  );

  response.clear();

  DNSHeader responseHeader;
  responseHeader.transactionId = htons(header.transactionId);
  // responseHeader.flags         = htons(0x8500); // Standard response, no error
  responseHeader.flags |= F_RESPONSE;
  responseHeader.flags |= F_AUTHORITATIVE;
  responseHeader.flags |= F_RECDESIRED;
  responseHeader.flags = htons(responseHeader.flags);

  responseHeader.qdcount = htons(header.qdcount);
  responseHeader.ancount = htons(answers.size());
  responseHeader.nscount = htons(0);
  responseHeader.arcount = htons(0);

  uint8_t *headerPtr = (uint8_t *)&responseHeader;
  response.insert(response.end(), headerPtr, headerPtr + sizeof(DNSHeader));

  for (const auto &query : queries) {
    appendDNSQuery(response, query);
  }

  for (const auto &answer : answers) {
    appendDNSAnswer(response, answer);
  }

  return response;
}

std::string DNS::parseDNSQueryName(const uint8_t *data, int &offset) {
  std::ostringstream name;
  while (data[offset] != 0) {
    int length = data[offset];
    offset++;
    if (!name.str().empty()) {
      name << ".";
    }
    name.write((const char *)(&data[offset]), length);
    offset += length;
  }
  offset++; // skip the null terminator
  return name.str();
}

DNSQuery DNS::parseDNSQuery(const uint8_t *data, int &offset) {
  DNSQuery query;
  query.name = parseDNSQueryName(data, offset);
  query.type = ntohs(*(uint16_t *)(data + offset));
  offset += 2;
  query.qclass = ntohs(*(uint16_t *)(data + offset));
  offset += 2;
  return query;
}

DNSAnswer DNS::parseDNSAnswer(const uint8_t *data, int &offset) {
  DNSAnswer answer;
  answer.name = parseDNSQueryName(data, offset);
  answer.type = ntohs(*(uint16_t *)(data + offset));
  offset += 2;
  answer.qclass = ntohs(*(uint16_t *)(data + offset));
  offset += 2;
  answer.ttl = ntohl(*(uint32_t *)(data + offset));
  offset += 4;
  answer.rdlength = ntohs(*(uint16_t *)(data + offset));
  offset += 2;
  answer.rdata.insert(answer.rdata.end(), data + offset, data + offset + answer.rdlength);
  offset += answer.rdlength;
  return answer;
}

void DNS::appendDNSQuery(std::vector<uint8_t> &response, const DNSQuery &query) {
  appendDNSName(response, query.name);
  appendUint16(response, query.type);
  appendUint16(response, query.qclass);
}

void DNS::appendDNSAnswer(std::vector<uint8_t> &response, const DNSAnswer &answer) {
  appendDNSName(response, answer.name);
  appendUint16(response, answer.type);
  appendUint16(response, answer.qclass);
  appendUint32(response, answer.ttl);
  appendUint16(response, answer.rdlength);
  response.insert(response.end(), answer.rdata.begin(), answer.rdata.end());
}

void DNS::appendDNSName(std::vector<uint8_t> &response, const std::string &name) {
  std::istringstream iss(name);
  std::string        part;
  while (std::getline(iss, part, '.')) {
    response.push_back(part.length());
    response.insert(response.end(), part.begin(), part.end());
  }
  response.push_back('\0');
}

void DNS::appendUint16(std::vector<uint8_t> &response, uint16_t value) {
  value        = htons(value);
  uint8_t *ptr = (uint8_t *)&value;
  response.insert(response.end(), ptr, ptr + 2);
}

void DNS::appendUint32(std::vector<uint8_t> &response, uint32_t value) {
  value        = htonl(value);
  uint8_t *ptr = (uint8_t *)&value;
  response.insert(response.end(), ptr, ptr + 4);
}

std::ostream &operator<<(std::ostream &os, const DNSQuery &query) {
  os << "+------------------+-------------------+" << std::endl;
  os << "|       Query Name | " << query.name << std::endl;
  os << "|       Query Type | " << std::left << std::setw(17) << to_string(query.type, dns_type_vals) << " |" << std::endl;
  os << "|      Query Class | " << std::left << std::setw(17) << to_string(query.qclass, dns_class_vals) << " |" << std::endl;
  os << "+------------------+-------------------+" << std::endl;
  return os;
}

std::ostream &operator<<(std::ostream &os, const DNS &packet) {
  os << "|                 DNS                  |" << std::endl;
  os << "+------------------+-------------------+" << std::endl;
  os << "|   Transaction ID | 0x" << std::left << std::setw(15) << std::hex << packet.header.transactionId << std::dec << " |" << std::endl;
  os << "|            Flags | 0x" << std::left << std::setw(15) << std::hex << packet.header.flags << std::dec << " |" << std::endl;
  os << "|        Questions | " << std::left << std::setw(17) << packet.header.qdcount << " |" << std::endl;
  os << "|       Answer PRs | " << std::left << std::setw(17) << packet.header.ancount << " |" << std::endl;
  os << "|    Authority PRs | " << std::left << std::setw(17) << packet.header.nscount << " |" << std::endl;
  os << "|   Additional PRs | " << std::left << std::setw(17) << packet.header.arcount << " |" << std::endl;
  os << "+------------------+-------------------+" << std::endl;
  os << "|               Queries                |" << std::endl;
  for (const auto &query : packet.queries) {
    os << query;
  }

  return os;
}
