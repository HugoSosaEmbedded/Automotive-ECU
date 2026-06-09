#include "main.h"

char buffer1[64];
char buffer2[64];

char* tx_buffer = buffer1;   // buffer actual a transmitir
char* fill_buffer = buffer2; // buffer donde escribimos nuevos datos


extern volatile uint32_t i;


void UART3_Init(void)
{
	RCC->APB1ENR |= (1<<18); //Enable clock for USART3
	USART3->CR1 &= ~((1<<12) | (1<<28)); // 8 data bits as word length
	USART3->CR2 &= ~((1<<12) | (1<<13)); // USART configured with 1 stop bit
	USART3->CR1 &= ~(1<<15); // Oversamplig  by 16
	USART3->BRR = (8<<4) | 11; // Baud rate desired 115200
	USART3->CR1 |= (1<<3); //Transmitter is enabled
	USART3->CR1 |= (1<<0); //USART enable

	NVIC_EnableIRQ(USART3_IRQn);
	NVIC_SetPriority(USART3_IRQn,5);
}

void UART3_Transmmit(void)
{
	Swap_Buffer();
	i = 0;  // reinicia índice para ISR
	USART3->CR1 |= (1<<7); // activar TXEIE para que la ISR continúe transmit
}

void Swap_Buffer(void)
{
	char* tmp = tx_buffer;
	tx_buffer = fill_buffer;
	fill_buffer = tmp;
}
