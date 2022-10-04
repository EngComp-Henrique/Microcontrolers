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

#define K0 			!(GPIOE->IDR & (1<<4))
#define K1 			!(GPIOE->IDR & (1<<3))
#define LED_ON(n) 	GPIOA->ODR &= ~(1<<n)
#define LED_OFF(n) 	GPIOA->ODR |= (1<<n)

void Delay(int delay)
{
	while (delay) --delay;
}

/*
 * DESAFIO: Ligar
 *
 * */

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;            //habilita o clock do GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;            //habilita o clock do GPIOE

    GPIOA->MODER |= (0b01 << 12);    //configura o pino PA6 como saída
    GPIOA->MODER |= (0b01 << 14);    //configura o pino PA7 como saída
    GPIOE->MODER &= ~(0b11 << 6);    //configurando o pino PE3 como entrada
    GPIOE->PUPDR |= (0b01 << 6);    //liga o resistor de pull-up no pino PE3 (pra garanbir nível alto quando a chave estiver solta)
    GPIOE->MODER &= ~(0b11 << 8);    //configurando o pino PE4 como entrada
    GPIOE->PUPDR |= (0b01 << 8);    //liga o resistor de pull-up no pino PE4 (pra garanbir nível alto quando a chave estiver solta)

    int k0 = 0;
    while(1)
    {
    	LED_OFF(6);
    	LED_OFF(7);

    	if (K0 && !(K1))
    	{
    		k0 = 1;
    		while (k0) {
    			if (K1) {
					LED_ON(6);
					LED_ON(7);
					Delay(10000000);
					k0 = 0;
    			}

    		}
    	}

    }
}
