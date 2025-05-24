[org 0x0100]

jmp start  

; Data section (Two 32-bit numbers)
num1 dw 0x1234, 0x5678   
num2 dw 0x9ABC, 0xDEF0   
result dw 4 dup(0)       

start:
    mov ax, [num1]   
    mov dx, [num1+2] 
    mov bx, [num2]   
    mov cx, [num2+2] 

    mul bx         
    mov [result], ax  
    mov [result+2], dx 

    mov ax, [num1+2] 
    mul bx           
    add [result+2], ax  
    adc [result+4], dx  

    mov ax, [num1]   
    mul cx           
    add [result+2], ax 
    adc [result+4], dx 

    mov ax, [num1+2] 
    mul cx           
    add [result+4], ax  
    adc [result+6], dx  

    mov ax, 0x4c00
    int 0x21
