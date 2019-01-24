#ifndef __SPI_H
#define __SPI_H


#include "stm32f10x.h"
 
#define SPI_IO GPIOA   
#define SPI_DI GPIO_Pin_5  
#define SPI_CLK GPIO_Pin_6  
#define SPI_CS GPIO_Pin_7 

#define SPI_DI_H GPIO_SetBits(GPIOA, GPIO_Pin_5)  
#define SPI_DI_L GPIO_ResetBits(GPIOA, GPIO_Pin_5)  
#define SPI_CLK_H GPIO_SetBits(GPIOA, GPIO_Pin_6)  
#define SPI_CLK_L GPIO_ResetBits(GPIOA, GPIO_Pin_6)  
#define SPI_CS_H GPIO_SetBits(GPIOA, GPIO_Pin_7) 
#define SPI_CS_L GPIO_ResetBits(GPIOA, GPIO_Pin_7) 

void SPI1_Config(void);
void SPI_SendData(unsigned int i);
void SPI_SendData_Byte(unsigned int DATA0,unsigned int DATA1);
void SPI_WriteData(unsigned int i);
void SPI_WriteComm(unsigned int i);

void Generic_Short_Write_NP(unsigned int i);
void Generic_Short_Write_1P(unsigned int D0,unsigned int D1);
void Generic_Long_Write_2P(unsigned char D0,unsigned char D1,unsigned char D2);
void Generic_Long_Write_3P(unsigned char D0,unsigned char D1,unsigned char D2,unsigned char D3);
void Generic_Long_Write_4P(unsigned char D0,unsigned char D1,unsigned char D2,unsigned char D3,unsigned char D4);
void Generic_Long_Write_5P(unsigned char D0,unsigned char D1,unsigned char D2,unsigned char D3,unsigned char D4,unsigned char D5);
void Generic_Long_Write_6P(unsigned char D0,unsigned char D1,unsigned char D2,unsigned char D3,unsigned char D4,unsigned char D5,unsigned char D6);
void Generic_Long_Write_7P(unsigned char D0,unsigned char D1,unsigned char D2,unsigned char D3,unsigned char D4,unsigned char D5,unsigned char D6,unsigned char D7);
void Generic_Long_Write_FIFO(unsigned int num,unsigned char array[]);



#endif
