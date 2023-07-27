.section .text
printInt: .asciz "%d"

printStr: .asciz "%s"

printlnInt: .asciz "%d\n"

printlnStr: .asciz "%s\n"

.global main
.balign 4

factorial:
	push {lr}
	sub SP, SP, #32
	str r0, [SP, #0]
	ldr r0, [SP, #0]
	mov r1, #1
	str r1, [SP, #4]
	ldr r0, [SP, #0]
	ldr r1, [SP, #4]
	cmp r0, r1
	mov r0, #0
	movle r0, #1
	str r0, [SP, #8]
	ldr r0, [SP, #8]
	cmp r0, #1
	bne if0
	mov r0, #1
	str r0, [SP, #12]
	ldr r0, [SP, #12]
	b factorial_return
	b endif0
if0: @ here is a tag ---------- if0
	ldr r0, [SP, #0]
	ldr r0, [SP, #0]
	mov r1, #1
	str r1, [SP, #20]
	ldr r0, [SP, #0]
	ldr r1, [SP, #20]
	sub r2, r0, r1
	str r2, [SP, #24]
	ldr r5, [SP, #24]
	mov r0, r5
	bl factorial
	str r0, [SP, #16]
	mov r1, r0
	ldr r0, [SP, #0]
	mul r2, r0, r1
	str r2, [SP, #28]
	ldr r0, [SP, #28]
	b factorial_return
endif0: @ here is a tag ---------- endif0
factorial_return:
	add SP, SP, #32
	pop {pc}

main:
	push {lr}
	sub SP, SP, #36
	str r0, [SP, #0]
	str r1, [SP, #4]
	sub r0, r0, #1
	str r0, [r1, #0]
	mov r0, #0
	str r0, [SP, #8]
	ldr r0, [SP, #8]
	mov r1, #1
	str r1, [SP, #12]
	ldr r0, [SP, #8]
	ldr r1, [SP, #12]
	add r2, r0, r1
	str r2, [SP, #16]
	ldr r0, [SP, #16]
	mov r1, #4
	str r1, [SP, #20]
	ldr r0, [SP, #16]
	ldr r1, [SP, #20]
	mul r2, r0, r1
	str r2, [SP, #24]
	ldr r0, [SP, #24]
	ldr r1, [SP, #4]
	ldr r1, [r1, r0]
	mov r0, r1
	bl atoi
	str r0, [SP, #-100]
	str r0, [SP, #28]
	ldr r5, [SP, #28]
	mov r0, r5
	bl factorial
	str r0, [SP, #32]
	mov r1, r0
	ldr r0, =printlnInt
	bl printf
main_return:
	add SP, SP, #36
	pop {pc}
