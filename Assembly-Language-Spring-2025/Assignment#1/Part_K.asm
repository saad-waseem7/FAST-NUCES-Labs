[org 0x0100]
jmp start

string db "hello world", 0
target db 'o'
replace db 'X'

start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov si, string
    mov al, [target]
    push ax
    mov al, [replace]
    push ax
    call ReplaceChar
    mov ax, 0x4c00
    int 0x21

ReplaceChar:
    push bp
    mov bp, sp
    push si
    push di
    push ax
    push bx
    mov di, si
    mov ah, [bp+4]
    mov bl, [bp+6]
    cld

replace_loop:
    lodsb
    cmp al, 0
    je done
    cmp al, bl
    jne store_char
    mov al, ah

store_char:
    stosb
    jmp replace_loop

done:
    pop bx
    pop ax
    pop di
    pop si
    pop bp
    ret 4