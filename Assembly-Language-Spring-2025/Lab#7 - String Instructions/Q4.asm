[org 0x0100]

    mov si, myStr
    mov di, myStr
    mov al, 'c'

remove_loop:
    lodsb
    cmp al, '$'
    je display_string
    cmp al, 'c'
    je remove_loop
    stosb
    jmp remove_loop

display_string:
    mov al, '$'
    stosb

    mov dx, myStr
    mov ah, 9
    int 0x21

    mov ax, 0x4c00
    int 0x21

myStr db 'cabccdefcfdcxyzcc$', 0