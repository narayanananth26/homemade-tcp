CC = clang
CFLAGS = -Wall -Wextra -Werror -Iinclude -g -std=c11
LDFLAGS =

# Source files
TUN_SRC = src/tun.c
UTILS_SRC = src/utils.c
COMMON_SRCS = $(TUN_SRC) $(UTILS_SRC)
COMMON_OBJS = $(COMMON_SRCS:.c=.o)

# Targets
all: packet_reader

packet_reader: examples/packet_reader.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(COMMON_OBJS) packet_reader

.PHONY: all clean
