[org 0x0100]

start:
    mov ax, 0B25Dh 

    mov bx, ax      
    and ax, 0xAAAA  
    and bx, 0x5555  

    shr ax, 1       
    shl bx, 1       
    or ax, bx       

    mov ax, 0x4c00
    int 0x21
