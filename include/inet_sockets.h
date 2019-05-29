//
// Created by smitropoulos on 5/24/19.
//

#ifndef LINET_INET_SOCKETS_H
#define LINET_INET_SOCKETS_H

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#ifdef __cplusplus
extern "C"{
#endif

#define TRUE 1
#define FALSE 0

#define IS_ADDR_STR_LEN 4096

/* Suggested length for string buffer that caller
should pass to inetAddressStr(). Must be greater
than (NI_MAXHOST + NI_MAXSERV + 4) */


int inetConnect(const char* host, const char* service, int type);

static int inetPassiveSocket(const char* service, int type, socklen_t* addrlen, int doListen, int backlog);

int inetListen(const char* service, int backlog, socklen_t* addrlen);

int inetBind(const char* service, int type, socklen_t* addrlen);

char* inetAddressStr(const struct sockaddr* addr, socklen_t addrlen, char* addrStr, int addrStrLen);

#ifdef __cplusplus
}
#endif

#endif //LINET_INET_SOCKETS_H
