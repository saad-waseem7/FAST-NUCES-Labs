[org 0x0100]

jmp start

set1 db 1, 4, 6, 0
set2 db 1, 3, 6, 8, 0
intersect db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

start:
    mov si, set1
    mov di, set2
    mov bx, intersect

l1:
    mov al, [si]
    mov dl, [di]

    cmp al, 0
    je end
    cmp dl, 0
    je end

    cmp al, dl
    je store
    jb next_set1
    ja next_set2

store:
    mov [bx], al
    inc bx
    inc si
    inc di
    jmp l1

next_set1:
    inc si
    jmp l1

next_set2:
    inc di
    jmp l1

end:
    mov word[bx], 0
    mov ax, 0x4c00
    int 0x21