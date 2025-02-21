[org 0x0100]

jmp start

set1 db 1, 4, 6, 0
set2 db 1, 3, 5, 8, 0
union db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

start:
    mov si, set1
    mov di, set2
    mov bx, union

l1:
    mov al, [si]
    mov dl, [di]

    cmp al, 0
    je copy_set2
    cmp dl, 0
    je copy_set1

    cmp al, dl
    je store_one
    jb store_set1
    ja store_set2

store_one:
    mov [bx], al
    inc si
    inc di
    jmp next_union

store_set1:
    mov [bx], al
    inc si
    jmp next_union

store_set2:
    mov [bx], dl
    inc di

next_union:
    inc bx
    cmp bx, union + 9
    jge end
    jmp l1

copy_set1:
    mov al, [si]
    cmp al, 0
    je end
    mov [bx], al
    inc si
    inc bx
    jmp copy_set1

copy_set2:
    mov dl, [di]
    cmp dl, 0
    je end
    mov [bx], dl
    inc di
    inc bx
    jmp copy_set2

end:
    mov word[bx], 0
    mov ax, 0x4c00
    int 0x21