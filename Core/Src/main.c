/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  * Modifier: Ngo Le Tuyet Hoa
  * Updated: 17 DEC 2022
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  * 
  * 
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
#include "string.h"
#include <stdio.h>
#include <stdint.h>
#include "lock_system.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim10;

/* USER CODE BEGIN PV */
//INITIALIZE_VARIABLES
// flag variable
int flag_pass = 1, flag_rfid = 1, flag_change = 1;

//declare numsWords
int numofwords;
			
// variable RFID
unsigned char CardID[4]; //mang nhan ID tu ben ngoai
unsigned char MyID[4] = {0x63, 0x93, 0x9B,0xAC};	//My card on my keys
unsigned char ReadID_buf[4]; //mang doc ID tu FLASH

uint8_t key[16] = ""; //contains 16 character 	//temp array //mang tam chua input tu nguoi dung

uint8_t mode[4]; //mang chua che do
int wrong_count = 0; //dem so lan user nhap sai mk hoac ID
char default_pass[16] = ""; //nang chua mat khau mac dinh

//uint8_t str[MFRC522_MAX_LEN]; //mang chua UID cua the

//Flash mem store/read
uint32_t Rx_Data[30];
uint32_t Rx_DataRFID[30];


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM10_Init(void);
static void MX_SPI1_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
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
  MX_TIM10_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	
	HAL_TIM_Base_Start_IT(&htim10); //khai bao su dung TIM10
	//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //khai bao su dung PWM TIM1 CH1

		MFRC522_Init(); //khoi tao cho cam bien dien tu RC522
		
		lcd_clear();
		lcd_put_cur(0,0);
		lcd_send_string("WELCOME TO UIT");
		lcd_put_cur(1,2);
		lcd_send_string("CE FACULTY ^-^");
		HAL_Delay(2000);
	
			
		Flash_Read_Data(0x08008100 , Rx_Data, 1); //Read only one word from mem to check if there is data in it or not

		if(Rx_Data[0] == 0xFFFFFFFF) //this will only run once when customer first buy lock when flash is empty
		{	
			lcd_clear();
			lcd_put_cur(0,0);
			lcd_send_string("CAI MATKHAU: ");
				
			password_enter(key,16);
				
			numofwords = (strlen((const char*)key)/4)+((strlen((const char*)key)%4)!=0);
				
			//ghi mat khau vao sector 2 address 0x0800100
			Flash_Write_Data(0x08008100 , (uint32_t *)key, numofwords); //ghi mat khau tu ban phim vao bo nho Flash

			HAL_Delay(1); //buffer delay

			//ghi UID vao sector 3
			Flash_Write_Data(0x0800C000,(uint32_t*)MyID,4); //ghi UID master card vao nho Flash

			HAL_Delay(1); //buffer delay
		}

		memset(key,0, sizeof(key)); //clear key temp pass array

		//Done initial system
			
		//Mo ta dac tinh chuc nang o khoa thong minh
		
		//CHE DO:
		//*: PASSWORD
		//**: RFID
		//***: DOI MK
 
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
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(50);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
					break;
				}
			
				if(mode[j] != 0x01)
				{
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
					delay_ms(50);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);

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
				HAL_Delay(10);
			}
		} else if(strncmp((const char*) mode,"**#",3) == 0)
		{	
			while(flag_rfid) {
				lcd_put_cur(0,0);
				lcd_send_string("INSERT ID CARD");
				
				RFID_task();
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|CS_Pin|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, KHOADIENTU_Pin|DENIED_LED_Pin|PASSIVE_BUZZER_Pin|LED_light_Pin
                          |CSD7_Pin, GPIO_PIN_RESET);

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

  /*Configure GPIO pins : KHOADIENTU_Pin DENIED_LED_Pin PASSIVE_BUZZER_Pin LED_light_Pin
                           CSD7_Pin */
  GPIO_InitStruct.Pin = KHOADIENTU_Pin|DENIED_LED_Pin|PASSIVE_BUZZER_Pin|LED_light_Pin
                          |CSD7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
