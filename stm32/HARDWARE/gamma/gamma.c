#include "gamma.h"
#include "spi.h"
#include "stdlib.h"	
#include "usart.h"
#include "key.h"
#include "delay.h"
unsigned char array[5];
extern u8 str[11];//接收到的数据
extern u8 gray_number[26];
u8 send_str[11];
//                      v0        v1       v3        v5        v7       v11       v15       v23        v31       v47       v63       v95      v127       v128     v160      v192      v208      v224      v232      v240      v244     v248      v250      v252     v254       v255 
extern u8 D1[53];
extern u8 D2[53];
extern u8 D3[53];
extern u8 D4[53];
extern u8 D5[53];
extern u8 D6[53];

 		u8 time;
    int cha1;
    int cha2;
		  u8 number;
			
			void sendID(u8 *send_str)
{
	  int i;
		for(i = 0 ;i < 11;i++)
		if(send_str[i] < 16)
		{
		  printf("%x",0);
		  printf("%X",send_str[i]);
		}
		else 
			printf("%X",send_str[i]);
      printf("-");
}	
			
			void send_9503VDC(unsigned char cmd,unsigned char data)
	{
	  GPIO_ResetBits(GPIOE,GPIO_Pin_6);  		 
  Generic_Short_Write_1P(cmd,data);
		 
	 GPIO_SetBits(GPIOE,GPIO_Pin_6); 
	
	}
	
	void send_9503Vgamma(unsigned char str5)
	{
	         GPIO_ResetBits(GPIOE,GPIO_Pin_6);
		        Generic_Long_Write_FIFO(53,D1);
		        Generic_Long_Write_FIFO(53,D2);
		        Generic_Long_Write_FIFO(53,D3);
		        Generic_Long_Write_FIFO(53,D4);
		        Generic_Long_Write_FIFO(53,D5);
	          Generic_Long_Write_FIFO(53,D6);
	          GPIO_SetBits(GPIOE,GPIO_Pin_6);
			      delay_ms(350);  
	          send_str[0] = 17;
	          send_str[1] = 03;
	          send_str[2] = 00;
	          send_str[3] = 00;
	          send_str[4] = 00;
	          send_str[5] = str5;//灰阶
	          send_str[6] = 00;
	          send_str[7] = 00;
	          send_str[8] = 01;//finish
	          send_str[9] = 00;   
	          send_str[10] = 187;
	                  
			      sendID(send_str);
	
	}
			
			void flicker(void)
	{
		
		
		GPIO_ResetBits(GPIOE,GPIO_Pin_6); 
		Generic_Short_Write_1P(0x9a,number);
		Generic_Short_Write_1P(0x9b,number-cha1);
		Generic_Long_Write_2P(0x82,number-cha2,number-cha2);
		GPIO_SetBits(GPIOE,GPIO_Pin_6); 	
		
		delay_ms(500);
		send_str[0] = 17;
		send_str[1] = 02;
		send_str[2] = number;
		send_str[3] = number-cha1;
		send_str[4] = number-cha2;
		
		send_str[6] = 00;
		send_str[7] = 00;
		send_str[8] = 01;    //send_finish
		send_str[9] = 00;   //finish
		send_str[10] = 187;
		
		sendID(send_str);
	
		str[4] = str[4]+1;

	
	}
	
	
	void gamma_base(unsigned char str5)    //做标准曲线的切图函数
{
	 switch(str5)
	 {
	 //case 0 :key_gamma_up(0);delay_ms(500);break;       //若无fliker
		 case 0 :key_gamma_up(26);delay_ms(500);break;      //第0灰
		 case 255 :key_gamma_up(255);delay_ms(500);break;   //第255灰
		 case 1:key_gamma_up(28);delay_ms(500);break;       //图片复位1灰阶
    // default:key_gamma_up(1);delay_ms(500);break;
	 }
	 
							send_str[0] = 17;
	        	  send_str[1] = 06;
	        	  send_str[2] = 00;
	        	  send_str[3] = 00;
	        	  send_str[4] = 00;
	        	  send_str[5] = str5;//灰阶
	        	  send_str[6] = 00;
	        	  send_str[7] = 00;
	        	  send_str[8] = 00;//finish
	        	  send_str[9] = 00;   
	        	  send_str[10] = 187;
	        	  sendID(send_str);
	 
 }

void gamma_test(unsigned char str5) 
{
	 switch(str5)
	 {
	 //case 0 :key_gamma_up(0);delay_ms(500);break;       //若无fliker
		 case 0 :key_gamma_up(26);delay_ms(500);break;       //第0灰
		 case 255 :key_gamma_up(255);delay_ms(500);break;       //第255灰
		// case 1:key_gamma_up(28);delay_ms(500);break;
     default:key_gamma_up(1);delay_ms(500);break;
	 }
	            
	           
	             if(str5 <255)
							 {
	            send_str[0] = 17;
	        	  send_str[1] = 05;
	        	  send_str[2] = 00;
	        	  send_str[3] = 00;
	        	  send_str[4] = 00;
	        	  send_str[5] = str5;//灰阶
	        	  send_str[6] = 00;
	        	  send_str[7] = 00;
	        	  send_str[8] = 00;//finish
	        	  send_str[9] = 00;   
	        	  send_str[10] = 187;
	        	  sendID(send_str);
							 }
							
								 
							 
							 str5 = 0;
	
}
	
	void fliker_test(unsigned char str5) 
{

	            send_str[0] = 17;
	        	  send_str[1] = 04;
	        	  send_str[2] = 00;
	        	  send_str[3] = 00;
	        	  send_str[4] = 00;
	        	  send_str[5] = 00;//灰阶
	        	  send_str[6] = 00;
	        	  send_str[7] = 00;
	        	  send_str[8] = 01;//finish
	        	  send_str[9] = 00;   
	        	  send_str[10] = 187;
	        	  sendID(send_str);
	           delay_ms(200);
	          
	           			
}

void auto_fliker(unsigned char str5)
{
	          
               switch(str5)
							 {
							 case 128:
							 {
								 if(number == 0)
								 {   
									   cha1 = str[2]-str[3];
							       cha2 = str[2]-str[4];
										 key_gamma_up(13);
									   delay_ms(1000);
								 }
								  send_str[5] = 128;
								  flicker();
								  number ++;
								 break;
							 }
               case 160:								 
							 {
							    key_gamma_up(1);
								  delay_ms(1000);
								 
								 GPIO_ResetBits(GPIOE,GPIO_Pin_6); 
		            Generic_Short_Write_1P(0x9a,str[2]);
		            Generic_Short_Write_1P(0x9b,str[3]);
		            Generic_Long_Write_2P(0x82,str[4],str[4]);
			          GPIO_SetBits(GPIOE,GPIO_Pin_6); 	
		
		            delay_ms(350);
								 
								 send_str[0] = 17;
								send_str[1] = 02;
								send_str[2] = str[2];
								send_str[3] = str[3];
								send_str[4] = str[4];
								send_str[5] = 160;
								send_str[6] = 00;
								send_str[7] = 00;
								send_str[8] = 01;    //send_finish
								send_str[9] = 00;   //finish
								send_str[10] = 187;
								
								sendID(send_str);
								
							
								break;
							 }
							case 63:
							{
								 	key_gamma_down(4);
						    delay_ms(1000);
								GPIO_ResetBits(GPIOE,GPIO_Pin_6); 
		            Generic_Short_Write_1P(0x9a,str[2]);
		            Generic_Short_Write_1P(0x9b,str[3]);
		            Generic_Long_Write_2P(0x82,str[4],str[4]);
			          GPIO_SetBits(GPIOE,GPIO_Pin_6); 	
		
		            delay_ms(350);
								 
								 send_str[0] = 17;
								send_str[1] = 02;
								send_str[2] = str[2];
								send_str[3] = str[3];
								send_str[4] = str[4];
								send_str[5] = 63;
								send_str[6] = 00;
								send_str[7] = 00;
								send_str[8] = 01;    //send_finish
								send_str[9] = 00;   //finish
								send_str[10] = 187;
								
								sendID(send_str);
							  	 break;
							}
							    
							 }
				   
  
						if(str[9] == 1)  //全部发送完成
						{
							       str[9] = 0;
						         key_gamma_down(10);
						         delay_ms(1000);
								 }
						str5 = 0;
			 }

void auto_fliker1(unsigned char str5)
{
	          
               switch(str5)
							 {
							 case 128:
							 {
								 if(number == 0)
								 {   
									   cha1 = str[2]-str[3];
							       cha2 = str[2]-str[4];
										 key_gamma_up(13);
									   delay_ms(1000);
								 }
								  send_str[5] = 128;
								  flicker();
								  number ++;
								 break;
							 }
               case 160:								 
							 {
							    key_gamma_up(1);
								  delay_ms(1000);
								 
								 GPIO_ResetBits(GPIOE,GPIO_Pin_6); 
		            Generic_Short_Write_1P(0x93,str[3]);
		           
			          GPIO_SetBits(GPIOE,GPIO_Pin_6); 	
		
		            delay_ms(350);
								 
								 send_str[0] = 17;
								send_str[1] = 02;
								send_str[2] = str[2];
								send_str[3] = str[3];
								send_str[4] = str[4];
								send_str[5] = 160;
								send_str[6] = 00;
								send_str[7] = 00;
								send_str[8] = 01;    //send_finish
								send_str[9] = 00;   //finish
								send_str[10] = 187;
								
								sendID(send_str);
								
							
								break;
							 }
							case 63:
							{
								 	key_gamma_down(4);
						    delay_ms(1000);
								GPIO_ResetBits(GPIOE,GPIO_Pin_6); 
		            Generic_Short_Write_1P(0x9a,str[2]);
		            Generic_Short_Write_1P(0x9b,str[3]);
		            Generic_Long_Write_2P(0x82,str[4],str[4]);
			          GPIO_SetBits(GPIOE,GPIO_Pin_6); 	
		
		            delay_ms(350);
								 
								 send_str[0] = 17;
								send_str[1] = 02;
								send_str[2] = str[2];
								send_str[3] = str[3];
								send_str[4] = str[4];
								send_str[5] = 63;
								send_str[6] = 00;
								send_str[7] = 00;
								send_str[8] = 01;    //send_finish
								send_str[9] = 00;   //finish
								send_str[10] = 187;
								
								sendID(send_str);
							  	 break;
							}
							    
							 }
				   
  
						if(str[9] == 1)  //全部发送完成
						{
							       str[9] = 0;
						         key_gamma_down(10);
						         delay_ms(1000);
								 }
						str5 = 0;
			 }


void auto_gamma(unsigned char str5)
{
         
	          if(str5 == 0)
	          {
							 key_gamma_up(26);       //第255灰阶 
							//key_gamma_up(0);      //无fliker
	           delay_ms(1000);  
	          D1[1] = str[2];   //str5代表两个寄存器控制一个灰阶
	          D2[1] = str[2];
	          D3[1] = str[2];   //str5代表两个寄存器
	          D4[1] = str[2];   //str5代表两个寄存器
	          D5[1] = str[2];   //str5代表两个寄存器
	          D6[1] = str[2];   //str5代表两个寄存器 
		       
		        D1[2] = str[3];   //str5代表两个寄存器控制一个灰阶
	          D2[2] = str[3];
	          D3[2] = str[3];   //str5代表两个寄存器
	          D4[2] = str[3];   //str5代表两个寄存器
	          D5[2] = str[3];   //str5代表两个寄存器
	          D6[2] = str[3];   //str5代表两个寄存器
		       
		        send_9503Vgamma(str5);
				
	          }
	            if(str5 == 255)
	         {
	          	key_gamma_up(255);       //第255灰阶 
	            delay_ms(1000);  
	            D1[51] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[51] = str[2];
	            D3[51] = str[2];   //str5代表两个寄存器
	            D4[51] = str[2];   //str5代表两个寄存器
	            D5[51] = str[2];   //str5代表两个寄存器
	            D6[51] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[52] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[52] = str[3];
	            D3[52] = str[3];   //str5代表两个寄存器
	            D4[52] = str[3];   //str5代表两个寄存器
	            D5[52] = str[3];   //str5代表两个寄存器
	            D6[52] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
								
	        	}
	         
	        	  if(str5 == 1)
								{
                if(time == 0)
								{
									 key_gamma_up(28);       //第1灰阶
								 //key_gamma_up(2);       //无fliker
									 delay_ms(1000);
								}
							D1[3] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[3] = str[2];
	            D3[3] = str[2];   //str5代表两个寄存器
	            D4[3] = str[2];   //str5代表两个寄存器
	            D5[3] = str[2];   //str5代表两个寄存器
	            D6[3] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[4] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[4] = str[3];
	            D3[4] = str[3];   //str5代表两个寄存器
	            D4[4] = str[3];   //str5代表两个寄存器
	            D5[4] = str[3];   //str5代表两个寄存器
	            D6[4] = str[3];   //str5代表两个寄存器
	            send_9503Vgamma(str5);
							
				           time ++;		
	        	}
					 if(str5 == 3)   
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        		 {    		
								str[9] =0;												
							 	key_gamma_up(2);       //第3灰阶
								delay_ms(1000);
							
	        		 }
	            D1[5] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[5] = str[2];
	            D3[5] = str[2];   //str5代表两个寄存器
	            D4[5] = str[2];   //str5代表两个寄存器
	            D5[5] = str[2];   //str5代表两个寄存器
	            D6[5] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[6] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[6] = str[3];
	            D3[6] = str[3];   //str5代表两个寄存器
	            D4[6] = str[3];   //str5代表两个寄存器
	            D5[6] = str[3];   //str5代表两个寄存器
	            D6[6] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
												
	        	}
	            if(str5 == 5)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    	
										str[9] =0;												
										key_gamma_up(2);       //第5灰阶
									  delay_ms(1000);
	        			 }
	            D1[7] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[7] = str[2];
	            D3[7] = str[2];   //str5代表两个寄存器
	            D4[7] = str[2];   //str5代表两个寄存器
	            D5[7] = str[2];   //str5代表两个寄存器
	            D6[7] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[8] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[8] = str[3];
	            D3[8] = str[3];   //str5代表两个寄存器
	            D4[8] = str[3];   //str5代表两个寄存器
	            D5[8] = str[3];   //str5代表两个寄存器
	            D6[8] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
							
							
												
	        	}
	             if(str5 == 7)
	         {
                  if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    			
													str[9] =0;											
										 	key_gamma_up(2);       //第7灰阶
											delay_ms(1000);
	        			    }
	            D1[9] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[9] = str[2];
	            D3[9] = str[2];   //str5代表两个寄存器
	            D4[9] = str[2];   //str5代表两个寄存器
	            D5[9] = str[2];   //str5代表两个寄存器
	            D6[9] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[10] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[10] = str[3];
	            D3[10] = str[3];   //str5代表两个寄存器
	            D4[10] = str[3];   //str5代表两个寄存器
	            D5[10] = str[3];   //str5代表两个寄存器
	            D6[10] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
							
							
												
	        	}
	        		   if(str5 == 11)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			  {    				
									  str[9] =0;
									 	key_gamma_up(4);       //第7灰阶
										delay_ms(1000);
	        			  }
	            D1[11] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[11] = str[2];
	            D3[11] = str[2];   //str5代表两个寄存器
	            D4[11] = str[2];   //str5代表两个寄存器
	            D5[11] = str[2];   //str5代表两个寄存器
	            D6[11] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[12] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[12] = str[3];
	            D3[12] = str[3];   //str5代表两个寄存器
	            D4[12] = str[3];   //str5代表两个寄存器
	            D5[12] = str[3];   //str5代表两个寄存器
	            D6[12] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);							
												
	        	}			
					    if(str5 == 15)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			  {    				
										 str[9] =0;
										 key_gamma_up(4);       //第7灰阶
										 delay_ms(1000);
	        			  }
	            D1[13] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[13] = str[2];
	            D3[13] = str[2];   //str5代表两个寄存器
	            D4[13] = str[2];   //str5代表两个寄存器
	            D5[13] = str[2];   //str5代表两个寄存器
	            D6[13] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[14] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[14] = str[3];
	            D3[14] = str[3];   //str5代表两个寄存器
	            D4[14] = str[3];   //str5代表两个寄存器
	            D5[14] = str[3];   //str5代表两个寄存器
	            D6[14] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
													
	        	}			
          
						 if(str5 == 23)
	         {
                if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    
									str[9] =0;												
								 	key_gamma_up(8);       //第7灰阶
									delay_ms(1000);
	        			 }
	            D1[15] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[15] = str[2];
	            D3[15] = str[2];   //str5代表两个寄存器
	            D4[15] = str[2];   //str5代表两个寄存器
	            D5[15] = str[2];   //str5代表两个寄存器
	            D6[15] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[16] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[16] = str[3];
	            D3[16] = str[3];   //str5代表两个寄存器
	            D4[16] = str[3];   //str5代表两个寄存器
	            D5[16] = str[3];   //str5代表两个寄存器
	            D6[16] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
							
					
	        	}		
					  if(str5 == 31)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    	
								  str[9] =0;												
									key_gamma_up(8);       //第7灰阶
							   	delay_ms(1000);
	        			 }
	            D1[17] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[17] = str[2];
	            D3[17] = str[2];   //str5代表两个寄存器
	            D4[17] = str[2];   //str5代表两个寄存器
	            D5[17] = str[2];   //str5代表两个寄存器
	            D6[17] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[18] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[18] = str[3];
	            D3[18] = str[3];   //str5代表两个寄存器
	            D4[18] = str[3];   //str5代表两个寄存器
	            D5[18] = str[3];   //str5代表两个寄存器
	            D6[18] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
																				
	        	}		
						  if(str5 == 47)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    
									str[9] =0;												
								 	key_gamma_up(16);       //第7灰阶
									delay_ms(1000);
	        			 }		
	            D1[19] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[19] = str[2];
	            D3[19] = str[2];   //str5代表两个寄存器
	            D4[19] = str[2];   //str5代表两个寄存器
	            D5[19] = str[2];   //str5代表两个寄存器
	            D6[19] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[20] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[20] = str[3];
	            D3[20] = str[3];   //str5代表两个寄存器
	            D4[20] = str[3];   //str5代表两个寄存器
	            D5[20] = str[3];   //str5代表两个寄存器
	            D6[20] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
							
														
	        	}		
					 
							  if(str5 == 63)
	         {
               if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
											str[9] =0;												
										 	key_gamma_up(16);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            D1[21] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[21] = str[2];
	            D3[21] = str[2];   //str5代表两个寄存器
	            D4[21] = str[2];   //str5代表两个寄存器
	            D5[21] = str[2];   //str5代表两个寄存器
	            D6[21] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[22] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[22] = str[3];
	            D3[22] = str[3];   //str5代表两个寄存器
	            D4[22] = str[3];   //str5代表两个寄存器
	            D5[22] = str[3];   //str5代表两个寄存器
	            D6[22] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
															
	        	}		
					 
						  if(str5 == 95)
	         {
                if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
													str[9] =0;												
										 	key_gamma_up(32);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            D1[23] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[23] = str[2];
	            D3[23] = str[2];   //str5代表两个寄存器
	            D4[23] = str[2];   //str5代表两个寄存器
	            D5[23] = str[2];   //str5代表两个寄存器
	            D6[23] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[24] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[24] = str[3];
	            D3[24] = str[3];   //str5代表两个寄存器
	            D4[24] = str[3];   //str5代表两个寄存器
	            D5[24] = str[3];   //str5代表两个寄存器
	            D6[24] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
							
															
	        	}		
					 
						  if(str5 == 127)
	         {
            if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    
													str[9] =0;	
											
										 	key_gamma_up(32);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            D1[25] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[25] = str[2];
	            D3[25] = str[2];   //str5代表两个寄存器
	            D4[25] = str[2];   //str5代表两个寄存器
	            D5[25] = str[2];   //str5代表两个寄存器
	            D6[25] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[26] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[26] = str[3];
	            D3[26] = str[3];   //str5代表两个寄存器
	            D4[26] = str[3];   //str5代表两个寄存器
	            D5[26] = str[3];   //str5代表两个寄存器
	            D6[26] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
							
															
	        	}		
	        		
						if(str5 == 128)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(1);       //第7灰阶
											delay_ms(1000);
	        			    }			
	            D1[27] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[27] = str[2];
	            D3[27] = str[2];   //str5代表两个寄存器
	            D4[27] = str[2];   //str5代表两个寄存器
	            D5[27] = str[2];   //str5代表两个寄存器
	            D6[27] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[28] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[28] = str[3];
	            D3[28] = str[3];   //str5代表两个寄存器
	            D4[28] = str[3];   //str5代表两个寄存器
	            D5[28] = str[3];   //str5代表两个寄存器
	            D6[28] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
							
													
	        	}								
					 if(str5 == 160)
	         {
            if(str[9] == 1)  //上一个灰阶比较完成
	        		{    			
									str[9] =0;												
								 	key_gamma_up(32);       //第7灰阶
									delay_ms(1000);
	        	  }				
	            D1[29] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[29] = str[2];
	            D3[29] = str[2];   //str5代表两个寄存器
	            D4[29] = str[2];   //str5代表两个寄存器
	            D5[29] = str[2];   //str5代表两个寄存器
	            D6[29] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[30] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[30] = str[3];
	            D3[30] = str[3];   //str5代表两个寄存器
	            D4[30] = str[3];   //str5代表两个寄存器
	            D5[30] = str[3];   //str5代表两个寄存器
	            D6[30] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
							
												
	        	}		

					 if(str5 == 192)
	         {
            if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
													str[9] =0;												
										 	key_gamma_up(32);       //第7灰阶
											delay_ms(1000);
	        			    }		
	            D1[31] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[31] = str[2];
	            D3[31] = str[2];   //str5代表两个寄存器
	            D4[31] = str[2];   //str5代表两个寄存器
	            D5[31] = str[2];   //str5代表两个寄存器
	            D6[31] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[32] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[32] = str[3];
	            D3[32] = str[3];   //str5代表两个寄存器
	            D4[32] = str[3];   //str5代表两个寄存器
	            D5[32] = str[3];   //str5代表两个寄存器
	            D6[32] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
														
	        	}			

            if(str5 == 208)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(16);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            D1[33] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[33] = str[2];
	            D3[33] = str[2];   //str5代表两个寄存器
	            D4[33] = str[2];   //str5代表两个寄存器
	            D5[33] = str[2];   //str5代表两个寄存器
	            D6[33] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[34] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[34] = str[3];
	            D3[34] = str[3];   //str5代表两个寄存器
	            D4[34] = str[3];   //str5代表两个寄存器
	            D5[34] = str[3];   //str5代表两个寄存器
	            D6[34] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
															
	        	}					

          if(str5 == 224)    ////////////////////////////////////////////////////////
	         {
             if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    			
													str[9] =0;												
										 	key_gamma_up(16);       //第7灰阶
											delay_ms(1000);
	        			    }					
	            D1[35] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[35] = str[2];
	            D3[35] = str[2];   //str5代表两个寄存器
	            D4[35] = str[2];   //str5代表两个寄存器
	            D5[35] = str[2];   //str5代表两个寄存器
	            D6[35] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[36] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[36] = str[3];
	            D3[36] = str[3];   //str5代表两个寄存器
	            D4[36] = str[3];   //str5代表两个寄存器
	            D5[36] = str[3];   //str5代表两个寄存器
	            D6[36] = str[3];   //str5代表两个寄存器
	        	
	        	send_9503Vgamma(str5);
							
											
	        	}			

            if(str5 == 232)
	         {
             if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(8);       //第7灰阶
											delay_ms(1000);
	        			    }									
	            D1[37] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[37] = str[2];
	            D3[37] = str[2];   //str5代表两个寄存器
	            D4[37] = str[2];   //str5代表两个寄存器
	            D5[37] = str[2];   //str5代表两个寄存器
	            D6[37] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[38] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[38] = str[3];
	            D3[38] = str[3];   //str5代表两个寄存器
	            D4[38] = str[3];   //str5代表两个寄存器
	            D5[38] = str[3];   //str5代表两个寄存器
	            D6[38] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
							
	        	}									
						
						    if(str5 == 240)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    
													str[9] =0;												
										 	key_gamma_up(8);       //第7灰阶
											delay_ms(1000);
	        			    }						
										
	            D1[39] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[39] = str[2];
	            D3[39] = str[2];   //str5代表两个寄存器
	            D4[39] = str[2];   //str5代表两个寄存器
	            D5[39] = str[2];   //str5代表两个寄存器
	            D6[39] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[40] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[40] = str[3];
	            D3[40] = str[3];   //str5代表两个寄存器
	            D4[40] = str[3];   //str5代表两个寄存器
	            D5[40] = str[3];   //str5代表两个寄存器
	            D6[40] = str[3];   //str5代表两个寄存器
	        	
	        	send_9503Vgamma(str5);
							
										
	        	}			
					 
										    if(str5 == 244)
	         {
             	if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    			
													str[9] =0;												
										 	key_gamma_up(4);       //第7灰阶
											delay_ms(1000);
	        			    }					
	            D1[41] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[41] = str[2];
	            D3[41] = str[2];   //str5代表两个寄存器
	            D4[41] = str[2];   //str5代表两个寄存器
	            D5[41] = str[2];   //str5代表两个寄存器
	            D6[41] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[42] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[42] = str[3];
	            D3[42] = str[3];   //str5代表两个寄存器
	            D4[42] = str[3];   //str5代表两个寄存器
	            D5[42] = str[3];   //str5代表两个寄存器
	            D6[42] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
	        	}		
					 
								 if(str5 == 248)
	         {
              	if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(4);       //第7灰阶
											delay_ms(1000);
	        			    }									
	            D1[43] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[43] = str[2];
	            D3[43] = str[2];   //str5代表两个寄存器
	            D4[43] = str[2];   //str5代表两个寄存器
	            D5[43] = str[2];   //str5代表两个寄存器
	            D6[43] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[44] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[44] = str[3];
	            D3[44] = str[3];   //str5代表两个寄存器
	            D4[44] = str[3];   //str5代表两个寄存器
	            D5[44] = str[3];   //str5代表两个寄存器
	            D6[44] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
	        	}		
					 
						if(str5 == 250)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
													str[9] =0;												
										 	key_gamma_up(2);       //第7灰阶
											delay_ms(1000);
	        			    }				
										
	            D1[45] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[45] = str[2];
	            D3[45] = str[2];   //str5代表两个寄存器
	            D4[45] = str[2];   //str5代表两个寄存器
	            D5[45] = str[2];   //str5代表两个寄存器
	            D6[45] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[46] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[46] = str[3];
	            D3[46] = str[3];   //str5代表两个寄存器
	            D4[46] = str[3];   //str5代表两个寄存器
	            D5[46] = str[3];   //str5代表两个寄存器
	            D6[46] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
	        	}		
					 
					if(str5 == 252)
	         { 
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(2);       //第7灰阶
											delay_ms(1000);
	        			    }						
										
	            D1[47] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[47] = str[2];
	            D3[47] = str[2];   //str5代表两个寄存器
	            D4[47] = str[2];   //str5代表两个寄存器
	            D5[47] = str[2];   //str5代表两个寄存器
	            D6[47] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[48] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[48] = str[3];
	            D3[48] = str[3];   //str5代表两个寄存器
	            D4[48] = str[3];   //str5代表两个寄存器
	            D5[48] = str[3];   //str5代表两个寄存器
	            D6[48] = str[3];   //str5代表两个寄存器
	        	
	        	send_9503Vgamma(str5);
										
	        	}		
					 
			    if(str5 == 254)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
													str[9] =0;												
										 	key_gamma_up(2);       //第7灰阶
											delay_ms(1000);
	        			    }					
										
	            D1[49] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[49] = str[2];
	            D3[49] = str[2];   //str5代表两个寄存器
	            D4[49] = str[2];   //str5代表两个寄存器
	            D5[49] = str[2];   //str5代表两个寄存器
	            D6[49] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[50] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[50] = str[3];
	            D3[50] = str[3];   //str5代表两个寄存器
	            D4[50] = str[3];   //str5代表两个寄存器
	            D5[50] = str[3];   //str5代表两个寄存器
	            D6[50] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
											
	        	}		
					 
				
							 
				
					 
		
				
						
}


void auto_gamma2(unsigned char str5)
{

					 
					 	          if(str5 == 0)
	          {
						
	           key_gamma_up(26);       //第255灰阶 
							//key_gamma_up(0);       //无fliker
							
	           delay_ms(1000);  
	          D1[51] = str[2];   //str5代表两个寄存器控制一个灰阶
	          D2[51] = str[2];
	          D3[51] = str[2];   //str5代表两个寄存器
	          D4[51] = str[2];   //str5代表两个寄存器
	          D5[51] = str[2];   //str5代表两个寄存器
	          D6[51] = str[2];   //str5代表两个寄存器 
		       
		        D1[52] = str[3];   //str5代表两个寄存器控制一个灰阶
	          D2[52] = str[3];
	          D3[52] = str[3];   //str5代表两个寄存器
	          D4[52] = str[3];   //str5代表两个寄存器
	          D5[52] = str[3];   //str5代表两个寄存器
	          D6[52] = str[3];   //str5代表两个寄存器
		       
		       send_9503Vgamma(str5);
				
	          }
	            if(str5 == 255)
	         {
	          	key_gamma_up(255);       //第255灰阶 
	            delay_ms(1000);  
	            D1[1] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[1] = str[2];
	            D3[1] = str[2];   //str5代表两个寄存器
	            D4[1] = str[2];   //str5代表两个寄存器
	            D5[1] = str[2];   //str5代表两个寄存器
	            D6[1] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[2] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[2] = str[3];
	            D3[2] = str[3];   //str5代表两个寄存器
	            D4[2] = str[3];   //str5代表两个寄存器
	            D5[2] = str[3];   //str5代表两个寄存器
	            D6[2] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
								
	        	}
	         
	        	  if(str5 == 1)
								{
                if(time == 0)
								{
									 key_gamma_up(28);       //第1灰阶
								//	key_gamma_up(2);       //无fliker
									 delay_ms(1000);
								}
							     
	                 D1[49] = str[2];   //str5代表两个寄存器控制一个灰阶
	                 D2[49] = str[2];
	                 D3[49] = str[2];   //str5代表两个寄存器
	                 D4[49] = str[2];   //str5代表两个寄存器
	                 D5[49] = str[2];   //str5代表两个寄存器
	                 D6[49] = str[2];   //str5代表两个寄存器 
	        	       
	        	       D1[50] = str[3];   //str5代表两个寄存器控制一个灰阶
	                 D2[50] = str[3];
	                 D3[50] = str[3];   //str5代表两个寄存器
	                 D4[50] = str[3];   //str5代表两个寄存器
	                 D5[50] = str[3];   //str5代表两个寄存器
	                 D6[50] = str[3];   //str5代表两个寄存器
	        	
	        	       send_9503Vgamma(str5);
							
				           time ++;		
	        	}
					 if(str5 == 3)   
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        		 {    		
								str[9] =0;												
							 	key_gamma_up(2);       //第3灰阶
								delay_ms(1000);
							
	        		 }
	            D1[47] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[47] = str[2];
	            D3[47] = str[2];   //str5代表两个寄存器
	            D4[47] = str[2];   //str5代表两个寄存器
	            D5[47] = str[2];   //str5代表两个寄存器
	            D6[47] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[48] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[48] = str[3];
	            D3[48] = str[3];   //str5代表两个寄存器
	            D4[48] = str[3];   //str5代表两个寄存器
	            D5[48] = str[3];   //str5代表两个寄存器
	            D6[48] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
												
	        	}
	            if(str5 == 5)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    	
										str[9] =0;												
										key_gamma_up(2);       //第5灰阶
									  delay_ms(1000);
	        			 }
	            D1[45] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[45] = str[2];
	            D3[45] = str[2];   //str5代表两个寄存器
	            D4[45] = str[2];   //str5代表两个寄存器
	            D5[45] = str[2];   //str5代表两个寄存器
	            D6[45] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[46] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[46] = str[3];
	            D3[46] = str[3];   //str5代表两个寄存器
	            D4[46] = str[3];   //str5代表两个寄存器
	            D5[46] = str[3];   //str5代表两个寄存器
	            D6[46] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
							
							
												
	        	}
	             if(str5 == 7)
	         {
                  if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    			
													str[9] =0;											
										 	key_gamma_up(2);       //第7灰阶
											delay_ms(1000);
	        			    }
	            D1[43] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[43] = str[2];
	            D3[43] = str[2];   //str5代表两个寄存器
	            D4[43] = str[2];   //str5代表两个寄存器
	            D5[43] = str[2];   //str5代表两个寄存器
	            D6[43] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[44] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[44] = str[3];
	            D3[44] = str[3];   //str5代表两个寄存器
	            D4[44] = str[3];   //str5代表两个寄存器
	            D5[44] = str[3];   //str5代表两个寄存器
	            D6[44] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
							
												
	        	}
	        		   if(str5 == 11)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			  {    				
									  str[9] =0;
									 	key_gamma_up(4);       //第7灰阶
										delay_ms(1000);
	        			  }
	            D1[41] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[41] = str[2];
	            D3[41] = str[2];   //str5代表两个寄存器
	            D4[41] = str[2];   //str5代表两个寄存器
	            D5[41] = str[2];   //str5代表两个寄存器
	            D6[41] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[42] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[42] = str[3];
	            D3[42] = str[3];   //str5代表两个寄存器
	            D4[42] = str[3];   //str5代表两个寄存器
	            D5[42] = str[3];   //str5代表两个寄存器
	            D6[42] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);						
												
	        	}			
					    if(str5 == 15)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			  {    				
										 str[9] =0;
										 key_gamma_up(4);       //第7灰阶
										 delay_ms(1000);
	        			  }
	            D1[39] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[39] = str[2];
	            D3[39] = str[2];   //str5代表两个寄存器
	            D4[39] = str[2];   //str5代表两个寄存器
	            D5[39] = str[2];   //str5代表两个寄存器
	            D6[39] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[40] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[40] = str[3];
	            D3[40] = str[3];   //str5代表两个寄存器
	            D4[40] = str[3];   //str5代表两个寄存器
	            D5[40] = str[3];   //str5代表两个寄存器
	            D6[40] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
													
	        	}			
          
						 if(str5 == 23)
	         {
                if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    
									str[9] =0;												
								 	key_gamma_up(8);       //第7灰阶
									delay_ms(1000);
	        			 }
	            D1[37] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[37] = str[2];
	            D3[37] = str[2];   //str5代表两个寄存器
	            D4[37] = str[2];   //str5代表两个寄存器
	            D5[37] = str[2];   //str5代表两个寄存器
	            D6[37] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[38] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[38] = str[3];
	            D3[38] = str[3];   //str5代表两个寄存器
	            D4[38] = str[3];   //str5代表两个寄存器
	            D5[38] = str[3];   //str5代表两个寄存器
	            D6[38] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
					
	        	}		
					  if(str5 == 31)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    	
								  str[9] =0;												
									key_gamma_up(8);       //第7灰阶
							   	delay_ms(1000);
	        			 }
	            D1[35] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[35] = str[2];
	            D3[35] = str[2];   //str5代表两个寄存器
	            D4[35] = str[2];   //str5代表两个寄存器
	            D5[35] = str[2];   //str5代表两个寄存器
	            D6[35] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[36] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[36] = str[3];
	            D3[36] = str[3];   //str5代表两个寄存器
	            D4[36] = str[3];   //str5代表两个寄存器
	            D5[36] = str[3];   //str5代表两个寄存器
	            D6[36] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
																				
	        	}		
						  if(str5 == 47)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    
									str[9] =0;												
								 	key_gamma_up(16);       //第7灰阶
									delay_ms(1000);
	        			 }		
	            D1[33] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[33] = str[2];
	            D3[33] = str[2];   //str5代表两个寄存器
	            D4[33] = str[2];   //str5代表两个寄存器
	            D5[33] = str[2];   //str5代表两个寄存器
	            D6[33] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[34] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[34] = str[3];
	            D3[34] = str[3];   //str5代表两个寄存器
	            D4[34] = str[3];   //str5代表两个寄存器
	            D5[34] = str[3];   //str5代表两个寄存器
	            D6[34] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
														
	        	}		
					 
							  if(str5 == 63)
	         {
               if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
											str[9] =0;												
										 	key_gamma_up(16);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            D1[31] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[31] = str[2];
	            D3[31] = str[2];   //str5代表两个寄存器
	            D4[31] = str[2];   //str5代表两个寄存器
	            D5[31] = str[2];   //str5代表两个寄存器
	            D6[31] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[32] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[32] = str[3];
	            D3[32] = str[3];   //str5代表两个寄存器
	            D4[32] = str[3];   //str5代表两个寄存器
	            D5[32] = str[3];   //str5代表两个寄存器
	            D6[32] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
							
															
	        	}		
					 
						  if(str5 == 95)
	         {
                if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
													str[9] =0;												
										 	key_gamma_up(32);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            D1[29] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[29] = str[2];
	            D3[29] = str[2];   //str5代表两个寄存器
	            D4[29] = str[2];   //str5代表两个寄存器
	            D5[29] = str[2];   //str5代表两个寄存器
	            D6[29] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[30] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[30] = str[3];
	            D3[30] = str[3];   //str5代表两个寄存器
	            D4[30] = str[3];   //str5代表两个寄存器
	            D5[30] = str[3];   //str5代表两个寄存器
	            D6[30] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
															
	        	}		
					 
						  if(str5 == 127)
	         {
            if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    
													str[9] =0;	
											
										 	key_gamma_up(32);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            D1[27] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[27] = str[2];
	            D3[27] = str[2];   //str5代表两个寄存器
	            D4[27] = str[2];   //str5代表两个寄存器
	            D5[27] = str[2];   //str5代表两个寄存器
	            D6[27] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[28] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[28] = str[3];
	            D3[28] = str[3];   //str5代表两个寄存器
	            D4[28] = str[3];   //str5代表两个寄存器
	            D5[28] = str[3];   //str5代表两个寄存器
	            D6[28] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
															
	        	}		
	        		
						if(str5 == 128)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(1);       //第7灰阶
											delay_ms(1000);
	        			    }			
	            D1[25] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[25] = str[2];
	            D3[25] = str[2];   //str5代表两个寄存器
	            D4[25] = str[2];   //str5代表两个寄存器
	            D5[25] = str[2];   //str5代表两个寄存器
	            D6[25] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[26] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[26] = str[3];
	            D3[26] = str[3];   //str5代表两个寄存器
	            D4[26] = str[3];   //str5代表两个寄存器
	            D5[26] = str[3];   //str5代表两个寄存器
	            D6[26] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
													
	        	}								
					 if(str5 == 160)
	         {
            if(str[9] == 1)  //上一个灰阶比较完成
	        		{    			
									str[9] =0;												
								 	key_gamma_up(32);       //第7灰阶
									delay_ms(1000);
	        	  }				
	            D1[23] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[23] = str[2];
	            D3[23] = str[2];   //str5代表两个寄存器
	            D4[23] = str[2];   //str5代表两个寄存器
	            D5[23] = str[2];   //str5代表两个寄存器
	            D6[23] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[24] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[24] = str[3];
	            D3[24] = str[3];   //str5代表两个寄存器
	            D4[24] = str[3];   //str5代表两个寄存器
	            D5[24] = str[3];   //str5代表两个寄存器
	            D6[24] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
												
	        	}		

					 if(str5 == 192)
	         {
            if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
													str[9] =0;												
										 	key_gamma_up(32);       //第7灰阶
											delay_ms(1000);
	        			    }		
	            D1[21] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[21] = str[2];
	            D3[21] = str[2];   //str5代表两个寄存器
	            D4[21] = str[2];   //str5代表两个寄存器
	            D5[21] = str[2];   //str5代表两个寄存器
	            D6[21] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[22] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[22] = str[3];
	            D3[22] = str[3];   //str5代表两个寄存器
	            D4[22] = str[3];   //str5代表两个寄存器
	            D5[22] = str[3];   //str5代表两个寄存器
	            D6[22] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
														
	        	}			

            if(str5 == 208)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(16);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            D1[19] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[19] = str[2];
	            D3[19] = str[2];   //str5代表两个寄存器
	            D4[19] = str[2];   //str5代表两个寄存器
	            D5[19] = str[2];   //str5代表两个寄存器
	            D6[19] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[20] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[20] = str[3];
	            D3[20] = str[3];   //str5代表两个寄存器
	            D4[20] = str[3];   //str5代表两个寄存器
	            D5[20] = str[3];   //str5代表两个寄存器
	            D6[20] = str[3];   //str5代表两个寄存器
	        	
	        	send_9503Vgamma(str5);
															
	        	}					

          if(str5 == 224)    ////////////////////////////////////////////////////////
	         {
             if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    			
													str[9] =0;												
										 	key_gamma_up(16);       //第7灰阶
											delay_ms(1000);
	        			    }					
	            D1[17] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[17] = str[2];
	            D3[17] = str[2];   //str5代表两个寄存器
	            D4[17] = str[2];   //str5代表两个寄存器
	            D5[17] = str[2];   //str5代表两个寄存器
	            D6[17] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[18] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[18] = str[3];
	            D3[18] = str[3];   //str5代表两个寄存器
	            D4[18] = str[3];   //str5代表两个寄存器
	            D5[18] = str[3];   //str5代表两个寄存器
	            D6[18] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
											
	        	}			

            if(str5 == 232)
	         {
             if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(8);       //第7灰阶
											delay_ms(1000);
	        			    }									
	            D1[15] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[15] = str[2];
	            D3[15] = str[2];   //str5代表两个寄存器
	            D4[15] = str[2];   //str5代表两个寄存器
	            D5[15] = str[2];   //str5代表两个寄存器
	            D6[15] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[16] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[16] = str[3];
	            D3[16] = str[3];   //str5代表两个寄存器
	            D4[16] = str[3];   //str5代表两个寄存器
	            D5[16] = str[3];   //str5代表两个寄存器
	            D6[16] = str[3];   //str5代表两个寄存器
	        	
	        	send_9503Vgamma(str5);
	        	}									
						
						    if(str5 == 240)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    
													str[9] =0;												
										 	key_gamma_up(8);       //第7灰阶
											delay_ms(1000);
	        			    }						
										
	            D1[13] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[13] = str[2];
	            D3[13] = str[2];   //str5代表两个寄存器
	            D4[13] = str[2];   //str5代表两个寄存器
	            D5[13] = str[2];   //str5代表两个寄存器
	            D6[13] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[14] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[14] = str[3];
	            D3[14] = str[3];   //str5代表两个寄存器
	            D4[14] = str[3];   //str5代表两个寄存器
	            D5[14] = str[3];   //str5代表两个寄存器
	            D6[14] = str[3];   //str5代表两个寄存器
	        	
	        	send_9503Vgamma(str5);
	        	}			
					 
										    if(str5 == 244)
	         {
             	if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    			
													str[9] =0;												
										 	key_gamma_up(4);       //第7灰阶
											delay_ms(1000);
	        			    }					
	            D1[11] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[11] = str[2];
	            D3[11] = str[2];   //str5代表两个寄存器
	            D4[11] = str[2];   //str5代表两个寄存器
	            D5[11] = str[2];   //str5代表两个寄存器
	            D6[11] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[12] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[12] = str[3];
	            D3[12] = str[3];   //str5代表两个寄存器
	            D4[12] = str[3];   //str5代表两个寄存器
	            D5[12] = str[3];   //str5代表两个寄存器
	            D6[12] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
										
	        	}		
					 
								 if(str5 == 248)
	         {
              	if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(4);       //第7灰阶
											delay_ms(1000);
	        			    }									
	            D1[9] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[9] = str[2];
	            D3[9] = str[2];   //str5代表两个寄存器
	            D4[9] = str[2];   //str5代表两个寄存器
	            D5[9] = str[2];   //str5代表两个寄存器
	            D6[9] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[10] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[10] = str[3];
	            D3[10] = str[3];   //str5代表两个寄存器
	            D4[10] = str[3];   //str5代表两个寄存器
	            D5[10] = str[3];   //str5代表两个寄存器
	            D6[10] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
						
	        	}		
					 
						if(str5 == 250)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
													str[9] =0;												
										 	key_gamma_up(2);       //第7灰阶
											delay_ms(1000);
	        			    }				
										
	            D1[7] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[7] = str[2];
	            D3[7] = str[2];   //str5代表两个寄存器
	            D4[7] = str[2];   //str5代表两个寄存器
	            D5[7] = str[2];   //str5代表两个寄存器
	            D6[7] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[8] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[8] = str[3];
	            D3[8] = str[3];   //str5代表两个寄存器
	            D4[8] = str[3];   //str5代表两个寄存器
	            D5[8] = str[3];   //str5代表两个寄存器
	            D6[8] = str[3];   //str5代表两个寄存器
	        	
	        	 send_9503Vgamma(str5);
	        	}		
					 
					if(str5 == 252)
	         { 
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(2);       //第7灰阶
											delay_ms(1000);
	        			    }						
										
	            D1[5] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[5] = str[2];
	            D3[5] = str[2];   //str5代表两个寄存器
	            D4[5] = str[2];   //str5代表两个寄存器
	            D5[5] = str[2];   //str5代表两个寄存器
	            D6[5] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[6] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[6] = str[3];
	            D3[6] = str[3];   //str5代表两个寄存器
	            D4[6] = str[3];   //str5代表两个寄存器
	            D5[6] = str[3];   //str5代表两个寄存器
	            D6[6] = str[3];   //str5代表两个寄存器
	        	
	        	send_9503Vgamma(str5);
										
	        	}		
					 
			    if(str5 == 254)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
													str[9] =0;												
										 	key_gamma_up(2);       //第7灰阶
											delay_ms(1000);
	        			    }					
										
	            D1[3] = str[2];   //str5代表两个寄存器控制一个灰阶
	            D2[3] = str[2];
	            D3[3] = str[2];   //str5代表两个寄存器
	            D4[3] = str[2];   //str5代表两个寄存器
	            D5[3] = str[2];   //str5代表两个寄存器
	            D6[3] = str[2];   //str5代表两个寄存器 
	        	
	        	  D1[4] = str[3];   //str5代表两个寄存器控制一个灰阶
	            D2[4] = str[3];
	            D3[4] = str[3];   //str5代表两个寄存器
	            D4[4] = str[3];   //str5代表两个寄存器
	            D5[4] = str[3];   //str5代表两个寄存器
	            D6[4] = str[3];   //str5代表两个寄存器
	        	
	        	  send_9503Vgamma(str5);
											
	        	}		
					 


}

