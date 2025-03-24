[org 0x0100]
jmp start

str1 db "Hello, World", 0  
str2 db 0          

start:
    mov ax, cs
    mov ds, ax  
    mov es, ax  
    mov si, str1
    mov di, str2
    mov cx, 14          
    cld                 
    rep movsb           

    mov ax, 0x4c00
    int 0x21
