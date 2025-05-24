[org 0x0100]                           ; set origin
    jmp start                          ; jump to program start

; Data declarations
CurrentRow:  dw 0                      ; current row position
CurrentCol:  dw 0                      ; current column position
Direction:   db 'R'                    ; current direction (R/L/U/D)
tickcount:   dw 0                      ; counter for timer ticks
buffer:      dw 0                      ; screen buffer

;--------------------------------------------------------------------
; subroutine to clear the screen
;--------------------------------------------------------------------
clrscr: 
    push es                            ; save registers
    push ax
    push di

    mov ax, 0xb800                     ; video memory segment
    mov es, ax                         ; point es to video base
    mov di, 0                          ; point di to top left column

nextloc: 
    mov word [es:di], 0x0720          ; clear next char on screen
    add di, 2                          ; move to next screen location
    cmp di, 4000                       ; has the whole screen cleared
    jne nextloc                        ; if no clear next position

    pop di                             ; restore registers
    pop ax
    pop es
    ret

;--------------------------------------------------------------------
; delay subroutine
;--------------------------------------------------------------------
delay:      
    push cx                            ; save cx
    mov cx, 0xFFFF                     ; set maximum count
loop1: 
    loop loop1                         ; first delay loop
    mov cx, 0xFFFF                     ; reset count
loop2: 
    loop loop2                         ; second delay loop
    pop cx                             ; restore cx
    ret

;--------------------------------------------------------------------
; print string subroutine
;--------------------------------------------------------------------
printstr:
    mov ax, 0xb800                     ; video memory segment
    mov es, ax                         ; point es to video base
    mov al, 80                         ; load al with columns per row
    mul byte [CurrentRow]              ; calculate row offset (80 x r)
    add ax, [CurrentCol]               ; word number (80xr) + c
    shl ax, 1                          ; byte no (((80xr) + c)x2)
    mov di, ax                         ; point di to required location
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
    mov word[es:di], 0x072A            ; show this char on screen

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
    cmp byte[Direction],'D'
    jne skip2

    cmp byte[CurrentRow],24
    jne cont2
    mov byte[Direction],'L'
    sub byte[CurrentCol],1
    jmp exit

cont2:
    add byte[CurrentRow],1
    jmp exit

skip2:
    cmp byte[Direction],'L'
    jne skip3

    cmp byte[CurrentCol],0
    jne cont3
    cmp byte[CurrentCol],0
    mov byte[Direction],'U'
    jmp exit

cont3:
    sub byte[CurrentCol],1
    jmp exit

skip3:
    cmp byte[Direction],'U'
    jne exit
    cmp byte[CurrentRow],0
    jne cont4
    cmp byte[CurrentRow],0
    mov byte[Direction],'R'
    jmp exit

cont4:
    sub byte[CurrentRow],1

exit:
    ret

;------------------------------------------------------
; timer interrupt service routine - runs every clock tick
;------------------------------------------------------
timer:  
    push ax
    
    ; check if 18 ticks have passed (approximately 1 second)
    cmp word[cs:tickcount], 18
    ja move
    
    ; increment counter if less than 18 ticks
    inc word [cs:tickcount]
    jmp end

move:
    ; reset counter and update display
    mov word[cs:tickcount], 0
    call printstr

end:
    ; send EOI to PIC
    mov al, 0x20
    out 0x20, al
    
    pop ax
    iret

;--------------------------------------------------------------------
; program initialization
;--------------------------------------------------------------------
start:
    ; setup interrupt vector table
    xor ax, ax
    mov es, ax                  ; point es to IVT base
    
    ; install timer ISR
    cli                        ; disable interrupts
    mov word [es:8*4], timer   ; store offset at n*4
    mov [es:8*4+2], cs         ; store segment at n*4+2
    sti                        ; enable interrupts
    
    ; infinite loop
    jmp $                      ; infinite loop
    
    ; (unreachable code)
    mov ax, 0x4c00            ; terminate program
    int 0x21