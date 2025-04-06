[org 0x0100]

start:
    mov dx, msg1
    mov ah, 09h
    int 0x21
    mov ah, 08h
    int 0x21
    mov bl, al
    mov dx, msg2
    mov ah, 09h
    int 0x21
    mov cl, 4
    mov al, bl
    shr al, cl
    call print_hex_digit
    mov al, bl
    and al, 0x0F
    call print_hex_digit

    mov ax, 0x4C00
    int 0x21

print_hex_digit:
    add al, 0x30
    cmp al, 0x39
    jle print_char
    add al, 7

print_char:
    mov ah, 02h
    mov dl, al
    int 0x21
    ret

msg1 db 'Enter a character: $'
msg2 db 'ASCII code: $'
