[org 0x0100]

mov ax, 0xb800
mov es, ax
call clrscr
call draw_triangle

mov ax, 0x4c00
int 0x21

draw_triangle:
    mov si, 1
    mov di, 40
draw_row:
    push cx
    push si
    mov ax, di
    sub ax, si
    shl ax, 1
    mov bp, ax
    mov ax, 80
    mov bx, si
    dec bx
    mul bx
    shl ax, 1
    add bp, ax
    cmp si, 1
    jne check_last_row
    mov word [es:bp], 0x072A
    jmp next_row

check_last_row:
    cmp si, 10
    jne print_underscores
    mov word [es:bp], 0x072A
    add bp, 2

    mov cx, 17
print_last_row:
    mov word [es:bp], 0x075F
    add bp, 2
    loop print_last_row
    mov word [es:bp], 0x072A
    jmp next_row

print_underscores:
    mov cx, si
    shl cx, 1
    sub cx, 1
print_inner_normal:
    mov word [es:bp], 0x075F
    add bp, 2
    loop print_inner_normal

next_row:
    inc si
    cmp si, 11
    jne draw_row
    ret

clrscr:
    mov ax, 0xb800
    mov es, ax
    mov di, 0
nextchar:
    mov word [es:di], 0x0720
    add di, 2
    cmp di, 4000
    jne nextchar
    ret
