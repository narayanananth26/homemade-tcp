#include "tun.h"
#include <fcntl.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

int tun_open(const char *dev_name) {
    char dev_path[256];
    snprintf(dev_path, sizeof(dev_path), "/dev/%s", dev_name);

    int fd = open(dev_path, O_RDWR);
    if (fd < 0) {
        perror("Cannot open TUN device");
        return -1;
    }

    printf("Opened TUN device: %s (fd=%d)\n", dev_path, fd);
    return fd;
}

int tun_configure(const char *dev_name, const char *local_ip,
                  const char *remote_ip) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "ifconfig %s %s %s up", dev_name, local_ip,
             remote_ip);

    printf("Configuring TUN: %s\n", cmd);
    return system(cmd);
}

int tun_read(int fd, void *buf, int len) { return read(fd, buf, len); }

int tun_write(int fd, const void *buf, int len) { return write(fd, buf, len); }
