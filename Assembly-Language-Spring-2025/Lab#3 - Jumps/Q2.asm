[org 0x0100]      

    mov si, 0     
    mov di, 1      

loop_start:
    mov al, [arr + si]      
    cmp al, [arr + si + 1]  
    je skip_duplicate       

    mov [arr + di], al      
    inc di                  

skip_duplicate:
    inc si                  
    cmp si, size - 1       
    jl loop_start           

fill_zeros:
    cmp di, size           
    jge end_program
    mov byte [arr + di], 0  
    jmp fill_zeros          

end_program:
    mov ah, 0x4c
    int 0x21

arr db 2,2,2,3,4,4,5,5,5,6  
size equ 10                 
