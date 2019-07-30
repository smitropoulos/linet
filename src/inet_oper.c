//
// Created by smitropoulos on 29/07/2019.
//

#include "inet_oper.h"
#include "inet_sockets.h"

int sendWOLPacket(unsigned char *packet) {

    int sock;
    int optval = 1;
    struct sockaddr_in addr;
    const char broadcast_addr[] = "255.255.255.255";

    addr.sin_family = AF_INET;
    addr.sin_port = htons(WOL_PORT);

    if (inet_aton(broadcast_addr, &addr.sin_addr) == 0) {
        perror("Not valid IP address given");
        return -1;
    }

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("Problem in creating a socket!");
        return -1;
    }

    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *) &optval, sizeof(optval)) < 0) {
        perror("Problem in setting socket options!");
        return -1;
    }

    if (sendto(sock, packet, MAGIC_PACKET_LENGTH, 0, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("Cannot send data!");
        return -1;
    }

    return 0;
}