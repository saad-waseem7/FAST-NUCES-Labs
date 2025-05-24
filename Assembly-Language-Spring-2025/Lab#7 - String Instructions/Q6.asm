[org 0x0100]
jmp start

compString: db 'ggggdddddddyyyyakxxxuww', 0

CompressStr:
    push bp
    mov bp, sp
    push es
    pusha
    push ds
    pop es
    xor ax, ax
    mov cx, 0xffff
    mov di, [bp + 4]
    repne scasb
    mov ax, 0xffff
    sub ax, cx
    mov cx, ax
    dec cx
    jz term_compr
    mov si, [bp + 4]
    mov di, [bp + 4]

compress_str:
    inc cx
    mov al, [di]
    repe scasb
    mov [si], al
    inc si
    dec di
    cmp cx, 0
    jnz compress_str
    mov byte [si], 0

term_compr:
    popa
    pop es
    pop bp
    ret 2

clrscrn:
    push es
    push ax
    push cx
    push di
    mov ax, 0xb800
    mov es, ax
    xor di, di
    mov ax, 0x0720
    mov cx, 2000
    cld
    rep stosw
    pop di
    pop cx
    pop ax
    pop es
    ret

printstr:
    push bp
    mov bp, sp
    push es
    pusha
    push ds
    pop es
    mov di, [bp+4]
    mov cx, 0xffff
    xor al, al
    repne scasb
    mov ax, 0xffff
    sub ax, cx
    dec ax
    jz exit
    mov cx, ax
    mov ax, 0xb800
    mov es, ax
    mov al, 80
    mul byte [bp+8]
    add ax, [bp+10]
    shl ax, 1
    mov di, ax
    mov si, [bp+4]
    mov ah, [bp+6]
    cld

nextchar:
    lodsb
    stosw
    loop nextchar
    
exit:
    popa
    pop es
    pop bp
    ret 8

start:
    call clrscrn
    push word 0
    push word 7
    push word 0x07
    push word compString
    call printstr
    push word compString
    call CompressStr
    push word 0
    push word 8
    push word 0x07
    push word compString
    call printstr
    mov ax, 0
    int 0x16
    mov ax, 0x4c00
    int 0x21