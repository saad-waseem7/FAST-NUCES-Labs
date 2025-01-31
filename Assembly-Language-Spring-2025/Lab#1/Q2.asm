[org 0x0100] 

mov cx, 5     
mov ax, 0     
mov bx, 3     

sum_loop:
    add ax, bx  
    add bx, 3   
    loop sum_loop 

mov ax, 0x4c00
int 0x21
