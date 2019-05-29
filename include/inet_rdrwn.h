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

#ifdef __cplusplus
extern "C"{
#endif


ssize_t readn(int fd, void *buffer, size_t n);

ssize_t writen(int fd, const void *buffer, size_t n);

int sendWOLpacket(char *physicalAddress);

#ifdef __cplusplus
}
#endif

#endif //LINET_INET_RDRWN_H