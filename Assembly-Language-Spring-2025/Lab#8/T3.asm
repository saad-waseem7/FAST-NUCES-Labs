org 100h

start:
    mov ah, 01h
    int 21h

    cmp al, 'q'
    je exit
    cmp al, 'Q'
    je exit

    cmp al, 'a'
    jb display
    cmp al, 'z'
    ja display
    sub al, 20h

display:
    mov dl, al
    mov ah, 02h
    int 21h
    jmp start

exit:
    mov ah, 4Ch
    int 21h