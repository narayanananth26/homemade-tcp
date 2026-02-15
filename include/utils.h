#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stddef.h>

// Print hex dump of buffer
void hex_dump(const void *data, size_t size);

// Convert IP address from uint32_t to string (e.g., "192.168.1.1")
void ip_to_str(uint32_t ip, char *buf);

// Convert IP address from string to uint32_t
uint32_t str_to_ip(const char *ip_str);

// Network to host byte order conversions
// (macOS provides ntohs, ntohl, htons, htonl, but you can wrap them)

#endif // UTILS_H
