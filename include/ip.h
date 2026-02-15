#ifndef IP_H
#define IP_H

#include <stdint.h>

// IP Protocol numbers
#define IPPROTO_ICMP 1
#define IPPROTO_TCP 6
#define IPPROTO_UDP 17

// IP Header structure (20 bytes minimum)
struct iphdr {
    uint8_t version_ihl; // Version (4 bits) + IHL (4 bits)
    uint8_t tos;         // Type of service
    uint16_t tot_len;    // Total length
    uint16_t id;         // Identification
    uint16_t frag_off;   // Fragment offset
    uint8_t ttl;         // Time to live
    uint8_t protocol;    // Protocol
    uint16_t check;      // Header checksum
    uint32_t saddr;      // Source address
    uint32_t daddr;      // Destination address
} __attribute__((packed));

// Helper macros
#define IP_VERSION(iph) ((iph)->version_ihl >> 4)
#define IP_IHL(iph) ((iph)->version_ihl & 0x0F)
#define IP_HDRLEN(iph) (IP_IHL(iph) * 4)

#endif // IP_H
