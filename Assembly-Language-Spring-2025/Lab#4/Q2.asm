[org 0x0100]

jmp start  

num dw 0x1234, 0x5678, 0x9ABC, 0xDEF0  ; 64-bit number (Little Endian)

start:
    mov ax, [num]      
    mov bx, [num+2]    
    mov cx, [num+4]    
    mov dx, [num+6]    

    mov cl, 1

shift_left:
    shl ax, 1
    rcl bx, 1
    rcl cx, 1
    rcl dx, 1

    mov ax, 0x4c00
    int 0x21
