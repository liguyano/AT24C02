//
// Created by kurum on 2/19/2023.
//

#include "MAtrix_key.h"
void Delay(unsigned char t)/*延时函数*/
{
    while(t--)
    {
        //Display_Dynamic();
    }
}
unsigned char get_fromt_P3()
{

    if (!P34)
        return 0;
    else if (!P35)
        return 1;
    else if (!P42)
        return 2;
    else if (!P44)
        return 3;
    else
        return 9;
}
/**
 * @brief which key of matrix been clciked
 * */
unsigned char get_key()
{//P34 P35 P42 P44
    unsigned char i=0,t=0;
    for (;i<4;i++) {
        P3 |= 0x0f;
        P3 &= _crol_(0xFE, i);
        t=get_fromt_P3();
        if (t!=9)
        {
            return (i*4+t);
        }
    }
    return 17;
    // DisplaySMG_Bit(SMG_duanma[get_fromt_P3()],0);

}