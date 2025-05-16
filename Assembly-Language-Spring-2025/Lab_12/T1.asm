[org 0x0100]
jmp start

CurrentRow: dw 0
CurrentCol: dw 0
Direction: db 'R'
buffer: dw 0
;--------------------------------------------------------------------
; subroutine to clear the screen
;--------------------------------------------------------------------
clrscr: 
    push es
    push ax
    push di

    mov ax, 0xb800
    mov es, ax ; point es to video base
    mov di, 0 ; point di to top left column

    nextloc: mov word [es:di], 0x0720 ; clear next char on screen
    add di, 2 ; move to next screen location
    cmp di, 4000 ; has the whole screen cleared
    jne nextloc ; if no clear next position

    pop di
    pop ax
    pop es
    ret

delay:      
    push cx
    mov cx, 0xFFFF
    loop1: loop loop1
    mov cx, 0xFFFF
    loop2: loop loop2
    pop cx
    ret

;--------------------------------------------------------------------
;--------------------------------------------------------------------
printstr:
    push bp
    mov bp, sp
    pusha
    mov ax, 0xb800
    mov es, ax ; point es to video base
    mov al, 80 ; load al with columns per row

    mul byte [CurrentRow] ; 80 x r
    add ax, [CurrentCol] ; word number (80xr) + c
    shl ax, 1 ; byte no (((80xr) + c)x2)


    mov di, ax ; point di to required location
    mov ax, word[buffer]

    cmp byte[CurrentRow], 0
    jne go
    mov word[es:di-2], ax
    jmp go3
go:
    cmp byte[CurrentRow], 24
    jne go1
    mov word[es:di+2], ax
    jmp go3
go1:
    cmp byte[CurrentCol], 0
    jne go2
    mov word[es:di+160], ax
    jmp go3
go2:
    cmp byte[CurrentCol], 79
    jne go
    mov word[es:di-160], ax
go3:

    mov ax, word[es:di]
    mov [buffer], ax
    mov word[es:di], 0x072A ; show this char on screen

        
    cmp byte[Direction],'R'
    jne skip


    cmp byte[CurrentCol],79
    jne cont
    mov byte[Direction],'D'
    add byte[CurrentRow],1
    jmp exit

cont:
    add byte[CurrentCol],1
    jmp exit

skip:
    cmp byte[Direction], 'D'           ; check if moving down
    jne skip2                          ; if not, check next direction
    
    cmp byte[CurrentRow], 24           ; check if at bottom edge
    jne cont2                          ; if not, continue moving down
    mov byte[Direction], 'L'           ; change direction to left
    sub byte[CurrentCol], 1            ; move one column left
    jmp exit
    
cont2:
    add byte[CurrentRow], 1            ; move down one row
    jmp exit

skip2:
    cmp byte[Direction], 'L'           ; check if moving left
    jne skip3                          ; if not, check next direction
    
    cmp byte[CurrentCol], 0            ; check if at left edge
    jne cont3                          ; if not, continue moving left
    mov byte[Direction], 'U'           ; change direction to up
    jmp exit
    
cont3:
    sub byte[CurrentCol], 1            ; move left one column
    jmp exit

skip3:
    cmp byte[Direction], 'U'           ; check if moving up
    jne exit                          ; if not, exit
    cmp byte[CurrentRow], 0            ; check if at top edge
    jne cont4                          ; if not, continue moving up
    mov byte[Direction], 'R'           ; change direction to right
    jmp exit
    
cont4:
    sub byte[CurrentRow], 1            ; move up one row

exit:
    pop bp                             ; restore base pointer
    popa                              ; restore all registers
    ret

;------------------------------------------------------
; timer interrupt service routine
;------------------------------------------------------
timer:  
    push ax                            ; save ax register

    ;call clrscr                       ; call the clrscr subroutine
    call printstr                      ; print tick count

    mov al, 0x20                       ; PIC EOI command
    out 0x20, al                       ; signal end of interrupt

    pop ax                             ; restore ax register
    iret                              ; return from interrupt

;--------------------------------------------------------------------
; program initialization
;--------------------------------------------------------------------
start:
    xor ax, ax                         ; clear ax
    mov es, ax                         ; point es to IVT base

    cli                               ; disable interrupts
    mov word [es:8*4], timer          ; store timer ISR offset
    mov [es:8*4+2], cs                ; store timer ISR segment
    sti                               ; enable interrupts

    jmp $                             ; infinite loop

    ; unreachable code
    mov ax, 0x4c00                    ; terminate program
    int 0x21                          ; DOS interrupt