[org 0x0100]
jmp start

counter:
    dw 0

ISR_60h:
    push ax
    push bx
    push cx
    push dx

    mov ax, cs
    mov ds, ax

    inc word [counter]

    mov ax, [counter]
    call print_hex

    pop dx
    pop cx
    pop bx
    pop ax
    iret

print_hex:
    push ax
    push bx
    push cx
    push dx

    mov bx, ax
    mov cx, 4

hex_loop:
    rol bx, 4
    mov dl, bl
    and dl, 0x0F
    add dl, '0'
    cmp dl, '9'
    jbe print_digit
    add dl, 7

print_digit:
    mov ah, 0x0E
    int 0x10

    loop hex_loop

    pop dx
    pop cx
    pop bx
    pop ax
    ret

start:
    mov ax, 0x3500 + 0x60
    int 0x21
    mov [old_int60], bx
    mov [old_int60+2], es

    mov dx, ISR_60h
    mov ax, 0x2500 + 0x60
    int 0x21

    mov cx, 5

test_loop:
    int 0x60
    loop test_loop

    mov dx, [old_int60]
    mov ds, [old_int60+2]
    mov ax, 0x2500 + 0x60
    int 0x21

    mov ax, 0x4C00
    int 0x21

old_int60 dw 0, 0
