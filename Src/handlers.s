
	.syntax unified
	.cpu cortex-m4
	.thumb

	.global SVC_Handler
	.global NMI_Handler
  	.global HardFault_Handler
  	.global	MemManage_Handler
  	.global BusFault_Handler
  	.global	UsageFault_Handler


	@.extern _estack

	.type SVC_Handler, %function
SVC_Handler:
	push {lr}
	bl get_svc_type

	push {r0}
	ldr  r0, =CallSVC
	pop {r0}

	@	push {r4}

	@	sub sp, #4
	@	ldr r4, =0xDEADBEEF
	@	str r4, [sp]
	@	eor r4, r4
	@	ldr r4, [sp]
	@	add sp, #4

	mrs r4, control
	orr r4, #1
	msr control, r4
	isb

@	pop {r4}

	pop {lr}
	bx lr

	.type NMI_Handler, %function
NMI_Handler:
	bl .

	.type HardFault_Handler, %function
HardFault_Handler:
	bl .

	.type MemManage_Handler, %function
MemManage_Handler:
	bl .

	.type BusFault_Handler, %function
BusFault_Handler:
	bl .

	.type UsageFault_Handler, %function
UsageFault_Handler:
	bl .

