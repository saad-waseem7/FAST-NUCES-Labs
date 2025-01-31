; Square of 6 using byte-size operations
[org 0x0100]  ; Origin directive for DOS COM file

mov cl, 6     
mov al, 0    
mov bl, 6    

square_loop_byte:
    add al, bl  
    loop square_loop_byte

mov ax, 0x4c00
int 0x21