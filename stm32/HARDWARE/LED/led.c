/******************** ��ѧ�Ƽ� **************************
 * ʵ��ƽ̨��������STM32������
 * ��汾  ��ST3.5.0
 * ����    ����ѧ�Ƽ��Ŷ� 
 * �Ա�    ��http://shop102218275.taobao.com/
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 *��Ȩ���У�����ؾ���
**********************************************************************************/
#include "LED.h"

/*
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
 */
void GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	 GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOE������ʱ��*/
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	/*ѡ��Ҫ���Ƶ�GPIOC����*/															   
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	

	/*��������ģʽΪͨ���������*/
  	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIOC*/
     GPIO_Init(GPIOE, &GPIO_InitStructure);
	 
    /*PE.8 �����*/
    
	   GPIO_SetBits(GPIOE,GPIO_Pin_6);   
	
	
	


}



