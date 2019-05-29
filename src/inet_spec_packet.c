//
// Created by Stefanos Mitropoulos on 2019-05-27.
//

#include "inet_spec_packet.h"

void createMagicPacket(unsigned char *magicPacket, char *physicalAddress) {
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