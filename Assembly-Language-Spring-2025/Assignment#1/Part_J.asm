[org 0x0100]
jmp start

string: db "hello, world", 0
result: db 0

start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov si, string
    mov di, result
    cld

convert:
    lodsb
    cmp al, 0
    je done
    cmp al, 'a'
    jb store
    cmp al, 'z'
    ja store
    sub al, 32

store:
    stosb
    jmp convert

done:
    mov ax, 0x4c00
    int 0x21