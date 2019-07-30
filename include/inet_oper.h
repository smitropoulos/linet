//
// Created by smitropoulos on 29/07/2019.
//

#ifndef LINET_INET_OPER_H
#define LINET_INET_OPER_H

#include "inet_spec_packet.h"
#define WOL_PORT 9

#ifdef __cplusplus
extern "C"{
#endif


int sendWOLPacket(unsigned char *packet);


#ifdef __cplusplus
}
#endif

#endif //LINET_INET_OPER_H
