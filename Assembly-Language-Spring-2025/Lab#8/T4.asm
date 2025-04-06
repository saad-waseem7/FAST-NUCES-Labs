[org 0x0100]
jmp start

msg1 db 'My name is Muhammad Saad', 0Dh, 0Ah, '$'
msg2 db 'I am in coal lab', 0Dh, 0Ah, '$'
msg3 db 'Learning assembly language', 0Dh, 0Ah, '$'

print_string:
    push bp
    mov bp, sp
    push ax
    push dx
    mov dx, [bp+4]
    mov ah, 09h
    int 0x21
    pop dx
    pop ax
    pop bp
    ret 2

start:
    mov ax, msg1
    push ax
    call print_string

    mov ax, msg2
    push ax
    call print_string

    mov ax, msg3
    push ax
    call print_string

    mov ax, 0x4c00
    int 0x21
