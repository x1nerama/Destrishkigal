section .data
	buffer: db "dfsdsdsof:", 64

section .text
	global _start

_start:
	mov ecx,32 
	mov eax,buffer
	mov edx,65
	mov ebx,0
	xor esi,esi

_beforeLoop:
	cmp byte [buffer + esi],64
	je _loop

	inc esi 
	jmp _beforeLoop

_loop:
	mov [eax + esi],edx 
	cmp ecx,0
	je _printMessage
	inc esi
	loop _loop

_printMessage:
	mov eax,4
	mov ebx,1
	mov ecx,buffer
	mov edx,32
	int 0x80

	mov eax,1
	xor ebx,ebx
	int 0x80
	
