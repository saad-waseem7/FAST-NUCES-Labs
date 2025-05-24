[Org 0x0100]

mov ax,25h
mov bx, 30h

mov cx,ax
mov ax,bx
mov bx,cx
mov bx,[0x270]
mov ax,[num]
mov ax,[num+2]
mov ax,[num+4]

mov ax, 0x4c00
int 0x21

num: dw 12,25,10
