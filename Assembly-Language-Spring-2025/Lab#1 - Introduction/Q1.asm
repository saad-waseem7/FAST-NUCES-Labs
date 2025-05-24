[org 0x0100] 

mov ax, 5 ; AX = 5
mov bx, 10 ; BX = 10
add ax, bx ; AX = AX + BX
mov bx, 15 ; BX = 15
add ax, bx ; AX = AX + BX
mov ax, 0x4c00

int 0x21
