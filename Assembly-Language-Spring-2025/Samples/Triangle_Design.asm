[org 0x0100]

jmp start

currentcol: dw 40
currentrow: dw 12
dollarbaseloc: dw 0 

clr_scr:
    push es
    push ax
    push di
    mov ax, 0xb800
    mov es, ax
    mov di, 0
next_loc:
    mov word [es:di], 0x0720
    add di, 2
    cmp di, 4000
    jne next_loc
    pop di
    pop ax
    pop es
    ret

cal_loc:
    push bp
    mov bp, sp
    mov dx, [currentrow] ; storing row in dx
    mov ax, 80 
    mov bx, [currentcol] ; storing column in bx
    mul dx
    add ax, bx
    shl ax, 1
    pop bp
    ret

star:
    push bp
    mov bp, sp
    push es
    mov ax, 0xb800
    mov es, ax
    mov di, [bp+4]
    mov word [es:di], 0x032a
    pop es
    mov sp, bp
    pop bp
    ret 2

dollar:
    push bp
    mov bp, sp
    push es
    mov ax, 0xb800
    mov es, ax
    mov di, [bp+4]
    mov word [es:di], 0x0124
    pop es
    mov sp, bp
    pop bp
    ret 2

andd:
    push bp
    mov bp, sp
    push es
    mov ax, 0xb800
    mov es, ax
    mov di, [bp+4]
    mov word [es:di], 0x0226
    pop es
    mov sp, bp
    pop bp
    ret 2

fwd:
    push bp
    mov bp, sp
    push es
    mov ax, 0xb800
    mov es, ax
    mov di, [bp+4]
    mov word [es:di], 0x072f
    pop es
    mov sp, bp
    pop bp
    ret 2

bkd:
    push bp
    mov bp, sp
    push es
    mov ax, 0xb800
    mov es, ax
    mov di, [bp+4]
    mov word [es:di], 0x075C
    pop es
    mov sp, bp
    pop bp
    ret 2

us:
    push bp
    mov bp, sp
    push es
    mov ax, 0xb800
    mov es, ax
    mov di, [bp+4]
    mov word [es:di], 0x075F
    pop es
    mov sp, bp
    pop bp
    ret 2

start:
    call clr_scr
    call cal_loc
    push ax
    call dollar
    mov cx, 3

right_edge:
    mov dx, [currentcol]
    add dx, 1
    mov bx, [currentrow]
    add bx, 1
    mov [currentcol], dx
    mov [currentrow], bx
    call cal_loc
    push ax
    call bkd
    sub cx, 1
    jnz right_edge

    mov ax, 12
    mov [currentrow], ax
    mov ax, 40
    mov [currentcol], ax
    mov cx, 3

left_edge:
    mov dx, [currentcol]
    dec dx
    mov bx, [currentrow]
    add bx, 1
    mov [currentcol], dx
    mov [currentrow], bx
    call cal_loc
    push ax
    call fwd
    sub cx, 1
    jnz left_edge

asterisk:
    mov dx, [currentcol]
    dec dx
    mov bx, [currentrow]
    add bx, 1
    mov [currentcol], dx
    mov [currentrow], bx
    call cal_loc
    push ax
    call star
    mov cx, 7

baseline:
    mov dx, [currentcol]
    inc dx
    mov [currentcol], dx
    call cal_loc
    push ax
    call us
    sub cx, 1
    jnz baseline

the_and:
    mov dx, [currentcol]
    inc dx
    mov [currentcol], dx
    call cal_loc
    push ax
    call andd
    mov ax, 0x4C00
    int 0x21