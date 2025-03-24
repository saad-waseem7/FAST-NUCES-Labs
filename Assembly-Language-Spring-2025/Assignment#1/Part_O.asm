[org 0x0100]
jmp start

scrl_left:
    push bp
    mov bp, sp
    push ax
    push cx
    push si
    push di
    push es
    push ds
    mov ax, 2
    mul byte [bp+4]
    mov si, ax
    push si
    mov ax, 0xB800
    mov es, ax
    mov ds, ax
    mov cx, 2000
    sub cx, si
    xor di, di
    cld
    rep movsw
    mov ax, 0x0720
    pop cx

clear_last_column:
    mov di, 158
    add di, 160
    loop clear_last_column
    pop ds
    pop es
    pop di
    pop si
    pop cx
    pop ax
    pop bp
    ret 2

scrl_right:
    push bp
    mov bp, sp
    push ax
    push cx
    push si
    push di
    push es
    push ds

    mov ax, 2
    mul byte [bp+4]
    push ax
    shl ax, 1

    mov si, 1596
    sub si, ax
    mov ax, 0xB800
    mov es, ax
    mov ds, ax
    mov cx, 2000
    sub cx, ax
    mov di, 1598
    std
    rep movsw

    mov ax, 0x0720
    pop cx

clear_first_column:
    mov di, 0
    add di, 160
    loop clear_first_column
    pop ds
    pop es
    pop di
    pop si
    pop cx
    pop ax
    pop bp
    ret 2
    delay:
    xor cx, cx
    xor dx, dx
    mov cx, 40000

n1:
    mov dx, 80

n2:
    dec dx
    jnz n2
    loop n1
    ret

start:
    mov ax, 5
    push ax
    call scrl_left
    call delay
    mov ax, 5
    push ax
    call scrl_right
    call delay
    mov ax, 0x4c00
    int 0x21

