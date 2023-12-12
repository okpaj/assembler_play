
	.syntax unified
	.cpu cortex-m4
	.thumb

	.global EnableInterrupts
	.global DisableInterrupts
	.global ClearStack
	.global WaitForInterrupt
	.global CallSVC
	.global ChangeStack
	.global Change2MainStack
	.global stack_marker
	.global Get_psp_addr
	.global get_svc_type


	@.extern _estack

	.type EnableInterupts, %function
EnableInterrupts:
	cpsie i
	bx lr

	.type DisableInterrupts, %function
DisableInterrupts:
	cpsid i
	bx lr

	.type ClearStack, %function
ClearStack:
	ldr r0, =_estack
	ldr r1, =_Min_Stack_Size
	sub r0, #4

	ldr r2, =0xa5a5a5a5

cs_loop:
	@push r2
	@subs r1, #4
	str r2, [r0]
	sub r0, #4
	subs r1, #4
	bne cs_loop

	bx lr

	.type WaitForInterrupt, %function
WaitForInterrupt:
	wfi
	bx lr

	.align 2
	.type CallSVC, %function
CallSVC:
	svc #1
	bx lr


	.type ChangeStack, %function
ChangeStack:
	mrs r0, control
	mov r1, sp      @ if this is called in thread mode stack is still main
					@ but what when this routine called in handler mode?!?!
					@

	sub r1, #1024   @ it will be thread stack address

	orr r0, #2
	msr control, r0  @ from now thread mode will use PSP
	isb
	mov sp, r1       @ assuming we are in thread mode it sets PSP stack
					 @ TODO - verify beheviour of routine depending on
					 @ is this called in Handler
	bx lr

	.type Change2MainStack, %function
Change2MainStack:
	mrs r0, control
	@mvn r1, #2
	bic r0, #2
	msr control, r0
	isb
	bx lr

	.type stack_marker, %function
stack_marker:
	push {r0, r1}
	pop  {r0, r1}

	bx lr

	.type Get_psp_addr, %function
Get_psp_addr:
	mrs r0, psp

	bx lr

	.type get_svc_type, %function
get_svc_type:
	mrs r0, psp 			@ load stack pointer of interrupted thread

	ldr r1, [r0, #(6*4)]	@ load PC from thread stack => OK

	ldr r2, [r1, #-4]		@ load instruction before interrupt -> somehow
							@ this offset is not proper, very close but not
							@ in DF## (svc ##) instruction.
							@ Maybe -4 is working in ARM mode for all instructions
							@ being 32 bit. But for CM offset and PC is differnt
							@ depending on size of instruction
	ldr r2, [r1, #-2]


	bx lr
