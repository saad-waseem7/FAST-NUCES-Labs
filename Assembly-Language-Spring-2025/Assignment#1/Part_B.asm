[org 0x0100]
jmp start

num1: dw 15
num2: dw 20

start:
    push word [num1]
    push word [num2]
    pop word [num1]
    pop word [num2]

    mov ax, 0x4c00
    int 0x21