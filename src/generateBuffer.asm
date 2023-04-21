BITS 64

section .text
    global generate_buffer 

generate_buffer:
    push rbp 
    mov rbp,rsp 
    mov rbx,rdi ; rdi is the buffer address
    mov rcx,rsi ; rsi is the size value
    mov edx, 'A'
    xor rsi, rsi 

_beforeLoop:
    ; Goes to the end of the vulnerability name entered in this section.
    ; This is because the end of this vulnerability will be filled with AAAA in the next loop.
    cmp byte [rbx + rsi],0 ; check for null terminator
    je _loop 
    inc rsi 
    cmp rsi,rcx
    jge _returnBlock ; if size is greater than buffer size, return immediately
    jmp _beforeLoop

_loop:
    ; In this part, the vulnerability name starts to be filled with AAA at the end.
    mov [rbx + rsi],edx ; Here, A is added to the end of the vulnerability. Notice that the rsi register value increases below.
   ; For example, if we consider that the rbx register is VULN, now the rsi register will have the value 0x4. Then it will be added continuously increasing.
    inc rsi 
    cmp rsi,rcx ; rcx contains the buffer size entered by the user. If the rsi value is greater than rcx, the program will terminate.
    ; Otherwise it will continue to be filled with 'A' over and over with jmp.
    jge _returnBlock
    jmp _loop

_returnBlock:
    mov byte [rbx + rsi],0 ; add null terminator to end of buffer
    leave
    ret 