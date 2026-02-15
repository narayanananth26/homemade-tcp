#ifndef TUN_H
#define TUN_H

// Open a TUN device on macOS
// Returns file descriptor or -1 on error
int tun_open(const char *dev_name);

// Configure TUN device with IP address
int tun_configure(const char *dev_name, const char *local_ip, const char *remote_ip);

// Read a packet from TUN device
// Returns number of bytes read or -1 on error
int tun_read(int fd, void *buf, int len);

// Write a packet to TUN device
int tun_write(int fd, const void *buf, int len);

#endif // TUN_H
