[org 0x0100]

jmp start  ; Jump over data

; Data section (Two 64-bit numbers stored as 4 words each)
num1 dw 0xFFFF, 0x1234, 0xABCD, 0x1111  
num2 dw 0x0001, 0x5678, 0x2222, 0x3333
result dw 4 dup(0)  

start:
    mov ax, [num1]   
    mov bx, [num1+2]
    mov cx, [num1+4]
    mov dx, [num1+6] 

    add ax, [num2]  
    adc bx, [num2+2]
    adc cx, [num2+4]
    adc dx, [num2+6]

    mov [result], ax
    mov [result+2], bx
    mov [result+4], cx
    mov [result+6], dx

    mov ax, 0x4c00
    int 0x21
