org 100h

CompressData:
    push bp
    mov bp, sp
    push es
    push di
    push si
    push cx
    push ax
    push bx

    mov ax, 0xB800
    mov es, ax

    mov ax, [bp+4]
    mov bx, 160
    mul bx
    mov bx, [bp+6]
    shl bx, 1
    add ax, bx
    mov di, ax

    mov al, byte [es:di]
    cmp al, 0x20
    je done

    mov cx, 80
    lea si, [di+2]

scan_row:
    mov ah, byte [es:si]
    cmp ah, al
    jne shift_left

    add si, 2
    loop scan_row
    jmp done

shift_left:
    lea di, [di+2]
    lea si, [di+2]
    rep movsw

    mov al, 0x20
    mov ah, byte [es:di]

fill_spaces:
    stosw
    loop fill_spaces

done:
    pop bx
    pop ax
    pop cx
    pop si
    pop di
    pop es
    pop bp
    ret