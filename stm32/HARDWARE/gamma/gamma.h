#ifndef __gamma_H
#define __gamma_H

#include "stm32f10x.h"
void send_command(void);
//void readID(void);
void sendID(u8 *send_str);
void gamma_test(unsigned char str5);
void fliker_test(unsigned char str5);
void auto_gamma(unsigned char str5);
void auto_gamma2(unsigned char str5);



void auto_fliker(unsigned char str5);
void auto_fliker1(unsigned char str5);
#endif
