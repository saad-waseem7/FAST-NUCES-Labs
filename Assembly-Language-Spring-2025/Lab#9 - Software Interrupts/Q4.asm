[org 0x0100]

start:
    ; Initialize SI to point to buffer start
    mov si, buffer

    ; Get current date
    mov ah, 2Ah
    int 21h         ; CX = year, DH = month, DL = day

    mov bx, cx      ; Save year to BX
    mov al, dh      ; Month
    call print2
    mov byte [si], '-'
    inc si
    mov al, dl      ; Day
    call print2
    mov byte [si], '-'
    inc si
    mov ax, bx      ; Restore year
    call print4

    mov byte [si], ' '
    inc si

    ; Get current time
    mov ah, 2Ch
    int 21h         ; CH = hour, CL = minute, DH = second

    mov al, ch      ; Hour
    call print2
    mov byte [si], ':'
    inc si

    mov al, cl      ; Minute
    call print2
    mov byte [si], ':'
    inc si

    mov al, dh      ; Second
    call print2

    mov byte [si], '$' ; End of string for printing
    inc si

    ; Print buffer
    mov dx, buffer
    mov ah, 9
    int 21h

    ; Exit program
    mov ax, 4c00h
    int 21h

; ---------------------------------
; Subroutine: print2
; Converts 2-digit number in AL to ASCII and stores at [SI]
; ---------------------------------
print2:
    aam             ; AH = tens, AL = units
    add ax, 3030h   ; Convert to ASCII
    mov [si], ah
    inc si
    mov [si], al
    inc si
    ret

; ---------------------------------
; Subroutine: print4
; Converts 4-digit number in AX to ASCII and stores at [SI]
; ---------------------------------
print4:
    ; AX has year (e.g., 2025)
    push ax
    push cx
    push dx
    mov cx, 10
    mov di, si
    add di, 3       ; Write from right to left
    mov bp, 4

.print_loop:
    xor dx, dx
    div cx
    add dl, '0'
    mov [di], dl
    dec di
    dec bp
    jnz .print_loop

    add si, 4       ; Move SI forward by 4
    pop dx
    pop cx
    pop ax
    ret

; Reserve buffer space
buffer times 30 db 0
