[org 0x0100]
jmp start

string: db "civic", 0

start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov si, string
    call length_loop_l1
    mov si, string
    mov di, si
    add di, cx
    dec di
    shr cx, 1
    cld

palindrome_1:
    lodsb
    std
    scasb
    jne palindrome_2
    cld
    loop palindrome_1
    mov ax, 1
    jmp done

palindrome_2:
    mov ax, 0

done:
    mov ax, 0x4c00
    int 0x21  

length_found:
    ret    

length_loop_l1:
    mov cx, 0    
        
length_loop_l2:
    lodsb
    cmp al, 0        
    je length_found
    inc cx
    jmp length_loop_l2

