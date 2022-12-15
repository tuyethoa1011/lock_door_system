/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "i2c-lcd.h"
#include "string.h"
#include "rc522.h"
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
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


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim10;

/* USER CODE BEGIN PV */

// flag variable
int flag_pass = 1, flag_rfid = 1, flag_change = 1; //flag pass might not use
			
// variable RFID
//uint8_t dataUDP_permit[]="Ma the hop le ";
//uint8_t dataUDP_deny[]="Ma the khong hop le ";
//unsigned char CardID[4];
//unsigned char MyID[4] = {0x63, 0x93, 0x9B,0xAC};	//My card on my keys

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM10_Init(void);
static void MX_SPI1_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */


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



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t key[16] = ""; //contains 16 character 	//temp array //mang tam chua input tu nguoi dung
uint8_t user_pass [16] = ""; //mang chua mat khau nhap tu nguoi dung 

uint8_t confirm_pass[16] = ""; //mang chua mat khau xac nhan tu nguoi dung de doi mat khau

uint8_t mode[4];
int wrongpass_count = 0; //dem so lan user nhap sai mk
char default_pass[16] = ""; //nang chua mat khau mac dinh

uint8_t str[MFRC522_MAX_LEN]; //mang chua UID cua the

void delay_ms(long int time); //ham delat ms
void delay_1ms(void); //ham delay 1ms
char read_keypad(void); //ham doc nut nhan tu keypad
void password_enter(uint8_t *arr, int count); //ham nhap mat khau tu keypad
void keypad_password(void); //ham xu ly viec nhap mat khau tu keypad va xac nhan
void unlock_door(void); //ham dung de mo khoa cua
void RFID_task(void); //ham thuc hien quet the RFID
void change_pass(void); //ham thuc hien viec thay doi mat khau

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
					break;
				}
			
				if(key[i] != 0x01)
				{
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
						//do xong roi no cu chay xu ly trong vong lap nay mai thoi
						//cho den khi nhan thay tin hieu tu nut bam thi tat den khoa cua roi break vong lap out ra ngoai vo man hinh mac dinh
						if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == GPIO_PIN_SET)
						{
							//tat den
							HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_RESET);
							//doi 3s roi khoa cua lai
							//delay_ms(3000);
							
						
							//close door 
							htim1.Instance->CCR1 = 175; //quay 180 do
							
							
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
						else 
						{
							//do nothing, just wait
						}
					}
}


void keypad_password(void)
{				
				
		    lcd_clear();
				lcd_put_cur(0,0);
				lcd_send_string("ENTER PASSWORD: ");
	
				password_enter(key,16);
		
				
				memcpy(user_pass,key,sizeof(key));
				
				memset(key,0,sizeof(key));
			
				if(strncmp((const char*)user_pass,(const char*)default_pass,16)==0)
				{
					//dung mat khau thi minh se mo den bang chan PD13
					//dong thoi hien thi -- UNLOCKED -- roi giu cho den khi nao nut bam duoc cai dat muc dich de kich tin hieu khoa cua thi
					//tat den roi khoa cua roi quay ve man hinh che do mac dinh
					lcd_clear();
					lcd_put_cur(0,4);
					lcd_send_string("CORRECT!");
					lcd_put_cur(1,0);
					lcd_send_string("--- UNLOCKED ---");
					wrongpass_count = 0;
					//open door
					htim1.Instance->CCR1 = 75; //quay 180 do
					
					
					//turn on LED
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_SET);
					
					unlock_door();
					
				} else //truong hop nhap sai mk 
				{	
					
					++wrongpass_count;
					lcd_clear();
					lcd_put_cur(0,1);
					lcd_send_string("ACCESS DENIED!");
					lcd_put_cur(1,0);
					lcd_send_string("PLEASE TRY AGAIN");
					
					if(wrongpass_count == 5)
					{	
						HAL_Delay(1000);
						lcd_clear();
						lcd_put_cur(0,0);
						lcd_send_string("NHAP SAI > 5 LAN");
						lcd_put_cur(1,0);
						lcd_send_string("WAIT FOR 3 MINS");
						
						//actually we make 3 mins to simulate 3mins thiet no kidding
						delay_ms(180000);
						wrongpass_count = 0;
					}
					
				}
				
}

void RFID_task(void)
{	
	if(!MFRC522_Request(PICC_REQIDL,str))
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
					
					//tieng buzzer keu accept
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(200);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					
					HAL_Delay(1200);
					//open door
					htim1.Instance->CCR1 = 75; //quay 180 do
					
					
					//turn on LED
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_SET);
					
					unlock_door();
		
				}
				else if(str[1] != 0x93)
				{
					lcd_clear();
					lcd_put_cur(0,0);
					lcd_send_string("ACCESS DENIED");
					
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(50);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					delay_ms(50);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(200);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(270);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					
					
				 //buzzer keu accept
					//tieng buzzer keu bao denied, tieng keu giua accept voi denied se khac
					
					delay_ms(1000);
				}
			}
	}
}
void change_pass(void)
{				
				while(1) {
				lcd_clear();
				lcd_put_cur(0,0);
				lcd_send_string("CURRENT PASS:");
					
				password_enter(key,16);
				
				if(strncmp((const char*)key,default_pass,sizeof(key))==0)
				{
					lcd_clear();
					lcd_put_cur(0,0);
					lcd_send_string("CHANGE PASS: ");
					HAL_Delay(1200);
				
					memset(key,0,sizeof(key));
			
					password_enter(key,16);
					
				
			
					//done nhap mat khau duoc cai vo mang mat khau mac dinh de luu tru
		
					memcpy(default_pass,key,sizeof(key));
		
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
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM10_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	
	HAL_TIM_Base_Start_IT(&htim10); //khai bao su dung TIM10
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //khai bao su dung PWM TIM1 CH1

		MFRC522_Init(); //khoi tao cho cam bien dien tu RC522
		
		lcd_clear();
		lcd_put_cur(0,0);
		lcd_send_string("WELCOME TO UIT");
		lcd_put_cur(1,2);
		lcd_send_string("CE FACULTY ^-^");
		HAL_Delay(2000);
			
		lcd_clear();
		lcd_put_cur(0,0);
		lcd_send_string("CAI MATKHAU: ");
			
		lcd_put_cur(1,0);
		//can mot vong lap loop neu nhu nhap sai mat khau mac dinh thi loop ke tu luc moi khoi dong
		//neu nhu cho lau qua ma khong xac nhan doi mat khau thi comeback man hinh luc ban dau
		memset(key,0,sizeof(key));
			
		password_enter(key,16);
			
		//done nhap mat khau duoc cai vo mang mat khau mac dinh de luu tru
		
		memcpy(default_pass,key,sizeof(key));
		
		memset(key,0, sizeof(key)); //clear key temp pass array

	
		//Mo ta dac tinh chuc nang o khoa thong minh
		
		//CHE DO:
		//*: PASSWORD
		//**: RFID
		//***: DOI MK
		//MINH SE LAM MOT CAI BAN TUTORIAL NHO NHO CODE WEB GIOI THIEU CHO NGUOI DUNG CHANG HAN XD host tren github
 
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE BEGIN 3 */
		
	
			//initial
			flag_change = 1;
			flag_pass = 1;
			flag_rfid = 1;
			
			lcd_clear();
			lcd_put_cur(0,1);
			lcd_send_string("***WELCOME***");
		
			lcd_put_cur(1,0);
			lcd_send_string("MODE: ");
		
			int j = 0;
			int position = 5;
			//chon che do
			
			while(j<4)
			{
				mode[j] = read_keypad();
			
				if(mode[j]=='#') 
				{
					break;
				}
			
				if(mode[j] != 0x01)
				{
					lcd_put_cur(1,position);
					lcd_send_data(mode[j]);
					++j;
					++position;
				}
				HAL_Delay(100);	
		}

		lcd_clear();
		
		if(strncmp((const char*) mode,"*#",2) == 0)
		{
			while(flag_pass) {
				keypad_password();
				HAL_Delay(1200);
			}
		} else if(strncmp((const char*) mode,"**#",3) == 0)
		{	
			while(flag_rfid) {
				lcd_put_cur(0,0);
				lcd_send_string("INSERT ID CARD");
				
				RFID_task();
				HAL_Delay(10); 
			}
		}
		else if(strncmp((const char*) mode,"***#",4) == 0) //doi mat khau
		{
			change_pass();
		}
		memset(mode, 0, sizeof(mode)); //reset lai mode
	
		HAL_Delay(10);
		  /* USER CODE END 3 */
  
  }
     /* USER CODE END WHILE */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 1000;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 10000;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 9999;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|CS_Pin|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, PASSIVE_BUZZER_Pin|LED_light_Pin|CSD7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           RST_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 CS_Pin PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|CS_Pin|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PASSIVE_BUZZER_Pin LED_light_Pin CSD7_Pin */
  GPIO_InitStruct.Pin = PASSIVE_BUZZER_Pin|LED_light_Pin|CSD7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : LOCK_BUTTON_Pin */
  GPIO_InitStruct.Pin = LOCK_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(LOCK_BUTTON_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
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
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
