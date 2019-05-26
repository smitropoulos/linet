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

#define TRUE 1
#define FALSE 0

#define IS_ADDR_STR_LEN 4096

/* Suggested length for string buffer that caller
should pass to inetAddressStr(). Must be greater
than (NI_MAXHOST + NI_MAXSERV + 4) */

#ifdef __cplusplus
extern "C"{
#endif

int inetConnect(const char* host, const char* service, int type);

static int inetPassiveSocket(const char* service, int type, socklen_t* addrlen, int doListen, int backlog);

/*Return a listening FD for service with a backlog. If *addrlen  !=NULL then it will store the length of the created
 * socket to what it points to.*/
int inetListen(const char* service, int backlog, socklen_t* addrlen);

/*Primarily used for UDP servers. It creates and binds a socket of type (SOCK_STREAM || SOCK_DGRAM) on the wildcard IP of the host on port service. If *addrlen  !=NULL then it will store the length of the created
 * socket to what it points to.*/
int inetBind(const char* service, int type, socklen_t* addrlen);

/* Returns a null terminated string containing the human readable hostname and port into addrStr whose size is AddrStrLen. An always appropriate size is IS_ADDR_STR_LEN*/
char* inetAddressStr(const struct sockaddr* addr, socklen_t addrlen, char* addrStr, int addrStrLen);

#ifdef __cplusplus
}
#endif

#endif //LINET_INET_SOCKETS_H
