/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
//#include "stm32f401xe.h"

#define RCC_BASE		((uint32_t *)(0x40023800))
#define RCC_AHB1ENR		((uint32_t *)(0x40023830))

#define GPIOA_BASE		((uint32_t *)(0x40020000))
#define GPIOA_MODER		((uint32_t *)(0x40020000))
#define GPIOA_OTYPER	((uint32_t *)(0x40020004))
#define GPIOA_BSSR		((uint32_t *)(0x40020018))

void delay(uint32_t d);

int main(void)
{
    /* Loop forever */
	uint32_t volatile *reg;
	uint32_t val, one = 1;
	uint32_t volatile rr;

	reg = RCC_AHB1ENR;
	val = (uint32_t) 1;
	*reg = val;

	reg = GPIOA_MODER;
	val = *reg;
	val = val | (uint32_t)1;
	*reg = val;

	reg = GPIOA_BSSR;
	val = one;
	*reg = val;

	reg = GPIOA_BSSR;
	val = one << 16;
	*reg = val;



	while (1) {


		reg = GPIOA_BSSR;
		val = one;
		*reg = val;

		delay(1000000);

		reg = GPIOA_BSSR;
		val = one << 16;
		*reg = val;

		delay(1000000);
	}
}

void delay(uint32_t d) {
	for (; d > 0; --d) {
		;
	}
}
