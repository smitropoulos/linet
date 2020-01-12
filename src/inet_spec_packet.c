//
// Created by Stefanos Mitropoulos on 2019-05-27.
//

#include <stdlib.h>
#include "inet_spec_packet.h"
#include <stdio.h>


#define MAC_TOKENS       6
#define CONVERT_BASE       16

int createMagicPacket(unsigned char *magicPacket, char *mac) {

    size_t macLength = strlen(mac);

    char *tmpMac = ( char * ) malloc(
        macLength * sizeof(char) + 1); // argv is by default NULL terminated. Account for it with a spot for null termination in Malloc
    char *delimiter = ( char * ) ":";
    char *tok;
    unsigned char convertedMac[6];

    strcpy(tmpMac, mac);
    tok = strtok(tmpMac, delimiter);

    for ( int i = 0; i < MAC_TOKENS; i++ )
    {
        if ( tok == NULL)
        {
            return -1;
        }

        //Convert a string to long int with a convert base of 16 for hex
        convertedMac[i] = ( unsigned char ) strtol(tok, NULL, CONVERT_BASE);
        tok = strtok(NULL, delimiter);
    }

    // 6 x 0xFF on start of magicPacket
    for (int ii = 0; ii < 6; ii++) {
        magicPacket[ii] = 255;
    }

    for (int iii = 1; iii <= 16; iii++) {
        for (int j = 0; j < 6; j++) {
            magicPacket[iii * 6 + j] = convertedMac[j];
        }
    }

    free(tmpMac);

    return 0;
}