#include <STC15F2K60S2.H>
#include "intrins.h"
#include "I2C.h"
#define DELAY_TIME 5

/** 定义I2C总线时钟线和数据线 */
sbit scl = P2^0;
sbit sda = P2^1;

/**
* @brief I2C总线中一些必要的延时
*
* @param[in] i - 延时时间调整.
* @return none
*/
void i2c_delay(unsigned char i)
{
    do
    {
        _nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();		
    }
    while(i--);        
}

/**
* @brief 产生I2C总线启动条件.
*
* @param[in] none
* @param[out] none
* @return none
*/
void one_start()
{
    sda = 1;
    scl = 1;
    i2c_delay(DELAY_TIME);
    sda = 0;
    i2c_delay(DELAY_TIME);
    scl = 0;    
}

/**
* @brief 产生I2C总线停止条件
*
* @param[in] none
* @param[out] none.
* @return none
*/
void one_stop()
{
    sda = 0;
    scl = 1;
    i2c_delay(DELAY_TIME);
    sda = 1;
    i2c_delay(DELAY_TIME);       
}

/**
* @brief I2C发送一个字节的数据
*
* @param[in] byt - 待发送的字节
* @return none
*/
void one_sendByte(unsigned char byt)
{
    unsigned char i;
//
	EA = 0;
    for(i=0; i<8; i++){
        scl = 0;
        i2c_delay(DELAY_TIME);
        if(byt & 0x80){
            sda = 1;
        }
        else{
            sda = 0;
        }
        i2c_delay(DELAY_TIME);
        scl = 1;
        byt <<= 1;
        i2c_delay(DELAY_TIME);
    }
	EA = 1;
//
    scl = 0;  
}

/**
* @brief 等待应答
*
* @param[in] none
* @param[out] none
* @return none
*/
unsigned char I2C_recv_ack()
{
	unsigned char ackbit;
	sda=1;
    scl = 1;
    i2c_delay(DELAY_TIME);
    ackbit = sda; //while(sda);  //wait ack
    scl = 0;
    i2c_delay(DELAY_TIME);
	
	return ackbit;
}

/**
* @brief I2C接收一个字节数据
*
* @param[in] none
* @param[out] da
* @return da - 从I2C总线上接收到得数据
*/
unsigned char I2C_ReceiveByte(void)
{
	unsigned char da;
	unsigned char i;
//
	EA = 0;	
	for(i=0;i<8;i++){   
		scl = 1;
        sda=1;
		//i2c_delay(DELAY_TIME);
		da <<= 1;
		if(sda) 
			da |= 0x01;
		scl = 0;
		//i2c_delay(DELAY_TIME);
	}
	EA = 1;
//
	return da;    
}

/**
* @brief 发送应答
*
* @param[in] ackbit - 设定是否发送应答
* @return - none
*/
void I2C_send_ac(unsigned char What)
{
    scl = 0;
    sda = What;  //0：发送应答信号；1：发送非应答信号
    //i2c_delay(DELAY_TIME);
    scl = 1;
    //i2c_delay(DELAY_TIME);
    scl = 0; 
	sda = 1;
   // i2c_delay(DELAY_TIME);
}

/**
* @brief 读写操作过程中一些必要的延时
*
* @param[in] i - 指定延时时间
* @return - none
*/
void operate_delay(unsigned char t)
{
	unsigned char i;
	
	while(t--){
		for(i=0; i<112; i++);
	}
}