
#include "delay.h"
#include "sys.h"
#include "spi.h"
#include "init_code.h"
#include "usart.h"
#include "led.h"
#include "gamma.h"
#include "9702gamma.h"
#include <assert.h>
#include <string.h>
#include "stdlib.h"
#include "key.h"
extern	u8 Res;
extern  u16 counter,counter2;
extern u8 value2[8888];
extern u8 mode;
extern u8 flag;
extern u16 longer;//统计发送语句的条数
extern u16 lenth;//统计发送数据的个数
u8 str9_temp;


extern u8 D1[53];
extern u8 D2[53];
extern u8 D3[53];            
extern u8 D4[53];             
extern u8 D5[53];              
extern u8 D6[53];

unsigned char now_str2;
unsigned char now_str3;

u8 gray_number[26]={0,1,3,5,7,11,15,23,31,47,63,95,127,128,160,192,208,224,232,240,244,248,250,252,254,255};
 
//ALIENTEK战舰STM32开发板实验1
//跑马灯实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

extern unsigned char str[11];//接收到的数据
extern unsigned char send_str[11];//发送的数据





 int main(void)
 {	
	 u8 n;
	GPIO_Config();
	delay_init();	    	 //延时函数初始化	  
  SPI1_Config();
  uart_init(9600);
	init_code(); 
	 KEY_Init();
	delay_ms (800);
	 send_str[5] = 128;
	    GPIO_SetBits(GPIOB,GPIO_Pin_8);
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
		
	   GPIO_SetBits(GPIOE,GPIO_Pin_6);
        while(1)
				{
					    										
						if(str[1] == 1)  //模式一为手动	
						{		
							  
							delay_ms(200);
							str[1] = 00;
					    send_str[0] = 17;
		          send_str[1] = 01;
		          send_str[2] = str[2];
		          send_str[3] = 00;
		          send_str[4] = 00;
		          send_str[5] = 00;
		          send_str[6] = 00;
		          send_str[7] = 00;
		          send_str[8] = 01;
		          send_str[9] = 00;   //finish
		          send_str[10] = 187;
		          sendID(send_str);
							
						}
			    	else if(str[1] == 2)  //规定模式为自动fliker
					  {
						 
							str[1] =0;
							if(str[4] == 0)
	                   auto_fliker(str[5]);
							else if(str[4] == 1)
				       auto_fliker1(str[5]);
							else if(str[4] == 2)  //9702
				       auto_9702fliker(str[5]);
						}
						
						else if(str[1] == 3)   //规定模式为自动gamma
						{
							str[1] =0;
							if(str[7] == 0)
							{
								if(str[4] == 0)
							 auto_gamma(str[5]);
								else if(str[4] == 1)
							 auto_gamma2(str[5]);
								else	if(str[4] == 3)
							 auto_gamma3(str[5]);
							//	else if(str[4] == 3)
							// auto_gamma4(str[5]);
							}
							else 
							{
									 	key_gamma_up(28);     
							    	break;
							}								
			       				
	          }
						
	       else if(str[1] == 4)  //模式4为测量fliker模式	
						{
					   
						  fliker_test(str[5]);
							 fliker_test(str[5]);
							 fliker_test(str[5]);
 				//只测量一次	
							 		str[1] =0;
						 break;	

						}
						
					else if(str[1] == 5)
						{
							str[1] =0;
						  gamma_test(str[5]);
	
						}
						else if(str[1] == 6)
						{
							str[1] =0;
						  gamma_base(str[5]);
	
						}
	 }		
			}
		
//Generic_Short_Write_1P(0x9a,0x8D);            
//Generic_Short_Write_1P(0x9b,0x73);  
//Generic_Short_long_2P(0x82,0x55,0x55);	 
//Generic_Long_Write_2P(0x12,0x13,0x14);                         
//Generic_Long_Write_3P(0x15,0x16,0x17,0x18);                    
//Generic_Long_Write_4P(0x19,0x20,0x21,0x22,0x23);               
//Generic_Long_Write_5P(0x24,0x25,0x26,0x27,0x28,0x29);          
//Generic_Long_Write_6P(0x30,0x31,0x32,0x33,0x34,0x35,0x36);     
//Generic_Long_Write_7P(0x37,0x38,0x39,0x40,0x41,0x42,0x43,0x44);
		


			
//Generic_Short_Write_1P(0xFF,0x00);            
//Generic_Short_Write_1P(0xFF,0x00);
//Generic_Short_Write_1P(0xFF,0x00);            
//Generic_Long_Write_FIFO(5,array());


	 

	
			