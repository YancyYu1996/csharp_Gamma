#include "key.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板   

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9;//PE5.PE3
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);
}

void key_gamma_up(u16 gamma)
{
	u16 i;
	 GPIO_SetBits(GPIOE,GPIO_Pin_6);
	for(i = 0;i< gamma;i++)
	{
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		delay_ms(100);
	  GPIO_SetBits(GPIOB,GPIO_Pin_8);
		delay_ms(100);
	}
	GPIO_SetBits(GPIOB,GPIO_Pin_8);

}

void key_gamma_down(u16 gamma)
{
	u16 i;
	 GPIO_SetBits(GPIOE,GPIO_Pin_6);
	for(i = 0;i< gamma;i++)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		delay_ms(50);
	  GPIO_SetBits(GPIOB,GPIO_Pin_9);
		delay_ms(50);
	}
	GPIO_SetBits(GPIOB,GPIO_Pin_9);

}



