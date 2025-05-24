[org 0x0100]
jmp start

highString: db 'I am a student of COAL', 0
subString: db 'student', 0

HighStr:
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
    jz term_high
    inc cx
    push cx
    xor ax, ax
    mov cx, 0xffff
    mov di, [bp + 6]
    repne scasb
    mov bx, 0xffff
    sub bx, cx
    pop cx
    sub bx, cx
    jl term_high
    push word [bp + 12]
    push word [bp + 10]
    push word [bp + 8]
    push word [bp + 6]
    call printstr
    dec bx
    mov si, [bp + 6]
    mov di, [bp + 4]
    mov ax, si
    push si
    push cx

rep_compare:
    repe cmpsb
    jcxz found
    pop cx
    pop ax
    push si
    push cx
    mov di, [bp + 4]
    dec bx
    jnz rep_compare

term_high:
    pop cx
    pop si
    popa
    pop es
    pop bp
    ret 4

found:
    pop cx
    pop si
    push si
    push cx
    push word 0xb800
    pop es
    dec cx
    mov al, 80
    mul byte [bp+10]
    add ax, [bp+12]
    sub si, [bp + 6]
    add si, ax
    shl si, 1

highlight:
    mov byte [es:si + 1], 0x40
    add si, 2
    loop highlight
    jmp term_high

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
    push word 3
    push word 0x07
    push word highString
    call printstr
    push word 0
    push word 4
    push word 0x07
    push word subString
    call printstr
    push word 0
    push word 5
    push word 0x07
    push word highString
    push word subString
    call HighStr
    mov ax, 0
    int 0x16
    mov ax, 0x4c00
    int 0x21