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
    cmp byte [rbx + rsi],0 ; check for null terminator
    je _loop 
    inc rsi 
    cmp rsi,rcx
    jge _returnBlock ; if size is greater than buffer size, return immediately
    jmp _beforeLoop

_loop:
    mov [rbx + rsi],edx    
    inc rsi 
    cmp rsi,rcx
    jge _returnBlock ; if size is greater than buffer size, return immediately
    jmp _loop

_returnBlock:
    mov byte [rbx + rsi],0 ; add null terminator to end of buffer
    leave
    ret 