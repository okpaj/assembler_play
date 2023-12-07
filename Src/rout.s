
	.syntax unified
	.cpu cortex-m4
	.thumb

	.global EnableInterrupts
	.global DisableInterrupts


	.type EnableInterupts, %function
EnableInterrupts:
	cpsie i
	bx lr

	.type DisableInterrupts, %function
DisableInterrupts:
	cpsid i
	bx lr
