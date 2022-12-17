/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f411e_discovery.h"

extern int _write(int fd, char *ptr, int len);

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CS_Pin GPIO_PIN_6
#define CS_GPIO_Port GPIOA
#define KHOADIENTU_Pin GPIO_PIN_9
#define KHOADIENTU_GPIO_Port GPIOD
#define DENIED_LED_Pin GPIO_PIN_10
#define DENIED_LED_GPIO_Port GPIOD
#define PASSIVE_BUZZER_Pin GPIO_PIN_11
#define PASSIVE_BUZZER_GPIO_Port GPIOD
#define LED_light_Pin GPIO_PIN_13
#define LED_light_GPIO_Port GPIOD
#define RST_Pin GPIO_PIN_15
#define RST_GPIO_Port GPIOA
#define CSD7_Pin GPIO_PIN_7
#define CSD7_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/*
* Default values for SPI, change if needed
*/

/* Definition for SPIx clock resources */
#define SPIx                             SPI2
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI2_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_NSS_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_CS_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOD_CLK_ENABLE()
#define SPIx_FORCE_RESET()               __HAL_RCC_SPI2_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI2_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_3 // D13
#define SPIx_SCK_GPIO_PORT               GPIOD
#define SPIx_SCK_AF                      GPIO_AF5_SPI2
#define SPIx_MISO_PIN                    GPIO_PIN_14 // D12
#define SPIx_MISO_GPIO_PORT              GPIOB
#define SPIx_MISO_AF                     GPIO_AF5_SPI2
#define SPIx_MOSI_PIN                    GPIO_PIN_15 // D11
#define SPIx_MOSI_GPIO_PORT              GPIOB
#define SPIx_MOSI_AF                     GPIO_AF5_SPI2
#define SPIx_CS_PIN                      GPIO_PIN_11 // D10
#define SPIx_CS_GPIO_PORT                GPIOD

void Error_Handler(void);


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
