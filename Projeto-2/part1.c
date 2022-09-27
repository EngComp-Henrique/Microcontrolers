/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"

void Delay(int delay)
{
	while (delay) --delay;
}
			

int main(void)
{

	RCC->AHB1ENR |= 1;				// Liga o clock do GPIOA
	RCC->AHB1ENR |= (1 << 4);		// Liga o clock do GPIOE
	GPIOA->MODER |= (0b01 << 12);	// configura o pino PAC como saída
	GPIOA->MODER |= (0b01 << 14);

	// Configurando entradas
	GPIOE->MODER &= ~(0b11 << 8);
	GPIOE->MODER &= ~(0b11 << 6);

	GPIOE->PUPDR |= (0b01 << 6);
	GPIOE->PUPDR |= (0b01 << 8);


	while (1) {
		if (!(GPIOE->IDR & (1 << 4)) && !(GPIOE->IDR & (1 << 3))) {
			GPIOA->ODR &= ~(1 << 6);
		} else if (!(GPIOE->IDR & (1 << 4)) || !(GPIOE->IDR & (1 << 3))) {
			GPIOA->ODR &= ~(1 << 7);
		}
		else {
			GPIOA->ODR |= (1 << 6);
			GPIOA->ODR |= (1 << 7);
		}
	}

	return 1;
}
