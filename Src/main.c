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
#include "regs.h"
#include "regs_core.h"

void EXTI1_IRQHandler(void);
void delay(uint32_t d);
extern void EnableInterrupts(void);
extern void DisableInterrupts(void);
void SysTick_Handler(void);

extern void ClearStack(void);
extern void WaitForInterrupt(void);
extern void CallSVC(void);
extern void ChangeStack(void);
extern __attribute__((nacked)) void Change2MainStack(void);
extern void * Get_psp_addr(void);
extern void get_svc_type(void);

extern void stack_marker(uint32_t r0, uint32_t r1);

#define my_irq_no 7

#define LED_Green_Pin 0
#define LED_Green_Port GPIOA

extern uint32_t _estack;
extern uint32_t _Min_Stack_Size;

uint32_t volatile tick_counter;

struct poped_stack_t {
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r12;
	uint32_t lr;
	uint32_t pc;
	uint32_t xPRS;
};

int main(void)
{
    /* Loop forever */
	uint32_t val;
	struct poped_stack_t volatile * ps;
	volatile void ( * funk)(void);

	funk = &CallSVC;

	tick_counter = 0ul;

	//ClearStack();
	//NVIC->ISER[0] = 1 << 31;
	//NVIC->ICER[0] = 1 << 31;
	//DisableInterrupts();

	/* configure port and pins */
	RCC->AHB1ENR = (uint32_t) 1;

	val = GPIOA->MODER;
	val = val | (uint32_t)1;
	val = val | (uint32_t)1 << 4;
	GPIOA->MODER = val;

	val = GPIOA->OSPEEDR;
	val = val | 2 | ( 2 << 4);
	GPIOA->OSPEEDR = val;


	/* configure periphery interrupts */
	EXTI->IMR |= 2UL;
	EXTI->RTSR |= 2UL;
	SYSCFG->EXTICR[0] &= ~( 0xFUL << 4 );

	/* configure SysTICK */
	STK->VAL  = 0ul;
	STK->LOAD = 0x00FFFFFFul;
	val  = 0;
	val  = 1; /* bit 0 - enable systick */
	val |= ( 1 << 1 ); /* bit 1 - enable exeption on couting to zero */
	val |= ( 1 << 2 ); /* bit 2 = 1  choses processor clock as source */
	STK->CTRL = val;

	/* configure core interrupts */

	NVIC->ISER[0] = 1 << my_irq_no; // Enabling this EXTERNAL interrupt
	EnableInterrupts();

	//NVIC->ISPR[0] = 1 << my_irq_no;

	val = SCB->CPUID;
	val = SCB->CPUID;

	ChangeStack();
	//stack_marker(0x5a5a5a5a, 0xf0f0f0f0);
	//CallSVC();
	funk();

	Change2MainStack();

	while (1) {

		// NVIC->ISPR[0] = 1 << my_irq_no; // triger interrupt by seting its pending bit WORKED!!

		//delay(100000);
		//WaitForInterrupt();
		val = 1 << (16+2);
		//stack_marker(0x5a5a5a5a, 0xf0f0f0f0);

		//val = SCB->CPUID;
		//GPIOA->BSRR = val;
		//GPIOA->BSRR = 1 << 2;
		//delay(1000);

	}
}

void EXTI1_IRQHandler(void) {
	uint32_t val;
	struct poped_stack_t * ps;

	//stack_marker(0xa0a0a0a0, 0xe0e0e0e0);

	ps = Get_psp_addr();
	get_svc_type();
	val = GPIOA->ODR;
	if ( val & 4ul ) {
		GPIOA->BSRR = 1ul << (16+2);
	} else {
		GPIOA->BSRR = 1ul << 2;
	}

	//GPIOA->BSRR = 1 << 2;
	val = (2UL);
	EXTI->PR |= val;  // clear pending interrupt by setting this bit to 1
	//GPIOA->BSRR = 1 << (16+2) | 1;
	//delay(100);
	//GPIOA->BSRR = 1 << 2;
	//delay(1);
	return;
}

void SysTick_Handler(void) {
	uint32_t volatile val;

	//stack_marker(0x5a5a5a5a, 0xf0f0f0f0);
	val = GPIOA->ODR;
	if ( val & 1ul ) {
		GPIOA->BSRR = 1ul << 16;
	} else {
		GPIOA->BSRR = 1ul;
	}

	++tick_counter;
	return;
}

/*
void ClearStack(void) {
	uint32_t volatile * adr, indx;

	adr = _estack;
	for (indx = _Min_Stack_Size; indx > 0; --indx) {
		--adr;
		*adr = 0xA5A5A5A5UL;
	}
}
*/
void delay(uint32_t d) {
	uint32_t volatile x;
	for (; d > 0; --d) {
		x = d;
	}
	return;
}
