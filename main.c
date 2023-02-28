
#include "MAtrix_key.h"
#include "SSS.h"
#include "ATC02.h"
#include <math.h>
unsigned char yu = 1;/*用于记录月份*/
unsigned char code SMG_duanma[18]=
{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
0xbf,0x7f};/*用于数码管段选*/
void SelectHC573(unsigned char channel)/*74HC573锁存器*/
{
    switch(channel)
    {
        /*
         * &0x1f 将前三位置0
         * | 0x80 将第一位置1
         * | 0xa0 1010 0000
         * */
        case 4:
            P2 = (P2 & 0x1f) | 0x80;
            break;
        case 5:
            P2 = (P2 & 0x1f) | 0xa0;
            break;
        case 6:
            P2 = (P2 & 0x1f)| 0xc0;//1100
            break;
        case 7:
            P2 = (P2 & 0x1f) | 0xe0;
            break;
    }
}

void DIAPlaySMG_Bit(unsigned char value, unsigned char pos)/*数码管显示*/
{
    P0 = 0xff;
    /*段选*/
    SelectHC573(6);
    P0 = 0x01 << pos;
    P2&=0x1f;
    /*位选*/
    SelectHC573(7);
    P0 = value;
    P2&=0x1f;
}

void DelaySMG(unsigned int t)/*数码管延时函数*/
{
    while(t--);
}
void showMoreNUm(unsigned char num,unsigned char start)
{
    unsigned char h,t=0;
    h=num/100;
    DIAPlaySMG_Bit(SMG_duanma[h],start+0);
    DelaySMG(50);
    num=num%100;
    t=num/10;
    DIAPlaySMG_Bit(SMG_duanma[t],start+1);DelaySMG(50);
    num%=10;
    DIAPlaySMG_Bit(SMG_duanma[num],start+2);DelaySMG(50);

}
void showIntNUm(unsigned int num)
{
    unsigned char i,s;
    for (i=1;i<6;i++)
    {
        s=num/ pow(10.0,5.0-i*1.0) ;
        num %= (unsigned int ) pow(10.0,5.0-i);
        DIAPlaySMG_Bit(SMG_duanma[s],i-1);
        Delay(10);
    }
}

/**
 * @brief get which key of that raw has been clicked;
 * @return means which one
 * */

void Timer1Init(void)		//100微秒@11.0592MHz
{
    EA=1;
    PX1=1;
    ET1=1;
    EX0=1;
    IT0=0;
    AUXR |= 0x80;		//定时器时钟1T模式
    TMOD &= 0xF0;		//设置定时器模式
    TL0 = 0x50;		//设置定时初值
    TH0 = 0xFB;		//设置定时初值
    TF0 = 0;		//清除TF0标志
    TR0 = 1;		//定时器0开始计时
    ET0=1;
}
void Delay500ms()		//@11.0592MHz
{
    unsigned char i, j, k;

    _nop_();
    _nop_();
    i = 3;
    j = 26;
    k = 223;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

static unsigned int t1=0x0000;

unsigned char kk=17;
void main()
{unsigned  char xdata i = 0,t=0x22,sum=0;
    unsigned char keys[8]={16,16,16,16,16,16,16,16};
    Timer1Init();
    //unsigned char tmp=0;
   t1= atc_recv_data(0x00);
    SelectHC573(4);
   // t1=t;
    P0=0xff;    P2&=0x1f;

    //close the buzz
    SelectHC573(5);
    P0=0x00;
    P2&=0x1f;

    while(1) {
        kk=get_key();

        if (kk==0)
        {
            t1++;
            while (get_key()<17);
        } else if (kk==1)
        {
            t1--;
            while (get_key()<17);
        } else if( kk==2)
        {
            t=t1>>8;
            ATC_WRITE_DATA(0x00,t);

            Delay500ms();
            t1<<=8;
            t1>>=8;
            ATC_WRITE_DATA(0x01,t1);
            Delay500ms();
            //t1=t;
            while (get_key()<17);
        } else if (kk==3)
        {
            Delay500ms();
            t= atc_recv_data(0x00);
            Delay500ms();
            sum= atc_recv_data(0x01);
            t1=t;
            t1<<=8;
            t1+=sum;
            while (get_key()<17);
        }
        else
        {
            showIntNUm(t1);
        }
        Delay(10);
    }
}

void timeout_0() interrupt NUM1
{static unsigned int sHow;
    TL0 = 0x50;        //设置定时初值
    TH0 = 0xFB;        //设置定时初值
    sHow++;
    if (sHow >= 5000)
    {
        t1--;
        sHow=0;
    }
}