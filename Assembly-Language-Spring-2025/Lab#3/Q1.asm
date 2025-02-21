[org 0x0100]

    mov cx, 5    
    mov ax, 1    

outer_loop:
    mov bx, ax
    mov dx, cx  
    mov ax, 0   

inner_loop:
    add ax, bx   
    dec dx       
    jnz inner_loop

    loop outer_loop

    mov ah, 0x4c
    int 0x21
