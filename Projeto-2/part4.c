/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

/*
 Desafio: Ligar apenas os dois leds quando os DOIS bot�es forem pressinados. Caso apenas um dos leds seja ligado, n�o fa�a nada
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
	GPIOA->MODER |= (0b01 << 12);	// configura o pino PA6 como sa�da
	GPIOA->MODER |= (0b01 << 14);	// configura o pino PA7 como sa�da

	// Quando bot�o pressionado -> n�vel l�gico � baixo
	// Quando bot�o solto -> n�vel � FLUTUANTE! N�o � alto
	// O que queremos � que o n�vel do bot�o seja alto

	// Configurando entradas
	GPIOE->MODER &= ~(0b11 << 8);
	GPIOE->MODER &= ~(0b11 << 6);

	// Para isso conectamos um n�vel alto na entrada, e conectamos a um resistor
	// Habilitando registrador de pull-up -> garantir n�vel l�gico alto
	GPIOE->PUPDR |= (0b01 << 8);
	GPIOE->PUPDR |= (0b01 << 6);


	while (1) {
		// Lendo entrada
		// Fornecido atrav�s do registrador IDR. Apenas os 16 primeiros bits s�o utilizados
		if (!(GPIOE->IDR & (1 << 4))){
			GPIOA->ODR &= ~(1 << 6);
		} else {
			GPIOA->ODR |= (1 << 6);
		}

		if (!(GPIOE->IDR & (1 << 3))) {
			GPIOA->ODR &= ~(1 << 7);
		} else {
			GPIOA->ODR |= (1 << 7);
		}
	}

	return 1;
}
