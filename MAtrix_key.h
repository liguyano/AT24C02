//
// Created by kurum on 2/19/2023.
//

#ifndef CMAKELISTS_TXT_MATRIX_KEY_H
#define CMAKELISTS_TXT_MATRIX_KEY_H
#include "STC15F2K60S2.H"
#include <INTRINS.H>

void Delay(unsigned char t);/*延时函数*/

unsigned char get_key();
unsigned char get_fromt_P3();

#endif //CMAKELISTS_TXT_MATRIX_KEY_H
