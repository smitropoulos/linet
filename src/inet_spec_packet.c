//
// Created by Stefanos Mitropoulos on 2019-05-27.
//

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "inet_spec_packet.h"


#define MAC_ADDR_MAX       6
#define CONVERT_BASE       16

int createMagicPacket(unsigned char *magicPacket, char *mac) {

    char *tmpMac = (char *) malloc(strlen(mac) * sizeof(char));
    char *delimiter = (char *) ":";
    char *tok;
    unsigned char convMac[6];

    strncpy(tmpMac, mac, strlen(mac));
    tok = strtok(tmpMac, delimiter);

    for (int i = 0; i < MAC_ADDR_MAX; i++) {
        if (tok == NULL) {
            return -1;
        }

        convMac[i] = (unsigned char) strtol(tok, NULL, CONVERT_BASE);
        tok = strtok(NULL, delimiter);
    }

    // 6 x 0xFF on start of magicPacket
    for (int ii = 0; ii < 6; ii++) {
        magicPacket[ii] = 255;
        mac[ii] = mac[ii];
    }

    for (int iii = 1; iii <= 16; iii++) {
        for (int j = 0; j < 6; j++) {
            magicPacket[iii * 6 + j] = convMac[j];
        }
    }

    free(tmpMac);

    return 0;
}