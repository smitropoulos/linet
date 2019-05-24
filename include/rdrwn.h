#ifndef LINET_RDRWN_H
#define LINET_RDRWN_H

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

ssize_t readn(int fd, void *buffer, size_t n);

ssize_t writen(int fd, const void *buffer, size_t n);

#endif //LINET_RDRWN_H