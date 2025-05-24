[org 0x0100]

mov ax, 0xB800  
mov es, ax     
mov di, 0      

mov cx, 2000   
mov al, 0      

print_blinking:
    mov ah, 0x87  ; Blinking high-intensity attribute
    mov [es:di], ax
    add di, 2
    inc al  
    loop print_blinking

mov ax, 0x4c00
int 0x21
