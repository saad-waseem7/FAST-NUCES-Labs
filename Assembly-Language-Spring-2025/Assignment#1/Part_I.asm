[org 0x0100]
jmp start

string: db "Hello, World", 0
target: db 'W'

start:
    mov ax, cs
    mov es, ax
    mov di, string
    mov al, [target]
    mov cx, 0FFFFh
    cld
    repne scasb
    jne not_found
    jmp done

not_found:
    jmp done

done:
    mov ax, 0x4c00
    int 0x21