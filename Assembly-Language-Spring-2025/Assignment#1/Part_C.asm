[org 0x0100]
jmp start

string db "Hello, World", 0
length dw 12

start:
    mov cx, [length]
    mov si, string
    mov di, si

push_loop:
    mov al, [si]
    push ax
    inc si
    loop push_loop
    mov si, di

pop_loop:
    pop ax
    mov [si], al
    inc si
    loop pop_loop

    mov byte [si], 0

    mov ax, 0x4c00
    int 0x21