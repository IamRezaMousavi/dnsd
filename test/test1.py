from scapy.layers.dns import DNS, DNSQR
from scapy.layers.inet import IP, UDP
from scapy.sendrecv import sr1

dnsq1 = DNSQR(qname="cloud99p.org", qtype="A")
dnsq2 = DNSQR(qname="cloud99p.org", qtype="NS")

# p = IP(dst='localhost') / UDP(dport=8080) / DNS(rd=1, qd=[dnsq1, dnsq2])
# p = IP(dst='37.152.177.218') / UDP() / DNS(rd=1, qd=[dnsq1, dnsq2])
p = IP(dst="37.152.177.218") / UDP() / DNS(rd=1, qd=dnsq1)
res = sr1(p)

res.summary()
print(res)
