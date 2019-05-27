//
// Created by smitropoulos on 5/24/19.
//

#include "inet_sockets.h"
#include "../include/inet_sockets.h"

/*!
 * Create a socket of type (SOCK_STREAM || SOCK_DGRAM) and connect to a host on a service
 * @param host The host to connect to (either format)
 * @param service Service name or PORT number
 * @param type (SOCK_STREAM || SOCK_DGRAM) for their respective usage of TCP or UDP
 * @return Returns -1 on failure or the file descriptor it is connected to on success.
 */
int inetConnect(const char *host, const char *service, int type) {

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC; /* Allows IPv4 or IPv6 */
    hints.ai_socktype = type;   /* SOCK_STREAM SOCK_DGRAM */

    s = getaddrinfo(host, service, &hints, &result);
    if (s != 0) {
        errno = ENOSYS;
        return -1;
    }
    /* Walk through returned list until we find an address structure
    that can be used to successfully connect a socket */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue; /* On error, try next address */
        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break; /* Success */
        /* Connect failed: close this socket and try next address */
        close(sfd);
    }
    freeaddrinfo(result);
    return (rp == NULL) ? -1 : sfd;
}

/*!
 Public interfaces: inetBind() and inetListen()
 */
static int inetPassiveSocket(const char *service, int type, socklen_t *addrlen, int doListen, int backlog) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, optval, s;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = type;  /* SOCK_STREAM SOCK_DGRAM */
    hints.ai_family = AF_UNSPEC; /* Allows IPv4 or IPv6 */
    hints.ai_flags = AI_PASSIVE; /* Use wildcard IP address */
    s = getaddrinfo(NULL, service, &hints, &result);
    if (s != 0)
        return -1;
    /* Walk through returned list until we find an address structure
    that can be used to successfully create and bind a socket */
    optval = 1;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue; /* On error, try next address */
        if (doListen) {
            if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval,
                           sizeof(optval)) == -1) {
                close(sfd);
                freeaddrinfo(result);
                return -1;
            }
        }
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break; /* Success */
        /* bind() failed: close this socket and try next address */
        close(sfd);
    }
    if (rp != NULL && doListen) {
        if (listen(sfd, backlog) == -1) {
            freeaddrinfo(result);
            return -1;
        }
    }
    if (rp != NULL && addrlen != NULL)
        *addrlen = rp->ai_addrlen; /* Return address structure size */

    freeaddrinfo(result);
    return (rp == NULL) ? -1 : sfd;
}

/*!
 * Return a listening FD for service with a backlog. If *addrlen  !=NULL then it will store the length of the created
 * socket to what it points to.
 * @param service Service name or PORT number
 * @param backlog is equal to the number of pending connections the queue will hold.
 * @param addrlen a pointer to a socklen_t object to store the length of the returned socket to
 * @return a file descriptor to the socket opened
 */
int inetListen(const char *service, int backlog, socklen_t *addrlen) {
    return inetPassiveSocket(service, SOCK_STREAM, addrlen, TRUE, backlog);
}

/*!
 * Primarily used for UDP servers. It creates and binds a socket of type (SOCK_STREAM || SOCK_DGRAM) on the wildcard IP
 * of the host on port service. If *addrlen  !=NULL then it will store the length of the created
 * socket to what it points to.
 * @param service Service name or PORT number
 * @param type (SOCK_STREAM || SOCK_DGRAM) for their respective usage of TCP or UDP
 * @param addrlen a pointer to a socklen_t object to store the length of the returned socket to
 * @return a file descriptor to the socket opened
 */
int inetBind(const char *service, int type, socklen_t *addrlen) {
    return inetPassiveSocket(service, type, addrlen, FALSE, 0);
}

/*!
 * Returns a null terminated string containing the human readable hostname and port into addrStr whose size is
 * AddrStrLen. An always appropriate size is IS_ADDR_STR_LEN
 * @param addr a pointer to a sockaddr object which holds data on the connected peer
 * @param addrlen the lenght of the connected peer's address
 * @param addrStr a char array to store the returned human readable address
 * @param addrStrLen the length of the char array addrStr
 * @return returns addrStr
 */
char *inetAddressStr(const struct sockaddr *addr, socklen_t addrlen, char *addrStr, int addrStrLen) {
    char host[NI_MAXHOST], service[NI_MAXSERV];
    if (getnameinfo(addr, addrlen, host, NI_MAXHOST,
                    service, NI_MAXSERV, NI_NUMERICSERV) == 0)
        snprintf(addrStr, addrStrLen, "(%s, %s)", host, service);
    else
        snprintf(addrStr, addrStrLen, "(?UNKNOWN?)");
    addrStr[addrStrLen - 1] = '\0'; /* Ensure result is null-terminated */
    return addrStr;
}