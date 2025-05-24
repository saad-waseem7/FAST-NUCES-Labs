[org 0x0100]

mov ax, 0xB800  
mov es, ax     
mov di, 0      

mov cx, 2080   ; 13 rows * 160 bytes per row
fill_underscore:
    mov word [es:di], 0x075F  ; `_` character
    add di, 2  
    loop fill_underscore

mov cx, 1920   ; 12 rows * 160 bytes per row
fill_dot:
    mov word [es:di], 0x072E  ; `.` character
    add di, 2  
    loop fill_dot

mov ax, 0x4c00
int 0x21
