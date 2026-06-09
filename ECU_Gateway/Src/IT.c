#include "main.h"

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"
/* Private includes ----------------------------------------------------------*/

volatile uint32_t i = 0;
extern char* tx_buffer;
extern void CAN1_SetFlag(void);
extern void(*TIM3_CallBack)(void);

void TIM4_IRQHandler(void)
{
	//This interruption help us to implement a counter, it increments each 1ms
	if(TIM4->SR & TIM_SR_UIF)
	{
		if(TIM3_CallBack)
		{
			TIM3_CallBack();
		}

		TIM4->SR &= ~TIM_SR_UIF; // Clean Update interrupt flag to set no update occurred
	}
}

void CAN1_RX0_IRQHandler(void)
{
	//This interruption is activated when there is a message received, the interruption is diable when the message is released
	CAN1_SetFlag();
	CAN1->RF0R |= (1<<5); // liberar FIFO0 inmediatamente
}

void USART3_IRQHandler()
{
	//This interruption is to get the message that usart will be transmitting
	if(USART3->ISR & USART_ISR_TXE) // If the content has been transferred into the shift register
	{
		if(tx_buffer[i] != '\0')
		{
			USART3->TDR = tx_buffer[i++]; //Save value into USART3_TDR
		}

		else
		{
			USART3->CR1 &= ~USART_CR1_TXEIE; //Disable interrupt
		}
	}
}


