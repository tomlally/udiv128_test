SECTION .text

global h 

h:
    mov rax, rcx
    div r8
    mov [r9], rdx
    ret
