#include "main.h"

void GPIO_CAN1(void)
{
	//PD0  RX  PD1  TX
	RCC->AHB1ENR |= (1<<3); // Enable clock port D, RCC_AHB1ENR_GPIOBEN
	GPIOD->MODER &= ~((3<<0) | (3<<2));
	GPIOD->MODER |= ((2<<0) | (2<<2)); // PD1 and PD0 as alternate function
	GPIOD->OSPEEDR &= ~((3<<0) | (3<<2));
	GPIOD->OSPEEDR |= ((2<<0) | (2<<2)); // PD0 and PD1 high speed
	GPIOD->AFR[0] &= ~((0xF<<0) | (0xF<<4));
	GPIOD->AFR[0] |= ((9<<0) | (9<<4)); // PD0 y PD1 AF9
}

void GPIO_USART3(void)
{
	//PD8 TX, PD9 RX
	RCC->AHB1ENR |= (1<<3); // Enable clock port D, RCC_AHB1ENR_GPIODEN
	GPIOD->MODER &= ~((3<<16) | (3<<18));
	GPIOD->MODER |= ((2<<16) | (2<<18)); // PD8 and PD9 as alternate function
	GPIOD->OSPEEDR &= ~((3<<16) | (3<<18));
	GPIOD->OSPEEDR |= ((2<<16) | (2<<18)); // PD8 and PD9 high speed
	GPIOD->AFR[1] &= ~((0xF<<0) | (0xF<<4));
	GPIOD->AFR[1] |= ((7<<0) | (7<<4)); // PD8 y PD9 AF7
}

void GPIO_LED(void)
{
	//PA2, PA3, PA6
	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER &= ~((0x3<<4) | (0x3<<6) | (0x3<<12));
	GPIOA->MODER |= ((0x1<<4) | (0x1<<6) | (0x1<<12));
	GPIOA->OTYPER &= ~((0x3<<4) | (0x3<<6) | (0x3<<12));
}

void YELLOW_LED_ON(void)
{
	GPIOA->ODR |= (1<<2);
}

void GREEN_LED_ON(void)
{
	GPIOA->ODR |= (1<<3);
}

void RED_LED_ON(void)
{
	GPIOA->ODR |= (1<<6);
}

void YELLOW_LED_OFF(void)
{
	GPIOA->ODR &= ~(1<<2);
}

void GREEN_LED_OFF(void)
{
	GPIOA->ODR &= ~(1<<3);
}

void RED_LED_OFF(void)
{
	GPIOA->ODR &= ~(1<<6);
}
