#ifndef __9702gamma_H
#define __9702gamma_H

#include "stm32f10x.h"

void auto_gamma3(unsigned char str5);
void auto_9702fliker(unsigned char str5);
void send_9702DC(unsigned char cmd,unsigned char data,unsigned char str5);
void send_9702array(unsigned char array1[],unsigned char array2[],char str5);

#endif
