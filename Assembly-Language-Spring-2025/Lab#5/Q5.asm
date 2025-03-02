[org 0x0100]

jmp start

num1 db 12
num2 db 25
num3 db 18
result db 0

start:
    push word [num1]
    push word [num2]
    push word [num3]

    call FindMax

    pop ax
    mov [result], al

    mov ax, 0x4c00
    int 0x21

FindMax:
    push bp
    mov bp, sp
    sub sp, 2

    push ax
    push bx
    push cx

    mov al, [bp+4]
    mov bl, [bp+6]
    mov cl, [bp+8]

    mov [bp-2], al

    cmp bl, [bp-2]
    jle check_num3
    mov [bp-2], bl

check_num3:
    cmp cl, [bp-2]
    jle store_max
    mov [bp-2], cl

store_max:
    mov ax, [bp-2]
    push ax

    pop cx
    pop bx
    pop ax

    mov sp, bp
    pop bp
    ret 6