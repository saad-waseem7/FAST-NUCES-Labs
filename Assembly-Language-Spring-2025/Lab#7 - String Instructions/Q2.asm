[org 0x0100]

mov si, myStr
print_loop:
    lodsb
    cmp al, '$'
    je end_program
    cmp al, ' '
    je print_newline
    mov dl, al
    mov ah, 2
    int 0x21
    jmp print_loop

print_newline:
    mov dx, newline
    mov ah, 9
    int 0x21
    jmp print_loop

end_program:
    mov ax, 0x4c00
    int 0x21

myStr db 'I am a student of coal$', 0
newline db 13, 10, '$'
