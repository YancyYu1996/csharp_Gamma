#include "9702gamma.h"
#include "gamma.h"
#include "spi.h"
#include "stdlib.h"	
#include "usart.h"
#include "key.h"
#include "delay.h"

extern u8 str[11];//接收到的数据
extern u8 gray_number[26];
extern u8 send_str[11];
//                      v0        v1       v3        v5        v7       v11       v15       v23        v31       v47       v63       v95      v127       v128     v160      v192      v208      v224      v232      v240      v244     v248      v250      v252     v254       v255 
u8 F1[20] ={0xF1,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8 F2[20] ={0xF2,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

 unsigned char reg_93;
extern u8 time;	
	void send_9702DC(unsigned char cmd,unsigned char data,unsigned char str5)
	{
	  GPIO_ResetBits(GPIOE,GPIO_Pin_6); 
	 
	SPI_WriteComm(0x00b7);
	SPI_WriteData(0x0550);
	delay_ms(10);

	delay_ms(100);
	
	 Generic_Long_Write_3P(0xD5,0x61,0x74,0x97);
   Generic_Short_Write_1P(0xD0,0x10);
  		 
  Generic_Short_Write_1P(cmd,data);

	
  Generic_Short_Write_1P(0xFF,0xFF);//VCOM 88
  Generic_Short_Write_1P(0xFF,0xFF);//VCOM 88
  Generic_Short_Write_1P(0xFF,0xFF);//VCOM 88
  Generic_Short_Write_1P(0xFF,0xFF);//VCOM 88
  Generic_Short_Write_1P(0xFF,0xFF);//VCOM 88
		
	delay_ms(100);
	
	SPI_WriteComm(0x00b7);
	SPI_WriteData(0x0159);
	
	delay_ms(10);
		 
	 GPIO_SetBits(GPIOE,GPIO_Pin_6); 
	 
	 delay_ms(300);
		              send_str[0] = 17;
		              send_str[1] = 02;
		              send_str[2] = data;
		              send_str[3] = 00;
		              send_str[4] = 00;
		              send_str[5] = str5;
		              send_str[6] = 00;
		              send_str[7] = 00;
		              send_str[8] = 01;    //send_finish
		              send_str[9] = 00;   //finish
		              send_str[10] = 187;
		              
		              sendID(send_str);	 
	
	}
	
	void send_9702array(unsigned char array1[],unsigned char array2[],char str5)
	{
	  GPIO_ResetBits(GPIOE,GPIO_Pin_6); 
	 
	SPI_WriteComm(0x00b7);
	SPI_WriteData(0x0550);
	delay_ms(10);

	delay_ms(100);
	
	 Generic_Long_Write_3P(0xD5,0x61,0x74,0x97);
   Generic_Short_Write_1P(0xD0,0x11);
  		 
 Generic_Long_Write_FIFO(20,array1);Generic_Long_Write_FIFO(20,array2);

	
  Generic_Short_Write_1P(0xFF,0xFF);//VCOM 88
  Generic_Short_Write_1P(0xFF,0xFF);//VCOM 88
  Generic_Short_Write_1P(0xFF,0xFF);//VCOM 88
  Generic_Short_Write_1P(0xFF,0xFF);//VCOM 88
  Generic_Short_Write_1P(0xFF,0xFF);//VCOM 88
		
	delay_ms(100);
	
	SPI_WriteComm(0x00b7);
	SPI_WriteData(0x0159);
	
	delay_ms(10);
		 
	 GPIO_SetBits(GPIOE,GPIO_Pin_6); 
	 
	  delay_ms(400);
	        		     send_str[0] = 17;
	        	       send_str[1] = 03;
	        	       send_str[4] = 00;
	        	       send_str[5] = str5;//灰阶
	        	       send_str[6] = 00;
	        	       send_str[7] = 00;
	        	       send_str[8] = 01;//finish
	        	       send_str[9] = 00;   
	        	       send_str[10] = 187;
	        	       sendID(send_str);
	
	}
	
void auto_9702fliker(unsigned char str5)
{
	 switch(str5)
							 {
							 case 63:
							 {		
								  if(reg_93 == 0)
								 {
							    key_gamma_up(26+256);
								  delay_ms(1000);
								 }
								  
								  send_9702DC(0x93,reg_93,str5);	
		
		             
                  if(reg_93 < 255)								 
		                reg_93++;
									else 
										reg_93 = 0;
								 break;
							 }
               case 128:								 
							 {
								 if(reg_93 == 0)
								 {
							    key_gamma_up(1);
								  delay_ms(1000);
								 }
								 
								 send_9702DC(0x93,reg_93,str5);	
			                     	   
                  if(reg_93 < 255)								 
		                reg_93++;
									else 
										reg_93 = 0;
								 break;
													
							 }
							case 160:
							{
								  if(reg_93 == 0)
								 {
							    key_gamma_up(1);
								  delay_ms(1000);
								 }
								 
								 send_9702DC(0x93,reg_93,str5);	
  
                  if(reg_93 < 255)								 
		                reg_93++;
									else 
										reg_93 = 0;
								 break;
							}
						}
					}

void auto_gamma3(unsigned char str5)
{

					 
					 	          if(str5 == 0)
	          {
						
	           key_gamma_up(26);       //第0灰阶 
							//key_gamma_up(0);       //无fliker
							
	           delay_ms(1000);  
	          F1[19] = str[2];   //str5代表两个寄存器控制一个灰阶
	           F2[19] = str[2]; 
							
		        send_9702array(F1,F2,str5);
							
				
	          }
	            if(str5 == 255)
	         {
	          	key_gamma_up(255);       //第255灰阶 
	            delay_ms(1000);  
	            F1[1] = str[2];   //str5代表两个寄存器控制一个灰阶
	            F2[1] = str[2];
	         
	        	
	        	  send_9702array(F1,F2,str5);
							
	        	 
								
	        	}
	         
	        	  if(str5 == 4)
								{
                if(time == 0)
								{
									 key_gamma_up(31);       //第1灰阶
									 //key_gamma_up(2);       //无fliker
									 delay_ms(1000);
								}
							     
	                 F1[18] = str[2];   //str5代表两个寄存器控制一个灰阶
	                 F2[18] = str[2];
	        	
	        	     send_9702array(F1,F2,str5);
							
	        		   
							
				           time ++;		
	        	}
					 if(str5 == 8)   
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        		 {    		
								str[9] =0;												
							 	key_gamma_up(4);       //第8灰阶
								delay_ms(1000);
							
	        		 }
	            F1[17] = str[2];   //str5代表两个寄存器控制一个灰阶
              F2[17] = str[2];   //str5代表两个寄存器控制一个灰阶 
	           send_9702array(F1,F2,str5);

												
	        	}
					 
	            if(str5 == 12)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    	
										str[9] =0;												
										key_gamma_up(4);       //第5灰阶
									  delay_ms(1000);
	        			 }
	            F1[16] = str[2];   //str5代表两个寄存器控制一个灰阶
	         	   F2[16] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	 send_9702array(F1,F2,str5);
							
							
							
												
	        	}
	             if(str5 == 16)
	         {
                  if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    			
													str[9] =0;											
										 	key_gamma_up(4);       //第7灰阶
											delay_ms(1000);
	        			    }
	            F1[15] = str[2];   //str5代表两个寄存器控制一个灰阶
	             F2[15] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	
	          send_9702array(F1,F2,str5);
						
							
												
	        	}
	        		   if(str5 == 24)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			  {    				
									  str[9] =0;
									 	key_gamma_up(8);       //第7灰阶
										delay_ms(1000);
	        			  }
	            F1[14] = str[2];   //str5代表两个寄存器控制一个灰阶
      	      F2[14] = str[2];   //str5代表两个寄存器控制一个灰阶
	           send_9702array(F1,F2,str5);
														
												
	        	}			
					    if(str5 == 40)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			  {    				
										 str[9] =0;
										 key_gamma_up(16);       //第7灰阶
										 delay_ms(1000);
	        			  }
	            F1[13] = str[2];   //str5代表两个寄存器控制一个灰阶
	            F2[13] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	
	            send_9702array(F1,F2,str5);
						
													
	        	}			
          
						 if(str5 == 60)
	         {
                if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    
									str[9] =0;												
								 	key_gamma_up(20);       //第7灰阶
									delay_ms(1000);
	        			 }
	            F1[12] = str[2];   //str5代表两个寄存器控制一个灰阶
	            F2[12] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	  send_9702array(F1,F2,str5);
							
							
					
	        	}		
					  if(str5 == 96)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    	
								  str[9] =0;												
									key_gamma_up(36);       //第7灰阶
							   	delay_ms(1000);
	        			 }
	            F1[11] = str[2];   //str5代表两个寄存器控制一个灰阶
	            F2[11] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	  send_9702array(F1,F2,str5);
							
																				
	        	}		
						  if(str5 == 128)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			 {    
									str[9] =0;												
								 	key_gamma_up(32);       //第7灰阶
									delay_ms(1000);
	        			 }		
	            F1[10] = str[2];   //str5代表两个寄存器控制一个灰阶
	            F2[10] = str[2];   //str5代表两个寄存器控制一个灰阶
	          send_9702array(F1,F2,str5);
							
							
														
	        	}		
					 
							  if(str5 == 160)
	         {
               if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
											str[9] =0;												
										 	key_gamma_up(32);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            F1[9] = str[2];   //str5代表两个寄存器控制一个灰阶
	            F2[9] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	  send_9702array(F1,F2,str5);
							
							
															
	        	}		
					 
						  if(str5 == 188)
	         {
                if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
													str[9] =0;												
										 	key_gamma_up(28);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            F1[8] = str[2];   //str5代表两个寄存器控制一个灰阶
	             F2[8] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	
	           send_9702array(F1,F2,str5);
							
	       
							
															
	        	}		
					 
						  if(str5 == 208)
	         {
            if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    
													str[9] =0;	
											
										 	key_gamma_up(20);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            F1[7] = str[2];   //str5代表两个寄存器控制一个灰阶
	             F2[7] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	  send_9702array(F1,F2,str5);
				
							
															
	        	}		
	        		
						if(str5 == 224)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(16);       //第7灰阶
											delay_ms(1000);
	        			    }			
	            F1[6] = str[2];   //str5代表两个寄存器控制一个灰阶
	            F2[6] = str[2];   //str5代表两个寄存器控制一个灰阶
	          send_9702array(F1,F2,str5);
							
	        	
							
													
	        	}								
					 if(str5 == 232)
	         {
            if(str[9] == 1)  //上一个灰阶比较完成
	        		{    			
									str[9] =0;												
								 	key_gamma_up(8);       //第7灰阶
									delay_ms(1000);
	        	  }				
	            F1[5] = str[2];   //str5代表两个寄存器控制一个灰阶
	            F2[5] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	  send_9702array(F1,F2,str5);
		
							
												
	        	}		

					 if(str5 == 243)
	         {
            if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    	
													str[9] =0;												
										 	key_gamma_up(11);       //第7灰阶
											delay_ms(1000);
	        			    }		
	              F1[4] = str[2];   //str5代表两个寄存器控制一个灰阶
	              F2[4] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	  send_9702array(F1,F2,str5);
							
	    
							
														
	        	}			

            if(str5 == 247)
	         {
              if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    		
													str[9] =0;												
										 	key_gamma_up(4);       //第7灰阶
											delay_ms(1000);
	        			    }	
	            F1[3] = str[2];   //str5代表两个寄存器控制一个灰阶
	            F2[3] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	
	           send_9702array(F1,F2,str5);
							
	  
															
	        	}					

          if(str5 == 251)   
	         {
             if(str[9] == 1)  //上一个灰阶比较完成
	        			    {    			
													str[9] =0;												
										 	key_gamma_up(4);       //第7灰阶
											delay_ms(1000);
	        			    }					
	            F1[2] = str[2];   //str5代表两个寄存器控制一个灰阶
	             F2[2] = str[2];   //str5代表两个寄存器控制一个灰阶
	        	  send_9702array(F1,F2,str5);
							
	        	
											
	        	}			

					}


