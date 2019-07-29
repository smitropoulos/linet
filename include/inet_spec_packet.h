//
// Created by Stefanos Mitropoulos on 2019-05-27.
//

#ifndef LINET_INET_SPEC_PACKET_H
#define LINET_INET_SPEC_PACKET_H

#ifdef __cplusplus
extern "C"{
#endif

#include <string.h>

#define MAGIC_PACKET_LENGTH 102

// Create Magic Packet.  Magic packet consists of 6 bytes of 0xFF (255) and 16 times the mac address of the target
void createMagicPacket(unsigned char *magicPacket, char *physicalAddress);

#ifdef __cplusplus
}
#endif


#endif //LINET_INET_SPEC_PACKET_H
