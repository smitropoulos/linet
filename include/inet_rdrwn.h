#ifndef LINET_INET_RDRWN_H
#define LINET_INET_RDRWN_H

#include "inet_spec_packet.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PACKET_LENGTH 16

#ifdef __cplusplus
extern "C" {
#endif

ssize_t readn(int fd, void *buffer, size_t n);

ssize_t writen(int fd, const void *buffer, size_t n);

int createWOLpacket(const unsigned char mac_address[]);

#ifdef __cplusplus
}
#endif

#endif // LINET_INET_RDRWN_H
