#include "utils.h"
#include <stdio.h>
#include <arpa/inet.h>

void hex_dump(const void *data, size_t size) {
    const unsigned char *buf = (const unsigned char *)data;
    for (size_t i = 0; i < size; i++) {
        printf("%02x ", buf[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    if (size % 16 != 0) printf("\n");
}

void ip_to_str(uint32_t ip, char *buf) {
    unsigned char *bytes = (unsigned char *)&ip;
    sprintf(buf, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
}

uint32_t str_to_ip(const char *ip_str) {
    struct in_addr addr;
    inet_aton(ip_str, &addr);
    return addr.s_addr;
}
