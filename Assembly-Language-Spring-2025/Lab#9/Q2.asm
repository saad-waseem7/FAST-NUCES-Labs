[org 0x0100]

start:
    mov ah, 09h
    mov dx, msg1
    int 21h

    mov ah, 01h         ; Read first digit
    int 21h
    sub al, '0'         ; Convert ASCII to number
    mov bl, al          ; Store first operand in BL

    mov ah, 09h
    mov dx, msg2
    int 21h

    mov ah, 01h         ; Read second digit
    int 21h
    sub al, '0'
    mov bh, al          ; Store second operand in BH

    mov ah, 09h
    mov dx, msg3
    int 21h

    mov ah, 01h         ; Read operator
    int 21h
    cmp al, 'E'
    je exit

    mov cl, al          ; Save operator in CL

    ; Perform operation
    mov al, bl          ; First number
    mov ah, bh          ; Second number

    cmp cl, '+'
    je do_add
    cmp cl, '-'
    je do_sub
    cmp cl, '*'
    je do_mul
    cmp cl, '/'
    je do_div
    jmp invalid

do_add:
    add al, ah
    jmp show_result

do_sub:
    sub al, ah
    jmp show_result

do_mul:
    mul ah
    jmp show_result

do_div:
    xor ah, ah
    cmp ah, 0
    je do_div_safe
    jmp invalid

do_div_safe:
    div ah
    jmp show_result

invalid:
    mov ah, 09h
    mov dx, msg_invalid
    int 21h
    jmp start

show_result:
    add al, '0'         ; Convert to ASCII
    mov dl, al
    mov ah, 02h
    int 21h

    jmp start

exit:
    mov ax, 4C00h
    int 21h

msg1 db 'Enter first digit: $'
msg2 db 13,10, 'Enter second digit: $'
msg3 db 13,10, 'Enter operator (+, -, *, /) or E to exit: $'
msg_invalid db 13,10, 'Invalid input!', 13,10, '$'
