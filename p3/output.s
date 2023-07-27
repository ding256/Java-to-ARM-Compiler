.section .text
printInt: .asciz "%d"

printStr: .asciz "%s"

printlnInt: .asciz "%d\n"

printlnStr: .asciz "%s\n"

.global main
.balign 4
main:
	push {lr}
	sub SP, SP, #96
	str r0, [SP, #0]
	str r1, [SP, #4]
	sub r0, r0, #1
	str r0, [r1, #0]
	ldr r0, =0
	str r0, [SP, #8]
	ldr r0, [SP, #8]
	ldr r1, =1
	str r1, [SP, #12]
	ldr r0, [SP, #8]
	ldr r1, [SP, #12]
	add r2, r0, r1
	str r2, [SP, #16]
	ldr r0, [SP, #16]
	ldr r1, =4
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
	str r0, [SP, #28]

	ldr r0, =1
	str r0, [SP, #32]
	ldr r0, [SP, #32]
	ldr r1, =1
	str r1, [SP, #36]
	ldr r0, [SP, #32]
	ldr r1, [SP, #36]
	add r2, r0, r1
	str r2, [SP, #40]
	ldr r0, [SP, #40]
	ldr r1, =4
	str r1, [SP, #44]
	ldr r0, [SP, #40]
	ldr r1, [SP, #44]
	mul r2, r0, r1
	str r2, [SP, #48]
	ldr r0, [SP, #48]
	ldr r1, [SP, #4]
	ldr r1, [r1, r0]
	mov r0, r1
	bl atoi
	str r0, [SP, #52]

	ldr r0, =2
	str r0, [SP, #56]
	ldr r0, [SP, #56]
	ldr r1, =1
	str r1, [SP, #60]
	ldr r0, [SP, #56]
	ldr r1, [SP, #60]
	add r2, r0, r1
	str r2, [SP, #64]
	ldr r0, [SP, #64]
	ldr r1, =4
	str r1, [SP, #68]
	ldr r0, [SP, #64]
	ldr r1, [SP, #68]
	mul r2, r0, r1
	str r2, [SP, #72]
	ldr r0, [SP, #72]
	ldr r1, [SP, #4]
	ldr r1, [r1, r0]
	mov r0, r1
	bl atoi
	str r0, [SP, #76]

	ldr r0, [SP, #28]
	ldr r1, [SP, #52]
	ldr r0, [SP, #28]
	ldr r1, [SP, #52]
	mul r2, r0, r1
	str r2, [SP, #80]
	ldr r0, =300
	str r0, [SP, #84]
	ldr r1, [SP, #76]
	ldr r0, [SP, #84]
	ldr r1, [SP, #76]
	mul r2, r0, r1
	str r2, [SP, #88]
	ldr r0, [SP, #80]
	ldr r1, [SP, #88]
	sub r2, r0, r1
	str r2, [SP, #92]
	ldr r1, [SP, #92]
	ldr r0, =printlnInt
	bl printf

	add SP, SP, #96
	pop {pc}
