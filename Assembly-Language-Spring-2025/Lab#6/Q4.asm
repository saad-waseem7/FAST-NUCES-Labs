[org 0x0100]

mov ax, 0xB800  
mov es, ax     
mov di, 0      

mov cx, 2000   ; 4000 bytes / 2 (since each char takes 2 bytes)
mov al, 0      

print_ascii:
    mov ah, 0x07   ; Normal attribute
    mov [es:di], ax
    add di, 2
    inc al  
    loop print_ascii

mov ax, 0x4c00
int 0x21
