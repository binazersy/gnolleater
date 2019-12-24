; hello_world.asm
;
; Author: binazersy@gmail.com

global _start

section .text:

_start:
	mov eax, 0x4		; use the write syscall
	mov ebx, 1		; use stdout as the fd
	mov ecx, message	
	mov edx, message_length	
	int 0x80		; invoke the syscall


	mov eax, 0x1		; exit syscall
	mov ebx, 0
	int 0x80

section .data:
	message: db "Hello World!", 0xA
	message_length equ $-message
