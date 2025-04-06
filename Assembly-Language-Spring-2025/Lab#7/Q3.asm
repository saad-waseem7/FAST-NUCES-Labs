[org 0x0100]

    mov si, myStr
    mov al, 'd'  ; Character to find
    mov ah, '$'  ; Character to replace with

replace_loop:
    lodsb
    cmp al, '$'
    je display_string
    cmp al, 'd'
    jne continue_loop
    mov byte [si-1], ah  ; Replace character

continue_loop:
    jmp replace_loop

display_string:
    mov dx, myStr
    mov ah, 9
    int 0x21

    mov ax, 0x4c00
    int 0x21

myStr db 'ddsdfhgrtsdfhjghjksdd$', 0
