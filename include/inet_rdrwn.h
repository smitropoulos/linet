#ifndef LINET_INET_RDRWN_H
#define LINET_INET_RDRWN_H

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include "inet_spec_packet.h"

#define PACKET_LENGTH 16

#ifdef __cplusplus
extern "C"{
#endif


ssize_t readn(int fd, void *buffer, size_t n);

ssize_t writen(int fd, const void *buffer, size_t n);

int createWOLpacket(const unsigned char mac_address[]);

#ifdef __cplusplus
}
#endif

#endif //LINET_INET_RDRWN_H