[org 0x0100]  

; Square of 6 using word-size operations
mov cx, 6     
mov ax, 0     
mov bx, 6  

square_loop:
    add ax, bx  
    loop square_loop

mov ax, 0x4c00
int 0x21