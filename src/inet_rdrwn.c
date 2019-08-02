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
        }
        totRead += numRead;
        buf += numRead;
    }
    return totRead; /* Must be 'n' bytes if we get here */
}

/*!
 * Writes data to an fd in a loop (for TCP)
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

int createWOLpacket(const unsigned char *mac_address) {

    unsigned char packet[PACKET_LENGTH];

    for (int i = 0; i < 6; i++) {
        packet[i] = 0xFF;
    }

    for (int i = 1; i <= 16; i++) {
        for (int j = 0; j < 6; j++) {
            packet[i * 6 + j] = mac_address[j];
        }
    }


}
