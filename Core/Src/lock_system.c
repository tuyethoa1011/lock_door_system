/**
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************
  File:	      lock_system.h
  Modifier:   Ngo Le Tuyet Hoa
  Updated:    17th DEC 2022
  ***************************************************************************************************************
  Copyright (C) 2022 https://github.com/tuyethoa1011
  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.
  ***************************************************************************************************************
*/

#include "lock_system.h"

void delay_1ms(void)
{
 __HAL_TIM_SetCounter(&htim10, 0);
 while (__HAL_TIM_GetCounter(&htim10)<10);
}

void delay_ms(long int time)
{
 long int i = 0;
 for(i = 0; i < time; i++)
 {
   delay_1ms();
 }

}

char read_keypad (void)
{	

	/* Make ROW 1 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_RESET);  //Pull the R1 low
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
	
	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
		return '1';
	}
	
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
		return '2';
	}
	
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
		return '3';
	}
	
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
	{
		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
		return 'A';
	}
	
	/* Make ROW 2 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 High
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_RESET);  // Pull the R2 Low
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
	
	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
		return '4';
	}
	
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
		return '5';
	}
	
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
		return '6';
	}
	
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
	{
		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
		return 'B';
	}
	
	
	/* Make ROW 3 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 High
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_RESET);  // Pull the R3 Low
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
	
	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
		return '7';
	}
	
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
		return '8';
	}
	
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
		return '9';
	}
	
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
	{
		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
		return 'C';
	}
	
		
	/* Make ROW 4 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 High
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 Low
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_RESET);  // Pull the R4 High
	
	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
		return '*';
	}
	
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
		return '0';
	}
	
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
		return '#';
	}
	
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
	{
		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
		return 'D';
	}
}


void password_enter(uint8_t *arr,int count)
{
			int i = 0;
			//key[i] la mang giup de xac thuc mat khau luon
			while(i<count)
			{
				key[i] = read_keypad();
			
				if(key[i]=='#') 
				{	
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(50);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					break;
				}
			
				if(key[i] != 0x01)
				{	
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(50);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);

					lcd_put_cur(1,i);
					lcd_send_data(key[i]);
					++i;
				}
				HAL_Delay(100);	
		}
}

void unlock_door(void)
{
	while(1) 
	{
						
		//wait for 10 seconds automatically close the door
		delay_ms(10000); 
		//tat den
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_RESET);
		//doi 0.5s roi khoa cua lai
		delay_ms(500);
											
		//close door 
		//htim1.Instance->CCR1 = 175; //quay 180 do
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_RESET);
							
							
		lcd_clear();
		lcd_put_cur(0,2);
		lcd_send_string("GOOD BYE ^-^");
		lcd_put_cur(1,1);
		lcd_send_string("SEE YOU AGAIN");
							
		HAL_Delay(1200);
		flag_pass = 0;
		flag_rfid = 0;
		break;
	}
}

void getDefaultPass_FromFlash(void)
{
	Flash_Read_Data(0x08008100 , Rx_Data, numofwords);

	Convert_To_Str(Rx_Data,default_pass);
}

void keypad_password(void)
{				
				
		    lcd_clear();
			lcd_put_cur(0,0);
			lcd_send_string("ENTER PASSWORD: ");
	
			password_enter(key,16);

			getDefaultPass_FromFlash();
			
			if(strncmp((const char*)key,(const char*)default_pass,16)==0)
			{
				//dung mat khau thi minh se mo den bang chan PD13
				//dong thoi hien thi -- UNLOCKED -- roi giu cho den khi nao nut bam duoc cai dat muc dich de kich tin hieu khoa cua thi
				//tat den roi khoa cua roi quay ve man hinh che do mac dinh
				lcd_clear();
				lcd_put_cur(0,4);
				lcd_send_string("CORRECT!");
				lcd_put_cur(1,0);
				lcd_send_string("--- UNLOCKED ---");
				wrong_count = 0;
				//open door
				//htim1.Instance->CCR1 = 75; //quay 180 do
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_SET);
					
				//turn on LED
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_SET);
					
				unlock_door();
					
			} else //truong hop nhap sai mk 
			{	
					
				++wrong_count;
				lcd_clear();
				lcd_put_cur(0,1);
				lcd_send_string("ACCESS DENIED!");
				lcd_put_cur(1,0);
				lcd_send_string("PLEASE TRY AGAIN");
				

				if(wrong_count == 5)
				{	
					HAL_Delay(1000);
					lcd_clear();
					lcd_put_cur(0,0);
					lcd_send_string("NHAP SAI > 5 LAN");
					lcd_put_cur(1,0);
					lcd_send_string("WAIT FOR 1 MIN");
					
					//actually we make 3 mins to simulate 3mins thiet no kidding
					delay_ms(60000);
					wrong_count = 0;
					flag_pass = 0;
					flag_rfid = 0;
				}
			HAL_Delay(1200);
		}
		memset(key,0,sizeof(key));
				
}

void RFID_task(void)
{	

	if(MFRC522_Check(CardID) == MI_OK)
	{
		Flash_Read_Data(0x0800C000 , Rx_DataRFID, 4);

		Convert_To_Str(Rx_DataRFID,(char*)ReadID_buf);

		if(MFRC522_Compare(CardID, ReadID_buf) == MI_OK)
		{
			lcd_clear();
			lcd_put_cur(0,0);
			lcd_send_string("ACCESS GRANTED");
			lcd_put_cur(1,0);
			lcd_send_string("WELCOME HOME");
			wrong_count = 0;
			//tieng buzzer keu accept
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
			delay_ms(200);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					
			HAL_Delay(1200);
			//open door
			//htim1.Instance->CCR1 = 75; //quay 180 do
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_SET);
					
			//turn on LED
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_SET);
					
			unlock_door();

		} else if (MFRC522_Compare(CardID, MyID) == MI_ERR){
			++wrong_count;
			lcd_clear();
			lcd_put_cur(0,1);
			lcd_send_string("ACCESS DENIED!");
			lcd_put_cur(1,0);
			lcd_send_string("PLEASE TRY AGAIN");
									
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_SET); //ERROR LED light

			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
			delay_ms(50);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
			delay_ms(50);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
			delay_ms(150);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
			delay_ms(270);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_RESET);

			if(wrong_count == 5)
			{	
				HAL_Delay(1000);
				lcd_clear();
				lcd_put_cur(0,0);
				lcd_send_string("SAI THE > 5 LAN");
				lcd_put_cur(1,0);
				lcd_send_string("WAIT FOR 1 MIN");
						
				//actually we make 3 mins to simulate 3mins thiet no kidding
				delay_ms(60000);
				wrong_count = 0;

				flag_pass = 0;
				flag_rfid = 0;
			}
					
			lcd_clear();
		}
	}
	/*if(!MFRC522_Request(PICC_REQIDL,str)) //mot cach viet khac voi chuc nang tuong tu
		{
			if(!MFRC522_Anticoll(str))
			{
				//do something
				if(str[1] == 0x93)
				{
					lcd_clear();
					lcd_put_cur(0,0);
					lcd_send_string("ACCESS GRANTED");
					lcd_put_cur(1,0);
					lcd_send_string("WELCOME HOME");
					wrong_count = 0;
					//tieng buzzer keu accept
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(200);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					
					HAL_Delay(1200);
					//open door
					//htim1.Instance->CCR1 = 75; //quay 180 do
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_SET);
					
					//turn on LED
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_SET);
					
					unlock_door();

		
				}
				else if(str[1] != 0x93)
				{
					++wrong_count;
					lcd_clear();
					lcd_put_cur(0,1);
					lcd_send_string("ACCESS DENIED!");
					lcd_put_cur(1,0);
					lcd_send_string("PLEASE TRY AGAIN");
					
				
					
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_SET); //ERROR LED light

					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(50);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					delay_ms(50);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(150);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(270);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_RESET);

					if(wrong_count == 5)
					{	
						HAL_Delay(1000);
						lcd_clear();
						lcd_put_cur(0,0);
						lcd_send_string("SAI THE > 5 LAN");
						lcd_put_cur(1,0);
						lcd_send_string("WAIT FOR 1 MIN");
						
						//actually we make 3 mins to simulate 3mins thiet no kidding
						delay_ms(60000);
						wrong_count = 0;

						flag_pass = 0;
						flag_rfid = 0;
					}
					
					lcd_clear();
				 
				}
			}
	}*/
}
void change_pass(void)
{				
				while(1) {
				lcd_clear();
				lcd_put_cur(0,0);
				lcd_send_string("CURRENT PASS:");
					
				password_enter(key,16);

				//su dung flash de lay mk
				getDefaultPass_FromFlash();
				
				if(strncmp((const char*)key,default_pass,sizeof(key))==0)
				{
					lcd_clear();
					lcd_put_cur(0,0);
					lcd_send_string("CHANGE PASS: ");
					HAL_Delay(1200);
				
					memset(key,0,sizeof(key));
			
					password_enter(key,16);
					
					numofwords = (strlen((const char*)key)/4)+((strlen((const char*)key)%4)!=0); //tim hieu cach tinh nay chut
				
					Flash_Write_Data(0x08008100 , (uint32_t *)key, numofwords);
			
					//done nhap mat khau duoc cai vo mang mat khau mac dinh de luu tru
					HAL_Delay(10); //delay dem buffer nhe de dam bao data duoc ghi vo flash
		
					memset(key,0, sizeof(key));
					break;
				}
				else
				{
					lcd_clear();
					lcd_put_cur(0,1);
					lcd_send_string("ACCESS DENIED!");
					
					memset(key,0, sizeof(key));
					
					HAL_Delay(2000);
					break;
				}			
			}
}
