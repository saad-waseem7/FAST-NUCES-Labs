[org 0x0100]

jmp start  

; Video memory address for text mode
mov ax, 0xB800  
mov es, ax   

; Global Variables
currentRow db 1
currentCol db 0
direction db 'R'  ; Start moving right

start:
loop_start:
    call MovingStar
    call Delay
    jmp loop_start  ; Infinite loop (Never exits)

    mov ax, 0x4c00
    int 0x21

; ---------------- Subroutine: Moving Star ----------------
MovingStar:
    ; Calculate video memory address for (row, col)
    mov al, [currentRow]
    mov ah, 160  ; 80 columns * 2 bytes per char
    mul ah       
    add ax, [currentCol]
    shl ax, 1  
    mov di, ax  

    ; Print star at the current position
    mov byte [es:di], '*'  ; Store '*'
    mov byte [es:di+1], 0x07  ; Attribute: Normal white

    ; Move according to direction
    cmp byte [direction], 'R'
    je move_right
    cmp byte [direction], 'D'
    je move_down
    cmp byte [direction], 'L'
    je move_left
    cmp byte [direction], 'U'
    je move_up
    ret

move_right:
    inc byte [currentCol]
    cmp byte [currentCol], 79
    jne ret_from_star
    mov byte [direction], 'D'
ret_from_star:
    ret

move_down:
    inc byte [currentRow]
    cmp byte [currentRow], 24
    jne ret_from_star
    mov byte [direction], 'L'
    ret

move_left:
    dec byte [currentCol]
    cmp byte [currentCol], 0
    jne ret_from_star
    mov byte [direction], 'U'
    ret

move_up:
    dec byte [currentRow]
    cmp byte [currentRow], 1
    jne ret_from_star
    mov byte [direction], 'R'
    ret

; ---------------- Delay Function ----------------
Delay:
    mov cx, 0xFFFF
delay_loop:
    loop delay_loop
    ret
