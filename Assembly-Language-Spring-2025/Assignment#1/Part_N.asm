[org 0x0100]
jmp start

num dw 6 

start:
    mov ax, cs
    mov ds, ax
    mov cx, [num]   
    call num_sum    

    jmp done

num_sum:
    cmp cx, 0
    je base_case  
    push cx       
    dec cx        
    call num_sum    
    pop cx        
    add ax, cx   
    ret

base_case:
    xor ax, ax    
    ret

done:
    mov ax, 0x4c00
    int 0x21