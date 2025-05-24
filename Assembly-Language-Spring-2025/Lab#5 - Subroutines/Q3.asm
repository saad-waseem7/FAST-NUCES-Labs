[org 0x0100]

jmp start  

string db "Hello, World!", 0  
length db 0  
start:
    mov si, string  
    call StrLength  
    mov [length], cl  

    mov ax, 0x4c00
    int 0x21

; ----------------- Subroutine: Find String Length -----------------
StrLength:
    mov cl, 0      

count_loop:
    cmp byte [si], 0  
    je done_count
    inc si            
    inc cl            
    jmp count_loop

done_count:
    ret
