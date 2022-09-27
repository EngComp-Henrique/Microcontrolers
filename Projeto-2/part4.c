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
 Desafio: Ligar apenas os dois leds quando os DOIS botões forem pressinados. Caso apenas um dos leds seja ligado, não faça nada
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
	GPIOA->MODER |= (0b01 << 12);	// configura o pino PA6 como saída
	GPIOA->MODER |= (0b01 << 14);	// configura o pino PA7 como saída

	// Quando botão pressionado -> nível lógico é baixo
	// Quando botão solto -> nível é FLUTUANTE! Não é alto
	// O que queremos é que o nível do botão seja alto

	// Configurando entradas
	GPIOE->MODER &= ~(0b11 << 8);
	GPIOE->MODER &= ~(0b11 << 6);

	// Para isso conectamos um nível alto na entrada, e conectamos a um resistor
	// Habilitando registrador de pull-up -> garantir nível lógico alto
	GPIOE->PUPDR |= (0b01 << 8);
	GPIOE->PUPDR |= (0b01 << 6);


	while (1) {
		// Lendo entrada
		// Fornecido através do registrador IDR. Apenas os 16 primeiros bits são utilizados
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
