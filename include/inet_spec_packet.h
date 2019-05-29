//
// Created by Stefanos Mitropoulos on 2019-05-27.
//

#ifndef LINET_INET_SPEC_PACKET_H
#define LINET_INET_SPEC_PACKET_H

#ifdef __cplusplus
extern "C"{
#endif

#include <string.h>

// Create Magic Packet
void createMagicPacket(unsigned char *magicPacket, char *physicalAddress);

#ifdef __cplusplus
}
#endif


#endif //LINET_INET_SPEC_PACKET_H
