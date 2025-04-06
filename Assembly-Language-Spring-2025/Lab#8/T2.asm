[org 0x0100]

jmp start

buffer: times 4000 db 0
message1: db 10, 13, 'Program started. $'
message2: db 10, 13, 'Message 22222... $'
message3: db 10, 13, 'Message 333... $'

sleep:
    push cx
    mov cx, 0xFFFF
delay:
    loop delay
    pop cx
    ret

clrscr:
    push es
    push ax
    push di
    mov ax, 0xb800
    mov es, ax
    mov di, 0
nextloc:
    mov word [es:di], 0x0720
    add di, 2
    cmp di, 4000
    jne nextloc
    pop di
    pop ax
    pop es
    ret

saveScreen:
    pusha
    mov cx, 4000
    mov ax, 0xb800
    mov ds, ax
    push cs
    pop es
    mov si, 0
    mov di, buffer
    cld
    rep movsb
    popa
    ret

restoreScreen:
    pusha
    mov cx, 4000
    mov ax, 0xb800
    mov es, ax
    push cs
    pop ds
    mov si, buffer
    mov di, 0
    cld
    rep movsb
    popa
    ret

start:
    call saveScreen
    mov ah, 0
    int 0x16
    call clrscr
    mov ah, 0
    int 0x16
    call restoreScreen
    mov ah, 0
    int 0x16
    mov ax, 0x4c00
    int 0x21


