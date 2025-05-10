[org 0x0100]

jmp start

clrscr:
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
printRectangle:
        push bp
        mov bp, sp
        push es
        push ax
        push cx
        push di
        mov ax, 0xb800
        mov es, ax
        mov al, 80
        mul byte [bp+12]
        add ax, [bp+10]
        shl ax, 1
        mov di, ax
        mov ah, [bp+4]
        mov cx, [bp+6]
        sub cx, [bp+10]
topLine:
        mov al, 0x2A
        mov [es:di], ax
        add di, 2
        loop topLine
        mov cx, [bp+8]
        sub cx, [bp+12]
        add di, 160
rightLine:
        mov al, 0x2A
        mov [es:di], ax
        add di, 160
        loop rightLine
        mov cx, [bp+6]
        sub cx, [bp+10]
        sub di, 2
bottomLine:
        mov al, 0x2A
        mov [es:di], ax
        sub di, 2
        loop bottomLine
        mov cx, [bp+8]
        sub cx, [bp+12]
        sub di, 160
leftLine:
        mov al, 0x2A
        mov [es:di], ax
        sub di, 160
        loop leftLine
        pop di
        pop cx
        pop ax
        pop es
        pop bp
        ret 10
start:
        call clrscr
        mov ax, 2
        push ax
        mov ax, 10
        push ax
        mov ax, 20
        push ax
        mov ax, 60
        push ax
        mov ax, 0x07
        push ax
        call printRectangle
        mov ax, 0x4c00
        int 0x21