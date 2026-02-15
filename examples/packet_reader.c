#include "ip.h"
#include "tun.h"
#include "utils.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 2048

int main(int argc, char *argv[]) {
    // Open TUN device
    int tun_fd = tun_open("tun0");
    if (tun_fd < 0) {
        fprintf(stderr, "Failed to open TUN device. Run with sudo?\n");
        return 1;
    }

    // Configure with IP addresses
    if (tun_configure("tun0", "10.0.0.1", "10.0.0.2") != 0) {
        fprintf(stderr, "Failed to configure TUN device\n");
        close(tun_fd);
        return 1;
    }

    printf("TUN device ready. Listening for packets...\n");
    printf("Test with: ping 10.0.0.2\n\n");

    // Main loop - read packets
    unsigned char buffer[BUFFER_SIZE];
    while (1) {
        int nread = tun_read(tun_fd, buffer, BUFFER_SIZE);
        if (nread < 0) {
            perror("Error reading from TUN");
            break;
        }

        printf("--- Received %d bytes ---\n", nread);

        // Parse IP header
        if (nread < sizeof(struct iphdr)) {
            printf("Packet too small for IP header\n\n");
            continue;
        }

        struct iphdr *iph = (struct iphdr *)buffer;

        // Extract fields
        char src_ip[16], dst_ip[16];
        ip_to_str(iph->saddr, src_ip);
        ip_to_str(iph->daddr, dst_ip);

        printf("IP version: %d\n", IP_VERSION(iph));
        printf("Header length: %d bytes\n", IP_HDRLEN(iph));
        printf("Total length: %d\n", ntohs(iph->tot_len));
        printf("Protocol: %d\n", iph->protocol);
        printf("TTL: %d\n", iph->ttl);
        printf("Source IP: %s\n", src_ip);
        printf("Dest IP: %s\n", dst_ip);

        // Show hex dump
        printf("\nHex dump:\n");
        hex_dump(buffer, nread);
        printf("\n");
    }

    close(tun_fd);
    return 0;
}
