#include "inet_rdrwn.h"


/*!
 * Read data off of a socket
 * @param fd File descriptor to read data from
 * @param buffer Where to put the data read
 * @param n What size will be the data to be read
 * @return returns the number of bytes read or -1 for error
 */
ssize_t readn(int fd, void *buffer, size_t n) {

    ssize_t numRead; /* # of bytes fetched by last read() */
    size_t totRead; /* Total # of bytes read so far */
    char *buf;
    buf = buffer; /* No pointer arithmetic on "void *" */
    for (totRead = 0; totRead < n;) {
        numRead = read(fd, buf, n - totRead);
        if (numRead == 0) /* EOF */
            return totRead; /* May be 0 if this is first read() */
        if (numRead == -1) {
            if (errno == EINTR) {
                continue; /* Interrupted --> restart read() */
            } else if (errno == EWOULDBLOCK || errno == EAGAIN) {
                break;  /* Would block --> exit the loop */
            } else {
                return -1; /* Some other error */
            }
            break;
        }
        totRead += numRead;
        buf += numRead;
    }
    return totRead; /* Must be 'n' bytes if we get here */
}

/*!
 * Writes data to an fd
 * @param fd File descriptor to write data to
 * @param buffer Buffer that contains the data to be written
 * @param n Number of bytes to be written to fd
 * @return returns the number of bytes written or -1 for error
 */
ssize_t writen(int fd, const void *buffer, size_t n) {
    ssize_t numWritten; /* # of bytes written by last write() */
    size_t totWritten; /* Total # of bytes written so far */
    const char *buf;
    buf = buffer; /* No pointer arithmetic on "void *" */
    for (totWritten = 0; totWritten < n;) {
        numWritten = write(fd, buf, n - totWritten);
        if (numWritten <= 0) {
            if (numWritten == -1 && errno == EINTR) {
                continue; /* Interrupted --> restart write() */
            } else if (errno == EWOULDBLOCK || errno == EAGAIN) {
                continue;  /* Would block --> try again */
            } else
                return -1; /* Some other error */
        }
        totWritten += numWritten;
        buf += numWritten;
    }
    return totWritten; /* Must be 'n' bytes if we get here */
}

int sendWOLpacket(char *physicalAddress) {

    int broadcast = 1;
    struct sockaddr_in udpClient;
    struct sockaddr_in udpServer;
    char broadcastAddress[16] = "192.168.100.255";

    // Setup broadcast socket
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (setsockopt(udpSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast) == -1) {
        perror("Failed to setup a broadcast socket.\n");
        return -1;
    }

    // Set parameters
    udpClient.sin_family = AF_INET;
    udpClient.sin_addr.s_addr = INADDR_ANY;
    udpClient.sin_port = 0;
    // Bind socket
    if (bind(udpSocket, (struct sockaddr *) &udpClient, sizeof(udpClient)) < 0) {
        perror("Failed to bind.\n");
        return -1;
    }

    // Set server end point (the broadcast addres)
    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = inet_addr(broadcastAddress);
    udpServer.sin_port = htons(9);

    unsigned char packet[102];
    createMagicPacket(packet, physicalAddress);

    // Send the packet
    int rv = sendto(udpSocket, &packet, sizeof(unsigned char) * 102, 0, (struct sockaddr *) &udpServer,
                    sizeof(udpServer));

    return rv;
}