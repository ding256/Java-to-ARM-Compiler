.section .text
printInt: .asciz "%d"

printStr: .asciz "%s"

printlnInt: .asciz "%d\n"

printlnStr: .asciz "%s\n"

_true: .asciz "true"

_false: .asciz "false"

.global main
.balign 4

sqrt:
	push {lr}
	sub SP, SP, #60
	str r0, [SP, #0]
	mov r0, #0
	str r0, [SP, #4]
	ldr r0, [SP, #4]
	str r0, [SP, #8]
	mov r0, #0
	str r0, [SP, #12]
	ldr r0, [SP, #12]
	str r0, [SP, #16]
loop0: @ here is a tag ---------- loop0
	ldr r0, [SP, #16]
	ldr r1, [SP, #0]
	ldr r0, [SP, #16]
	ldr r1, [SP, #0]
	cmp r0, r1
	mov r0, #0
	movle r0, #1
	str r0, [SP, #20]
	ldr r0, [SP, #20]
	cmp r0, #1
	bne endloop0
	ldr r0, [SP, #16]
	mov r0, #2
	str r0, [SP, #24]
	ldr r1, [SP, #8]
	ldr r0, [SP, #24]
	ldr r1, [SP, #8]
	mul r2, r0, r1
	str r2, [SP, #28]
	mov r1, #1
	str r1, [SP, #32]
	ldr r0, [SP, #28]
	ldr r1, [SP, #32]
	add r2, r0, r1
	str r2, [SP, #36]
	ldr r0, [SP, #16]
	ldr r1, [SP, #36]
	add r2, r0, r1
	str r2, [SP, #40]
	ldr r0, [SP, #40]
	str r0, [SP, #16]
	ldr r0, [SP, #8]
	mov r1, #1
	str r1, [SP, #44]
	ldr r0, [SP, #8]
	ldr r1, [SP, #44]
	add r2, r0, r1
	str r2, [SP, #48]
	ldr r0, [SP, #48]
	str r0, [SP, #8]
	b loop0
endloop0: @ here is a tag ---------- endloop0
	ldr r0, [SP, #8]
	mov r1, #1
	str r1, [SP, #52]
	ldr r0, [SP, #8]
	ldr r1, [SP, #52]
	sub r2, r0, r1
	str r2, [SP, #56]
	ldr r0, [SP, #56]
	b sqrt_return
sqrt_return:
	add SP, SP, #60
	pop {pc}

isPrime:
	push {lr}
	sub SP, SP, #88
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
	mov r0, #0
	str r0, [SP, #12]
	ldr r0, [SP, #12]
	b isPrime_return
	b endif0
if0: @ here is a tag ---------- if0
	mov r0, #2
	str r0, [SP, #16]
	ldr r0, [SP, #16]
	str r0, [SP, #20]
loop1: @ here is a tag ---------- loop1
	ldr r0, [SP, #20]
	ldr r5, [SP, #0]
	mov r0, r5
	bl sqrt
	str r0, [SP, #24]
	mov r1, r0
	ldr r0, [SP, #20]
	ldr r1, [SP, #24]
	cmp r0, r1
	mov r0, #0
	movle r0, #1
	str r0, [SP, #28]
	ldr r0, [SP, #28]
	cmp r0, #1
	bne endloop1
	ldr r0, [SP, #0]
	str r0, [SP, #32]
	ldr r0, [SP, #20]
	str r0, [SP, #36]
	mov r0, #0
	str r0, [SP, #40]
	ldr r0, [SP, #40]
	str r0, [SP, #44]
loop2: @ here is a tag ---------- loop2
	ldr r0, [SP, #32]
	ldr r1, [SP, #36]
	ldr r0, [SP, #32]
	ldr r1, [SP, #36]
	cmp r0, r1
	mov r0, #0
	movge r0, #1
	str r0, [SP, #48]
	ldr r0, [SP, #48]
	cmp r0, #1
	bne endloop2
	ldr r0, [SP, #32]
	ldr r1, [SP, #36]
	ldr r0, [SP, #32]
	ldr r1, [SP, #36]
	sub r2, r0, r1
	str r2, [SP, #52]
	ldr r0, [SP, #52]
	str r0, [SP, #32]
	ldr r0, [SP, #44]
	mov r1, #1
	str r1, [SP, #56]
	ldr r0, [SP, #44]
	ldr r1, [SP, #56]
	add r2, r0, r1
	str r2, [SP, #60]
	ldr r0, [SP, #60]
	str r0, [SP, #44]
	b loop2
endloop2: @ here is a tag ---------- endloop2
	ldr r0, [SP, #32]
	mov r1, #0
	str r1, [SP, #64]
	ldr r0, [SP, #32]
	ldr r1, [SP, #64]
	cmp r0, r1
	mov r0, #0
	moveq r0, #1
	str r0, [SP, #68]
	ldr r0, [SP, #68]
	cmp r0, #1
	bne if1
	mov r0, #0
	str r0, [SP, #72]
	ldr r0, [SP, #72]
	b isPrime_return
	b endif1
if1: @ here is a tag ---------- if1
	ldr r0, [SP, #20]
	mov r1, #1
	str r1, [SP, #76]
	ldr r0, [SP, #20]
	ldr r1, [SP, #76]
	add r2, r0, r1
	str r2, [SP, #80]
	ldr r0, [SP, #80]
	str r0, [SP, #20]
endif1: @ here is a tag ---------- endif1
	b loop1
endloop1: @ here is a tag ---------- endloop1
	mov r0, #1
	str r0, [SP, #84]
	ldr r0, [SP, #84]
	b isPrime_return
endif0: @ here is a tag ---------- endif0
isPrime_return:
	add SP, SP, #88
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
	bl isPrime
	str r0, [SP, #32]
	ldr r0, [SP, #32]
	cmp r0, #1
	bne if2
	ldr r1, =_true
	ldr r0, =printlnStr
	bl printf
	b endif2
if2: @ here is a tag ---------- if2
	ldr r1, =_false
	ldr r0, =printlnStr
	bl printf
endif2: @ here is a tag ---------- endif2
main_return:
	add SP, SP, #36
	pop {pc}
