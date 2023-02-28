//
// Created by kurum on 2/21/2023.
//
#include "ATC02.h"
void ATC_WRITE_DATA(unsigned char WordAddress, unsigned char Byte)
{
    one_start();
    one_sendByte(ADDR);
    I2C_recv_ack();
    one_sendByte(WordAddress);
    I2C_recv_ack();
    one_sendByte(Byte);
    I2C_recv_ack();
    one_stop();
}
unsigned char atc_recv_data(unsigned char address)
{unsigned char result;
    one_start();
    one_sendByte(ADDR);
    I2C_recv_ack();
    one_sendByte(address);
    I2C_recv_ack();
    one_start();
    one_sendByte(ADDR |0x01);
    I2C_recv_ack();
    result=I2C_ReceiveByte();
    I2C_send_ac(1);
    one_stop();
    return result;

}
