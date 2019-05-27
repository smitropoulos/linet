//
// Created by Stefanos Mitropoulos on 2019-05-27.
//

#ifndef LINET_SPEC_PACKET_H
#define LINET_SPEC_PACKET_H

#ifdef __cplusplus
extern "C"{
#endif

#include <string.h>

// Create Magic Packet
void createMagicPacket(unsigned char *magicPacket, unsigned int *physicalAddress) {
    int i;
    // Mac Address Variable
    unsigned char mac[6];

    // 6 x 0xFF on start of magicPacket
    for (i = 0; i < 6; i++) {
        magicPacket[i] = 255;
        mac[i] = physicalAddress[i];
    }
    // Fill the rest of the magicPacket with 16 times the mac address
    for (i = 1; i <= 16; i++) {
        memcpy(&magicPacket[i * 6], &mac, 6 * sizeof(unsigned char));
    }
}

#ifdef __cplusplus
}
#endif


#endif //LINET_SPEC_PACKET_H
