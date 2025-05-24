[org 0x0100]

jmp start  

array dw -10, 25, -5, 7, -15, 30, 2, -40, 18, 22  
min_value dw 0  
max_value dw 0  

start:
    mov si, array  
    mov cx, 10     
    mov ax, [si]   
    mov dx, ax     
    add si, 2    

next_element:
    mov bx, [si]   

    cmp bx, ax     
    jl update_min  

    cmp bx, dx     
    jg update_max

    jmp skip

update_min:
    mov ax, bx     

update_max:
    mov dx, bx     

skip:
    add si, 2    
    loop next_element

    mov [min_value], ax  
    mov [max_value], dx

    mov ax, 0x4c00
    int 0x21
