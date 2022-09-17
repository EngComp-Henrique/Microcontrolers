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

	RCC->AHB1ENR |= 1;				// Liga o clock do GPIO
	GPIOA->MODER |= (0b01 << 12);	// configura o pino PAC como saída

	// GPIOA->ODR &= (1 << 6);
	// GPIOA->ODR |= (1 << 6);

	// while (1);

	int delay_off = 50000000;
	int delay_on = 100000;

	while (1) {
		GPIOA->ODR |= (1 << 6);		//Nível lógico alto no pino 6
		Delay(delay_off);
		GPIOA->ODR &= ~(1 << 6);	// Nível lógico baixo no pino 6
		Delay(delay_on);
		delay_off = delay_off / 2;
		if (delay_off == 0) delay_off = 50000000;
	}

	return 1;
}
