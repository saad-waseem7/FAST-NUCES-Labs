[org 0x0100]

jmp start  

array db 10  
N db 5         

start:
    mov si, array  
    mov al, [N]    
    call FillArray 

    mov ax, 0x4c00
    int 0x21

; ----------------- Recursive Subroutine: FillArray -----------------
FillArray:
    cmp al, 1      
    jl return_from_recursion

    mov [si], al   
    inc si         
    dec al         

    call FillArray 

return_from_recursion:
    ret
