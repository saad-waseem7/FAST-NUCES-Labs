[org 0x0100]
jmp start

ClearScreen:
    push bp
    mov bp, sp
    push ax
    push bx
    push cx
    push di
    push es
    push ds

    cld
    pushf
    pop ax
    test ah, 1
    jnz int_call

    mov bx, sp
    add bx, 4
    cmp bx, bp
    je far_call

near_call:
    call clear_screen
    jmp return_near

far_call:
    call clear_screen
    jmp return_far

int_call:
    call clear_screen
    jmp return_int

clear_screen:
    mov ax, 0xb800
    mov es, ax
    xor di, di
    mov cx, 2000
    mov ax, 0x0720
    rep stosw
    ret

return_near:
    pop ds
    pop es
    pop di
    pop cx
    pop bx
    pop ax
    pop bp
    ret

return_far:
    pop ds
    pop es
    pop di
    pop cx
    pop bx
    pop ax
    pop bp
    retf

return_int:
    pop ds
    pop es
    pop di
    pop cx
    pop bx
    pop ax
    pop bp
    iret

start:
    mov ax, 0
    push ax
    call ClearScreen

    mov ax, 0x4c00
    int 0x21
