#include "main.h"

void SetUp(void)
{
	  TIM4_Init();
	  GPIO_CAN1();
	  CAN1_Init();
	  GPIO_USART3();
	  UART3_Init();
	  GPIO_LED();
}


