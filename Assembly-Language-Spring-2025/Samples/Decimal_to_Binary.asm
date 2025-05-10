[org 0x0100]

jmp start

decimal_num: dw 13              ; Number to be converted (example: 13)
binary_result: times 16 db 0    ; Array to store binary result (max 16 bits)
bit_count: db 0                 ; Counter for number of bits stored

convert_to_binary:
    push bp    
    mov bp, sp        
    push ax   
    push bx
    push cx
    push dx
    push si
    mov ax, [bp+6] 
    mov bx, [bp+8]    
    mov si, 0  
    mov byte [bit_count], 0 
    cmp ax, 0         
    jne convert_loop  
    mov byte [bx], 0  
    mov byte [bit_count], 1
    jmp done_conversion

convert_loop:
    cmp ax, 0   
    je done_conversion
    xor dx, dx        
    mov cx, 2      
    div cx           
    mov [bx+si], dl   
    inc si            
    inc byte [bit_count] 
    jmp convert_loop

done_conversion:
    pop si     
    pop dx
    pop cx
    pop bx
    pop ax
    pop bp

    ret 4     

start:
    mov ax, [decimal_num] 
    push ax        
    mov ax, binary_result  
    push ax                 
    call convert_to_binary  
    mov ax, 0x4c00
    int 0x21