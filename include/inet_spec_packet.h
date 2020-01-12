//
// Created by Stefanos Mitropoulos on 2019-05-27.
//

#ifndef LINET_INET_SPEC_PACKET_H
#define LINET_INET_SPEC_PACKET_H

#ifdef __cplusplus
extern "C"{
#endif

#include <string.h>
#include <stdlib.h>
#define MAGIC_PACKET_LENGTH 102
#define MAC_TOKENS 6 //bytes
#define HEX_CONVERT_BASE 16 //
// Create Magic Packet.  Magic packet consists of 6 bytes of 0xFF (255) and 16 times the mac address of the target
int createMagicPacket(unsigned char *magicPacket, char *physicalAddress);

#ifdef __cplusplus
}
#endif


#endif //LINET_INET_SPEC_PACKET_H
