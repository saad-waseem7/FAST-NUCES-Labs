[org 0x0100]   

    mov cx, 5    ; num = 5
    mov ax, 0   

repeat_addition:
    add ax, 5  
    loop repeat_addition  

    mov ah, 0x4c
    int 0x21
