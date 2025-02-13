[org 0x0100]

mov [array1], byte 0
mov [array2], byte 1

mov al, [array1]
add al, [array2]
mov [array3], al

mov al, [array1]
add al, [array3]
mov [array1+1], al

mov al, [array3]
sub al, [array2]
mov [array2+1], al

mov al, [array1+1]
add al, [array2+1]
mov [array3+1], al

mov al, [array1+1]
add al, [array3+1]
mov [array1+2], al

mov al, [array3+1]
sub al, [array2+1]
mov [array2+2], al

mov al, [array1+2]
add al, [array2+2]
mov [array3+2], al

mov al, [array1+2]
add al, [array3+2]
mov [array1+3], al

mov al, [array3+2]
sub al, [array2+2]
mov [array2+3], al

mov al, [array1+3]
add al, [array2+3]
mov [array3+3], al

mov al, [array1+3]
add al, [array3+3]
mov [array1+4], al

mov al, [array3+3]
sub al, [array2+3]
mov [array2+4], al

mov al, [array1+4]
add al, [array2+4]
mov [array3+4], al


mov ax, 0x4c00
int 0x21

array1: times 5 db 0 
array2: times 5 db 0 
array3: times 5 db 0 
