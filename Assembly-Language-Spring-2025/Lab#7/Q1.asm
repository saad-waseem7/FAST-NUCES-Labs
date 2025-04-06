[org 0x0100] 

    mov si, myStr  
    mov cl, 0      
    mov al, 'a'    

count_loop:
    lodsb          
    cmp al, '$'    
    je display_count 
    cmp al, 'a'    ; Compare with target character
    jne count_loop 
    inc cl         
    jmp count_loop 

display_count:
    add cl, '0'    
    mov dl, cl     
    mov ah, 2      
    int 0x21       
    mov ax, 0x4c00 
    int 0x21     

myStr db 'I am a student of coal$', 0  