.syntax unified
.cpu cortex-m3
.text
	.thumb


	.thumb_func
	.global OS_getStackPointer
OS_getStackPointer:
	add r0, sp, #0
	bx lr


	.thumb_func
	.global handler_PendSV
handler_PendSV:
	cpsid i

	@ if(OS_currentTask)
	ldr r0, =OS_currentTask
	ldr r1, [r0]	@ dereference &OS_currentTask
	cmp r1, #0
	beq PendSV_restore

	push {r4-r11}	@ save registers not saved automatically by ISR

	str sp, [r1]	@ OS_currentTask->stp = stack pointer

PendSV_restore:
	@ OS_currentTask=OS_nextTask
	ldr r1, =OS_nextTask
	ldr r1, [r1]
	str r1, [r0]

	ldr sp, [r1]	@ switch context


	ldr r0, =OS_switchCounter
	ldr r1, [r0]
	add r1, #1
	str r1, [r0]


	pop {r4-r11}	@ restore registers not tracked by ISR

	cpsie i

@	bl breakpoint
@	mov lr, #0xFFFFFFF9

	bx lr


	.thumb_func
	.global copy_registers
copy_registers:
	ldr r0, =panic_registers

	str r0, [r0,#0]
	str r1, [r0,#4]
	str r2, [r0,#8]
	str r3, [r0,#12]
	str r4, [r0,#16]
	str r5, [r0,#20]
	str r6, [r0,#24]
	str r7, [r0,#28]
	str r8, [r0,#32]
	str r9, [r0,#36]
	str r10, [r0,#40]
	str r11, [r0,#44]
	str r12, [r0,#48]
	str r13, [r0,#52]

	mov r1, r14
	str r1, [r0,#56]

	mov r1, r15
	str r1, [r0,#60]

	mrs r1, psr
	str r1, [r0,#64]

	bx lr
