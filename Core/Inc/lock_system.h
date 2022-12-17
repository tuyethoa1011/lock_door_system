
/**
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************
  File:	      lock_system.c
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


#ifndef __LOCK_SYSTEM_H
#define __LOCK_SYSTEM_H

#include "rc522.h"
#include "i2c-lcd.h"
#include "FLASH_SECTOR_F4.h"
#include "string.h"
#include <stdio.h>
#include <stdint.h>

extern I2C_HandleTypeDef hi2c1; //khai bao struct I2C1
 
extern SPI_HandleTypeDef hspi1; //khai bao struct SPI1

extern TIM_HandleTypeDef htim10; //khai bao struct TIM10 (Timer to make exact delay)

//cac define duoi khai bao macro cac port pin nham phuc vu muc dich nhan tin hieu tu keypad
#define R1_PORT GPIOA
#define R1_PIN GPIO_PIN_7

#define R2_PORT GPIOA
#define R2_PIN GPIO_PIN_6

#define R3_PORT GPIOA
#define R3_PIN GPIO_PIN_5

#define R4_PORT GPIOA
#define R4_PIN GPIO_PIN_4

#define C1_PORT GPIOA
#define C1_PIN GPIO_PIN_3

#define C2_PORT GPIOA
#define C2_PIN GPIO_PIN_2

#define C3_PORT GPIOA
#define C3_PIN GPIO_PIN_1

#define C4_PORT GPIOA
#define C4_PIN GPIO_PIN_0

// flag variable
extern int flag_pass, flag_rfid, flag_change;

//declare numsWords
extern int numofwords;
			
// variable RFID
extern unsigned char CardID[4]; //mang nhan ID tu ben ngoai
extern unsigned char MyID[4];	//My card on my keys
extern unsigned char ReadID_buf[4]; //mang doc ID tu FLASH

extern uint8_t key[16]; //contains 16 character 	//temp array //mang tam chua input tu nguoi dung

extern uint8_t mode[4]; //mang chua che do
extern int wrong_count; //dem so lan user nhap sai mk hoac ID
extern char default_pass[16]; //nang chua mat khau mac dinh

//uint8_t str[MFRC522_MAX_LEN]; //mang chua UID cua the

//Flash mem store/read
extern uint32_t Rx_Data[30];
extern uint32_t Rx_DataRFID[30];


// RC522 function declaration
uint8_t MFRC522_Check(uint8_t* id);
uint8_t MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID);
void MFRC522_WriteRegister(uint8_t addr, uint8_t val);
uint8_t MFRC522_ReadRegister(uint8_t addr);
void MFRC522_SetBitMask(uint8_t reg, uint8_t mask);
void MFRC522_ClearBitMask(uint8_t reg, uint8_t mask);
uint8_t MFRC522_Request(uint8_t reqMode, uint8_t* TagType);
uint8_t MFRC522_ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen);
uint8_t MFRC522_Anticoll(uint8_t* serNum);
void MFRC522_CalulateCRC(uint8_t* pIndata, uint8_t len, uint8_t* pOutData);
uint8_t MFRC522_SelectTag(uint8_t* serNum);
uint8_t MFRC522_Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t* Sectorkey, uint8_t* serNum);
uint8_t MFRC522_Read(uint8_t blockAddr, uint8_t* recvData);
uint8_t MFRC522_Write(uint8_t blockAddr, uint8_t* writeData);
void MFRC522_Init(void);
void MFRC522_Reset(void);
void MFRC522_AntennaOn(void);
void MFRC522_AntennaOff(void);
void MFRC522_Halt(void);

void delay_ms(long int time); //ham delat ms
void delay_1ms(void); //ham delay 1ms
char read_keypad(void); //ham doc nut nhan tu keypad
void password_enter(uint8_t *arr, int count); //ham nhap mat khau tu keypad
void keypad_password(void); //ham xu ly viec nhap mat khau tu keypad va xac nhan
void unlock_door(void); //ham dung de mo khoa cua
void RFID_task(void); //ham thuc hien quet the RFID
void change_pass(void); //ham thuc hien viec thay doi mat khau
void getDefaultPass_FromFlash(void); //ham lay mat khau mac dich duoc luu trong FLASH MEM


#endif
