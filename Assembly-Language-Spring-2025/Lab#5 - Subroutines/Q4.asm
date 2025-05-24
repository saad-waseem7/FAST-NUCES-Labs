[org 0x0100]

jmp start

num db 5
result dw 0  

start:
    mov al, [num]    
    cbw              
    push ax         
    call Factorial  
    pop ax         
    mov [result], ax 

    mov ax, 0x4c00
    int 0x21

Factorial:
    pop cx          
    pop ax           

    cmp ax, 1
    jle base_case    

    dec ax
    push ax          
    call Factorial  
    pop bx          

    mul bx         
    push ax        
    push cx         
    ret

base_case:
    mov ax, 1
    push ax         
    push cx         
    ret
