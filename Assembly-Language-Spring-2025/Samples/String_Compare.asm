[org 0x0100]
; Compare two strings and print the result
jmp start 

str1 db "hello", 0 
str2 db "hello", 0  
len1 db 0          
len2 db 0          

start:
    mov di, str1   
    call StrLength
    mov [len1], cl 
    mov di, str2   
    call StrLength
    mov [len2], cl 
    mov al, [len1]
    cmp al, [len2]
    jne not_equal  
    mov si, str1   
    mov di, str2   
    mov cx, ax     
    repe cmpsb     
    jne not_equal  
equal:
    mov dx, msg_equal
    jmp print

not_equal:
    mov dx, msg_not_equal

print:
    mov ah, 09h   
    int 21h        
    mov ax, 0x4c00
    int 0x21
StrLength:
    mov cl, 0     
    mov al, 0     
find_len:
    scasb         
    je done_len   
    inc cl      
    jmp find_len
done_len:
    dec cl       
    ret

msg_equal db "Strings are equal!$"
msg_not_equal db "Strings are not equal!$"
