#include "spi.h"
void SPI1_Config() //spi接口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure; //声明一个结构体变量，用来初始化GPIO
	SystemInit();	//时钟初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=SPI_DI|SPI_CLK|SPI_CS;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(SPI_IO,&GPIO_InitStructure); 	   /* 初始化GPIO */



}
//SPI_写操作(16BIT)
void SPI_SendData(unsigned int i)
{  
	unsigned char n;
   for(n=0; n<16; n++)			
   {  
	  if(i&0x8000)
			SPI_DI_H;
     else 
			SPI_DI_L;
		 
			i<<= 1;
			SPI_CLK_L;
//		 __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
			SPI_CLK_H;
		}
}
void SPI_WriteData(unsigned int i)
{
  //flow of send Data	0x72
	unsigned char d=0x72;
	unsigned char n;
	
  SPI_CS_L;
	//__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	for(n=0; n<8; n++)			
  {  
	  if(d&0x80)
			SPI_DI_H;
     else 
			SPI_DI_L;

			d<<= 1;
			SPI_CLK_L;
		 //__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
			SPI_CLK_H;
	}
	 
		SPI_SendData(i);//D15-D0
    SPI_CS_H;
	//__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
}
//SPI_写操作(24BIT)
void SPI_SendData_Byte(unsigned int DATA0,unsigned int DATA1)//DEFINE
{  
	unsigned char ii;
	for(ii=0; ii<8; ii++){
	DATA1<<=1;
	}
	DATA1=DATA1+DATA0;
	SPI_WriteData(DATA1);
}

//SPI_写指令
void SPI_WriteComm(unsigned int i)
{
	//flow of send command	0x70
	unsigned char d=0x70;
	unsigned char n;
	
  SPI_CS_L;
	//__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	for(n=0; n<8; n++)			
  {  
	  if(d&0x80)
			SPI_DI_H;
     else 
			SPI_DI_L;

			d<<= 1;
			SPI_CLK_L;
		// __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
			SPI_CLK_H;
	}
	 
		SPI_SendData(i);//D15-D0
    SPI_CS_H;
//	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	
}
void Generic_Short_Write_NP(unsigned int i)//DEFINE
{
	SPI_WriteComm(0x00b7);
  SPI_WriteData(0x0110);
	
	SPI_WriteComm(0x00BC);
	SPI_WriteData(0x0001);

	SPI_WriteComm(0x00BF);
	SPI_WriteData(i);
  
}


void Generic_Short_Write_1P(unsigned int D0,unsigned int D1)///DEFINE
{
//	SPI_WriteComm(0x00b7);
//  SPI_WriteData(0x0110);//0110

	  SPI_WriteComm(0x00BC);
	  SPI_WriteData(0x0002);

	  SPI_WriteComm(0x00BF);
	  SPI_SendData_Byte(D0,D1);

}

void Generic_Long_Write_2P(unsigned char D0,unsigned char D1,unsigned char D2)///DEFINE
{

//	SPI_WriteComm(0x00b7);
//  SPI_WriteData(0x0510);
	
	SPI_WriteComm(0x00BC);
	SPI_WriteData(0x0003);

	SPI_WriteComm(0x00BF);
	SPI_SendData_Byte(D0,D1);
	
	SPI_WriteData(D2);
}

void Generic_Long_Write_3P(unsigned char D0,unsigned char D1,unsigned char D2,unsigned char D3)///DEFINE
{

	SPI_WriteComm(0x00BC);
	SPI_WriteData(0x0004);
	
	SPI_WriteComm(0x00BF);
	SPI_SendData_Byte(D0,D1);
	SPI_SendData_Byte(D2,D3);
	
	
}
void Generic_Long_Write_4P(unsigned char D0,unsigned char D1,unsigned char D2,unsigned char D3,unsigned char D4)///DEFINE
{

	SPI_WriteComm(0x00BC);
	SPI_WriteData(0x0005);

	SPI_WriteComm(0x00BF);
	SPI_SendData_Byte(D0,D1);
	SPI_SendData_Byte(D2,D3);
	
	SPI_WriteData(D4);
}

void Generic_Long_Write_5P(unsigned char D0,unsigned char D1,unsigned char D2,unsigned char D3,unsigned char D4,unsigned char D5)///DEFINE
{
	
	SPI_WriteComm(0x00BC);
	SPI_WriteData(0x0006);

	SPI_WriteComm(0x00BF);
	SPI_SendData_Byte(D0,D1);
	SPI_SendData_Byte(D2,D3);
	SPI_SendData_Byte(D4,D5);
	
	
}

void Generic_Long_Write_6P(unsigned char D0,unsigned char D1,unsigned char D2,unsigned char D3,unsigned char D4,unsigned char D5,unsigned char D6)///DEFINE
{

	SPI_WriteComm(0x00BC);
	SPI_WriteData(0x0007);

	SPI_WriteComm(0x00BF);
	
	SPI_SendData_Byte(D0,D1);
	SPI_SendData_Byte(D2,D3);
	SPI_SendData_Byte(D4,D5);
	SPI_WriteData(D6);
}

void Generic_Long_Write_7P(unsigned char D0,unsigned char D1,unsigned char D2,unsigned char D3,unsigned char D4,unsigned char D5,unsigned char D6,unsigned char D7)///DEFINE
{


	SPI_WriteComm(0x00BC);
	SPI_WriteData(0x0008);

	SPI_WriteComm(0x00BF);
	SPI_SendData_Byte(D0,D1);
	SPI_SendData_Byte(D2,D3);
	SPI_SendData_Byte(D4,D5);
	SPI_SendData_Byte(D6,D7);
}

void Generic_Long_Write_FIFO(unsigned int num,unsigned char array[])//num is array's number
{
	unsigned char n;

	SPI_WriteComm(0x00BC);
	SPI_WriteData(num);

	SPI_WriteComm(0x00BF);
	for(n=0; n<num;)
	{
		if((n+1)<num)
		{	
			SPI_SendData_Byte(array[n],array[n+1]);
			n=n+2;
		}
		else
		{
			SPI_WriteData(array[n]);
			n=n+1;
		}
	}//
}

