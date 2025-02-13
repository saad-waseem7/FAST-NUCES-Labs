[org 0x0100]    

    mov si, array1      
    mov di, array2 + 5  
    mov cx, 6          

reverse_loop:
    mov al, [si]    
    mov [di], al    
    inc si          
    dec di          
    loop reverse_loop

    mov ah, 0x4c
    int 0x21

array1 db 1, 2, 3, 4, 5, 6  
array2 db 0, 0, 0, 0, 0, 0  
