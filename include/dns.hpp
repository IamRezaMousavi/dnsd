#ifndef __DNS_HPP__
#define __DNS_HPP__

#include <cinttypes>
#include <string>
#include <unordered_map>
#include <vector>

/* type values  */
#define T_A          1     /* host address */
#define T_NS         2     /* authoritative name server */
#define T_MD         3     /* mail destination (obsolete) */
#define T_MF         4     /* mail forwarder (obsolete) */
#define T_CNAME      5     /* canonical name */
#define T_SOA        6     /* start of authority zone */
#define T_MB         7     /* mailbox domain name (experimental) */
#define T_MG         8     /* mail group member (experimental) */
#define T_MR         9     /* mail rename domain name (experimental) */
#define T_NULL       10    /* null RR (experimental) */
#define T_WKS        11    /* well known service */
#define T_PTR        12    /* domain name pointer */
#define T_HINFO      13    /* host information */
#define T_MINFO      14    /* mailbox or mail list information */
#define T_MX         15    /* mail routing information */
#define T_TXT        16    /* text strings */
#define T_RP         17    /* responsible person (RFC 1183) */
#define T_AFSDB      18    /* AFS data base location (RFC 1183) */
#define T_X25        19    /* X.25 address (RFC 1183) */
#define T_ISDN       20    /* ISDN address (RFC 1183) */
#define T_RT         21    /* route-through (RFC 1183) */
#define T_NSAP       22    /* OSI NSAP (RFC 1706) */
#define T_NSAP_PTR   23    /* PTR equivalent for OSI NSAP (RFC 1348 - obsolete) */
#define T_SIG        24    /* digital signature (RFC 2535) */
#define T_KEY        25    /* public key (RFC 2535) */
#define T_PX         26    /* pointer to X.400/RFC822 mapping info (RFC 1664) */
#define T_GPOS       27    /* geographical position (RFC 1712) */
#define T_AAAA       28    /* IPv6 address (RFC 1886) */
#define T_LOC        29    /* geographical location (RFC 1876) */
#define T_NXT        30    /* "next" name (RFC 2535) */
#define T_EID        31    /* Endpoint Identifier */
#define T_NIMLOC     32    /* Nimrod Locator */
#define T_SRV        33    /* service location (RFC 2052) */
#define T_ATMA       34    /* ATM Address */
#define T_NAPTR      35    /* naming authority pointer (RFC 3403) */
#define T_KX         36    /* Key Exchange (RFC 2230) */
#define T_CERT       37    /* Certificate (RFC 4398) */
#define T_A6         38    /* IPv6 address with indirection (RFC 2874 - obsolete) */
#define T_DNAME      39    /* Non-terminal DNS name redirection (RFC 2672) */
#define T_SINK       40    /* SINK */
#define T_OPT        41    /* OPT pseudo-RR (RFC 2671) */
#define T_APL        42    /* Lists of Address Prefixes (APL RR) (RFC 3123) */
#define T_DS         43    /* Delegation Signer (RFC 4034) */
#define T_SSHFP      44    /* Using DNS to Securely Publish SSH Key Fingerprints (RFC 4255) */
#define T_IPSECKEY   45    /* RFC 4025 */
#define T_RRSIG      46    /* RFC 4034 */
#define T_NSEC       47    /* RFC 4034 */
#define T_DNSKEY     48    /* RFC 4034 */
#define T_DHCID      49    /* DHCID RR (RFC 4701) */
#define T_NSEC3      50    /* Next secure hash (RFC 5155) */
#define T_NSEC3PARAM 51    /* NSEC3 parameters (RFC 5155) */
#define T_TLSA       52    /* TLSA (RFC 6698) */
#define T_HIP        55    /* Host Identity Protocol (HIP) RR (RFC 5205) */
#define T_NINFO      56    /* NINFO */
#define T_RKEY       57    /* RKEY */
#define T_TALINK     58    /* Trust Anchor LINK */
#define T_CDS        59    /* Child DS (RFC7344)*/
#define T_CDNSKEY    60    /* DNSKEY(s) the Child wants reflected in DS ( [RFC7344])*/
#define T_OPENPGPKEY 61    /* OPENPGPKEY draft-ietf-dane-openpgpkey-00 */
#define T_CSYNC      62    /* Child To Parent Synchronization (RFC7477) */
#define T_ZONEMD     63    /* Message Digest for DNS Zones (RFC8976) */
#define T_SVCB       64    /* draft-ietf-dnsop-svcb-https-01 */
#define T_HTTPS      65    /* draft-ietf-dnsop-svcb-https-01 */
#define T_SPF        99    /* SPF RR (RFC 4408) section 3 */
#define T_UINFO      100   /* [IANA-Reserved] */
#define T_UID        101   /* [IANA-Reserved] */
#define T_GID        102   /* [IANA-Reserved] */
#define T_UNSPEC     103   /* [IANA-Reserved] */
#define T_NID        104   /* ILNP [RFC6742] */
#define T_L32        105   /* ILNP [RFC6742] */
#define T_L64        106   /* ILNP [RFC6742] */
#define T_LP         107   /* ILNP [RFC6742] */
#define T_EUI48      108   /* EUI 48 Address (RFC7043) */
#define T_EUI64      109   /* EUI 64 Address (RFC7043) */
#define T_TKEY       249   /* Transaction Key (RFC 2930) */
#define T_TSIG       250   /* Transaction Signature (RFC 2845) */
#define T_IXFR       251   /* incremental transfer (RFC 1995) */
#define T_AXFR       252   /* transfer of an entire zone (RFC 5936) */
#define T_MAILB      253   /* mailbox-related RRs (MB, MG or MR) (RFC 1035) */
#define T_MAILA      254   /* mail agent RRs (OBSOLETE - see MX) (RFC 1035) */
#define T_ANY        255   /* A request for all records (RFC 1035) */
#define T_URI        256   /* URI */
#define T_CAA        257   /* Certification Authority Authorization (RFC 6844) */
#define T_AVC        258   /* Application Visibility and Control (Wolfgang_Riedel) */
#define T_DOA        259   /* Digital Object Architecture (draft-durand-doa-over-dns) */
#define T_AMTRELAY   260   /* Automatic Multicast Tunneling Relay (RFC8777) */
#define T_RESINFO    261   /* Resolver Information */
#define T_WALLET     262   /* Public wallet address */
#define T_TA         32768 /* DNSSEC Trust Authorities */
#define T_DLV        32769 /* DNSSEC Lookaside Validation (DLV) DNS Resource Record (RFC 4431) */
#define T_WINS       65281 /* Microsoft's WINS RR */
#define T_WINS_R     65282 /* Microsoft's WINS-R RR */
#define T_XPF        65422 /* XPF draft-bellis-dnsop-xpf */

const std::unordered_map<int, std::string> dns_type_vals = {
    {0,            "Unused"    },
    {T_A,          "A"         },
    {T_NS,         "NS"        },
    {T_MD,         "MD"        },
    {T_MF,         "MF"        },
    {T_CNAME,      "CNAME"     },
    {T_SOA,        "SOA"       },
    {T_MB,         "MB"        },
    {T_MG,         "MG"        },
    {T_MR,         "MR"        },
    {T_NULL,       "NULL"      },
    {T_WKS,        "WKS"       },
    {T_PTR,        "PTR"       },
    {T_HINFO,      "HINFO"     },
    {T_MINFO,      "MINFO"     },
    {T_MX,         "MX"        },
    {T_TXT,        "TXT"       },
    {T_RP,         "RP"        },
    {T_AFSDB,      "AFSDB"     },
    {T_X25,        "X25"       },
    {T_ISDN,       "ISDN"      },
    {T_RT,         "RT"        },
    {T_NSAP,       "NSAP"      },
    {T_NSAP_PTR,   "NSAP-PTR"  },
    {T_SIG,        "SIG"       },
    {T_KEY,        "KEY"       },
    {T_PX,         "PX"        },
    {T_GPOS,       "GPOS"      },
    {T_AAAA,       "AAAA"      },
    {T_LOC,        "LOC"       },
    {T_NXT,        "NXT"       },
    {T_EID,        "EID"       },
    {T_NIMLOC,     "NIMLOC"    },
    {T_SRV,        "SRV"       },
    {T_ATMA,       "ATMA"      },
    {T_NAPTR,      "NAPTR"     },
    {T_KX,         "KX"        },
    {T_CERT,       "CERT"      },
    {T_A6,         "A6"        },
    {T_DNAME,      "DNAME"     },
    {T_SINK,       "SINK"      },
    {T_OPT,        "OPT"       },
    {T_APL,        "APL"       },
    {T_DS,         "DS"        },
    {T_SSHFP,      "SSHFP"     },
    {T_IPSECKEY,   "IPSECKEY"  },
    {T_RRSIG,      "RRSIG"     },
    {T_NSEC,       "NSEC"      },
    {T_DNSKEY,     "DNSKEY"    },
    {T_DHCID,      "DHCID"     },
    {T_NSEC3,      "NSEC3"     },
    {T_NSEC3PARAM, "NSEC3PARAM"},
    {T_TLSA,       "TLSA"      },
    {T_HIP,        "HIP"       },
    {T_RKEY,       "RKEY"      },
    {T_TALINK,     "TALINK"    },
    {T_CDS,        "CDS"       },
    {T_CDNSKEY,    "CDNSKEY"   },
    {T_OPENPGPKEY, "OPENPGPKEY"},
    {T_CSYNC,      "CSYNC"     },
    {T_ZONEMD,     "ZONEMD"    },
    {T_SVCB,       "SVCB"      },
    {T_HTTPS,      "HTTPS"     },
    {T_SPF,        "SPF"       },
    {T_UINFO,      "UINFO"     },
    {T_UID,        "UID"       },
    {T_GID,        "GID"       },
    {T_UNSPEC,     "UNSPEC"    },
    {T_NID,        "NID"       },
    {T_L32,        "L32"       },
    {T_L64,        "L64"       },
    {T_LP,         "LP"        },
    {T_EUI48,      "EUI48"     },
    {T_EUI64,      "EUI64"     },
    {T_TKEY,       "TKEY"      },
    {T_TSIG,       "TSIG"      },
    {T_IXFR,       "IXFR"      },
    {T_AXFR,       "AXFR"      },
    {T_MAILB,      "MAILB"     },
    {T_MAILA,      "MAILA"     },
    {T_ANY,        "ANY"       },
    {T_URI,        "URI"       },
    {T_CAA,        "CAA"       },
    {T_AVC,        "AVC"       },
    {T_DOA,        "DOA"       },
    {T_AMTRELAY,   "AMTRELAY"  },
    {T_RESINFO,    "RESINFO"   },
    {T_WALLET,     "WALLET"    },
    {T_TA,         "TA"        },
    {T_DLV,        "DLV"       },

    {T_WINS,       "WINS"      },
    {T_WINS_R,     "WINS-R"    },
    {T_XPF,        "XPF"       },
};

/* Class values */
#define C_IN   1   /* the Internet */
#define C_CS   2   /* CSNET (obsolete) */
#define C_CH   3   /* CHAOS */
#define C_HS   4   /* Hesiod */
#define C_NONE 254 /* none */
#define C_ANY  255 /* any */

const std::unordered_map<int, std::string> dns_class_vals = {
    {C_IN,   "IN"  },
    {C_CS,   "CS"  },
    {C_CH,   "CH"  },
    {C_HS,   "HS"  },
    {C_NONE, "NONE"},
    {C_ANY,  "ANY" }
};

/* Bit fields in the flags */
#define F_RESPONSE      (1 << 15)   /* packet is response */
#define F_OPCODE        (0xF << 11) /* query opcode */
#define OPCODE_SHIFT    11
#define F_AUTHORITATIVE (1 << 10)  /* response is authoritative */
#define F_CONFLICT      (1 << 10)  /* conflict detected */
#define F_TRUNCATED     (1 << 9)   /* response is truncated */
#define F_RECDESIRED    (1 << 8)   /* recursion desired */
#define F_TENTATIVE     (1 << 8)   /* response is tentative */
#define F_RECAVAIL      (1 << 7)   /* recursion available */
#define F_Z             (1 << 6)   /* Z */
#define F_AUTHENTIC     (1 << 5)   /* authentic data (RFC2535) */
#define F_CHECKDISABLE  (1 << 4)   /* checking disabled (RFC2535) */
#define F_RCODE         (0xF << 0) /* reply code */

/* Optcode values for EDNS0 options (RFC 2671) */
#define O_LLQ               1      /* Long-lived query (on-hold, draft-sekar-dns-llq) */
#define O_UL                2      /* Update lease (on-hold, draft-sekar-dns-ul) */
#define O_NSID              3      /* Name Server Identifier (RFC 5001) */
#define O_OWNER             4      /* Owner, reserved (draft-cheshire-edns0-owner-option) */
#define O_DAU               5      /* DNSSEC Algorithm Understood (RFC6975) */
#define O_DHU               6      /* DS Hash Understood (RFC6975) */
#define O_N3U               7      /* NSEC3 Hash Understood (RFC6975) */
#define O_CLIENT_SUBNET     8      /* Client subnet as assigned by IANA */
#define O_EDNS_EXPIRE       9      /* EDNS Expire (RFC7314) */
#define O_CLIENT_SUBNET_EXP 0x50fa /* Client subnet (placeholder value, draft-vandergaast-edns-client-subnet) */
#define O_COOKIE            10     /* Cookies (RFC7873) */
#define O_EDNS_TCP_KA       11     /* edns-tcp-keepalive EDNS0 Option (RFC7828) */
#define O_PADDING           12     /* EDNS(0) Padding Option (RFC7830) */
#define O_CHAIN             13     /* draft-ietf-dnsop-edns-chain-query */
#define O_EXT_ERROR         15     /* Extended DNS Errors (RFC8914) */
#define O_REPORT_CHANNEL    18     /* DNS Error Reporting (RFC9567) */
#define O_ZONEVERSION       19     /* DNS Zone Version (ZONEVERSION) Option (RFC9660) */

/* Opcodes */
#define OPCODE_QUERY  0 /* standard query */
#define OPCODE_IQUERY 1 /* inverse query */
#define OPCODE_STATUS 2 /* server status request */
#define OPCODE_NOTIFY 4 /* zone change notification */
#define OPCODE_UPDATE 5 /* dynamic update */
#define OPCODE_DSO    6 /* DNS stateful operations */

const std::unordered_map<int, std::string> dns_opcode_vals = {
    {OPCODE_QUERY,  "Standard query"               },
    {OPCODE_IQUERY, "Inverse query"                },
    {OPCODE_STATUS, "Server status request"        },
    {OPCODE_NOTIFY, "Zone change notification"     },
    {OPCODE_UPDATE, "Dynamic update"               },
    {OPCODE_DSO,    "DNS Stateful operations (DSO)"},
};

/* Reply codes */
#define RCODE_NOERROR   0
#define RCODE_FORMERR   1
#define RCODE_SERVFAIL  2
#define RCODE_NXDOMAIN  3
#define RCODE_NOTIMPL   4
#define RCODE_REFUSED   5
#define RCODE_YXDOMAIN  6
#define RCODE_YXRRSET   7
#define RCODE_NXRRSET   8
#define RCODE_NOTAUTH   9
#define RCODE_NOTZONE   10
#define RCODE_DSOTYPENI 11

#define RCODE_BAD       16
#define RCODE_BADKEY    17
#define RCODE_BADTIME   18
#define RCODE_BADMODE   19
#define RCODE_BADNAME   20
#define RCODE_BADALG    21
#define RCODE_BADTRUNC  22
#define RCODE_BADCOOKIE 23

const std::unordered_map<int, std::string> dns_rcode_vals = {
    {RCODE_NOERROR,   "No error"                                 },
    {RCODE_FORMERR,   "Format error"                             },
    {RCODE_SERVFAIL,  "Server failure"                           },
    {RCODE_NXDOMAIN,  "No such name"                             },
    {RCODE_NOTIMPL,   "Not implemented"                          },
    {RCODE_REFUSED,   "Refused"                                  },
    {RCODE_YXDOMAIN,  "Name exists"                              },
    {RCODE_YXRRSET,   "RRset exists"                             },
    {RCODE_NXRRSET,   "RRset does not exist"                     },
    {RCODE_NOTAUTH,   "Not authoritative"                        },
    {RCODE_NOTZONE,   "Name out of zone"                         },
    {RCODE_DSOTYPENI, "DSO-Type not implemented"                 },
    /* 12-15            Unassigned */
    {RCODE_BAD,       "Bad OPT Version or TSIG Signature Failure"},
    {RCODE_BADKEY,    "Key not recognized"                       },
    {RCODE_BADTIME,   "Signature out of time window"             },
    {RCODE_BADMODE,   "Bad TKEY Mode"                            },
    {RCODE_BADNAME,   "Duplicate key name"                       },
    {RCODE_BADALG,    "Algorithm not supported"                  },
    {RCODE_BADTRUNC,  "Bad Truncation"                           },
    {RCODE_BADCOOKIE, "Bad/missing Server Cookie"                },
};

/*
                        DNS Header
                                    1  1  1  1  1  1
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      ID                       |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    QDCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ANCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    NSCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ARCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*/
struct DNSHeader {
  uint16_t transactionId;
  uint16_t flags;
  uint16_t qdcount;
  uint16_t ancount;
  uint16_t nscount;
  uint16_t arcount;
};

/*
                        DNS Query
                                    1  1  1  1  1  1
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                                               |
    /                     QNAME                     /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     QTYPE                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     QCLASS                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*/
struct DNSQuery {
  std::string name;
  uint16_t    type;
  uint16_t    qclass;
};

/*
                  DNS Resource Record
                                    1  1  1  1  1  1
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                                               |
    /                                               /
    /                      NAME                     /
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      TYPE                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     CLASS                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      TTL                      |
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                   RDLENGTH                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
    /                     RDATA                     /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*/
struct DNSAnswer {
  std::string          name;
  uint16_t             type;
  uint16_t             qclass;
  uint32_t             ttl;
  uint16_t             rdlength;
  std::vector<uint8_t> rdata;
};

class DNS {
public:
  DNS();
  DNS(const uint8_t *data);

  void                 parseDNS(const uint8_t *data);
  std::vector<uint8_t> buildDNSResponse();

  friend std::ostream &operator<<(std::ostream &os, const DNS &packet);

private:
  struct DNSHeader       header;
  std::vector<DNSQuery>  queries;
  std::vector<DNSAnswer> answers;

  std::string parseDNSQueryName(const uint8_t *data, int &offset);
  DNSQuery    parseDNSQuery(const uint8_t *data, int &offset);
  DNSAnswer   parseDNSAnswer(const uint8_t *data, int &offset);

  void appendDNSQuery(std::vector<uint8_t> &response, const DNSQuery &query);
  void appendDNSAnswer(std::vector<uint8_t> &response, const DNSAnswer &answer);
  void appendDNSName(std::vector<uint8_t> &response, const std::string &name);
  void appendUint16(std::vector<uint8_t> &response, uint16_t value);
  void appendUint32(std::vector<uint8_t> &response, uint32_t value);
};

#endif /* __DNS_HPP__ */
