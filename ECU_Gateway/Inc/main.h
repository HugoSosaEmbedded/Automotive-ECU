/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct
{
	uint16_t rpm;
	uint8_t alive_counter;
	uint8_t crc;
} payload_rpm_t;

typedef enum
{
	NORMAL_MESSAGE = 0,
	DEGRADED_MESSAGE,
	ERROR_MESSAGE
} states_t;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void System_Clock_Config(void);
void Error_Handler(void);
void CAN1_Init(void);
void GPIO_CAN1(void);
void CAN1_TX(void);
void UART3_Init(void);
void GPIO_USART3(void);
void Swap_Buffer(void);
void TIM4_Init(void);
bool CAN1_Received(payload_rpm_t* payload, uint8_t* crc_check);
void CAN1_SetFlag(void);
void UART3_Transmmit(void);
void SetUp();
void TIM3_RegisterCB(void(*cb)(void));
void TIM_Call(void);
void GPIO_LED(void);
void RED_LED_OFF(void);
void GREEN_LED_OFF(void);
void YELLOW_LED_OFF(void);
void RED_LED_ON(void);
void GREEN_LED_ON(void);
void YELLOW_LED_ON(void);
void Check_State(states_t message, uint8_t count);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
