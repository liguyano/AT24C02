//
// Created by kurum on 2/21/2023.
//

#ifndef CMAKELISTS_TXT_ATC02_H
#define CMAKELISTS_TXT_ATC02_H
#include "I2C.h"
#define ADDR 0xA0
void ATC_WRITE_DATA(unsigned char WordAddress, unsigned char Byte);
unsigned char atc_recv_data(unsigned char address);

#endif //CMAKELISTS_TXT_ATC02_H
