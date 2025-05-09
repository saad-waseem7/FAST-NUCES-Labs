; Multitasking And Dynamic Thread Registration
[org 0x0100]
jmp start

; PCB Layout:
; AX,BX,CX,DX,SI,DI,BP,SP,IP,CS,DS,SS,ES,FLAGS,NEXT,DUMMY
; 0, 2, 4, 6, 8,10,12,14,16,18,20,22,24, 26 , 28 , 30
pcb:        times 8*16 dw 0           ; Space for 8 PCBs
stack:      times 8*256 dw 0          ; Space for 8 stacks (512 bytes each)
nextpcb:    dw 1                      ; Index of next free PCB
current:    dw 0                      ; Index of current PCB
lineno:     dw 0                      ; Line number for next thread

; ---------------------------------------------------------------------------
; Subroutine to print a number on screen
; Takes the row no, column no, and number to be printed as parameters
; ---------------------------------------------------------------------------
printnum:
    push bp
    mov  bp, sp
    push es
    push ax
    push bx
    push cx
    push dx
    push di

    mov  di, 80                     ; Columns per row
    mov  ax, [bp+8]                 ; Load row number
    mul  di                         ; Calculate offset = row * 80
    mov  di, ax
    add  di, [bp+6]                 ; Add column offset
    shl  di, 1                      ; Convert to byte offset
    add  di, 8                      ; Skip top area of screen

    mov  ax, 0xb800
    mov  es, ax                     ; Point ES to video memory
    mov  ax, [bp+4]                 ; Number to be printed
    mov  bx, 16                     ; Base 16 for hex display
    mov  cx, 4                      ; Print 4 digits

nextdigit:
    mov  dx, 0
    div  bx                         ; AX / BX → quotient in AX, remainder in DX
    add  dl, 0x30                   ; Convert to ASCII
    cmp  dl, 0x39
    jbe  skipalpha
    add  dl, 7                      ; Convert to letter A-F if needed

skipalpha:
    mov  dh, 0x07                   ; Normal attribute
    mov  [es:di], dx
    sub  di, 2
    loop nextdigit

    pop  di
    pop  dx
    pop  cx
    pop  bx
    pop  ax
    pop  es
    pop  bp
    ret  6

; Thread subroutine (mytask)
; Takes the row number as input, calculates column, and prints numbers infinitely
mytask:
    push bp
    mov  bp, sp
    sub  sp, 2                     ; Reserve space for local counter
    push ax
    push bx
    push cx
    push dx

    mov  ax, [bp+4]                ; Row number
    mov  bx, 70
    mov  cx, ax
    mov  dx, 10
    mul  dx                        ; Row * 10
    sub  bx, ax                    ; Column = 70 - (row * 10)

    mov  word [bp-2], 0            ; Counter

printagain:
    push cx                        ; Row
    push bx                        ; Column
    push word [bp-2]               ; Value
    call printnum 
    inc  word [bp-2]
    jmp  printagain

    pop  dx
    pop  cx
    pop  bx
    pop  ax
    mov  sp, bp
    pop  bp
    ret

; ---------------------------------------------------------------------------
; Subroutine to initialize a new PCB/thread
; Takes segment, offset, and parameter for the new thread
; ---------------------------------------------------------------------------
initpcb:
    push bp
    mov  bp, sp
    push ax
    push bx
    push cx
    push si

    mov  bx, [nextpcb]
    cmp  bx, 8                    ; Maximum 8 PCBs
    je   exit

    mov  cl, 5
    shl  bx, cl                   ; BX *= 32

    mov  ax, [bp+8]
    mov  [pcb+bx+18], ax          ; CS
    mov  ax, [bp+6]
    mov  [pcb+bx+16], ax          ; IP

    mov  [pcb+bx+22], ds          ; DS for stack
    mov  si, [nextpcb]
    mov  cl, 9
    shl  si, cl                   ; SI *= 512
    add  si, 256*2+stack          ; Point to end of stack

    mov  ax, [bp+4]
    sub  si, 2
    mov  [si], ax                 ; Push parameter
    sub  si, 2                    ; Reserve space for return address
    mov  [pcb+bx+14], si          ; SP

    mov  word [pcb+bx+26], 0x0200 ; FLAGS
    mov  ax, [pcb+28]
    mov  [pcb+bx+28], ax         ; NEXT
    mov  ax, [nextpcb]
    mov  [pcb+28], ax
    inc  word [nextpcb]          ; Move to next PCB

exit:
    pop  si
    pop  cx
    pop  bx
    pop  ax
    pop  bp
    ret  6

; ---------------------------------------------------------------------------
; Timer interrupt service routine for thread switching
; ---------------------------------------------------------------------------
timer:
    push ds
    push bx
    push cs
    pop  ds

    mov  bx, [current]
    shl  bx, 5
    mov  [pcb+bx+0],  ax
    mov  [pcb+bx+4],  cx
    mov  [pcb+bx+6],  dx
    mov  [pcb+bx+8],  si
    mov  [pcb+bx+10], di
    mov  [pcb+bx+12], bp
    mov  [pcb+bx+24], es

    pop  ax
    mov  [pcb+bx+2],  ax
    pop  ax
    mov  [pcb+bx+20], ax
    pop  ax
    mov  [pcb+bx+16], ax
    pop  ax
    mov  [pcb+bx+18], ax
    pop  ax
    mov  [pcb+bx+26], ax
    mov  [pcb+bx+22], ss
    mov  [pcb+bx+14], sp

    mov  bx, [pcb+bx+28]
    mov  [current], bx
    shl  bx, 5

    mov  cx, [pcb+bx+4]
    mov  dx, [pcb+bx+6]
    mov  si, [pcb+bx+8]
    mov  di, [pcb+bx+10]
    mov  bp, [pcb+bx+12]
    mov  es, [pcb+bx+24]
    mov  ss, [pcb+bx+22]
    mov  sp, [pcb+bx+14]

    push word [pcb+bx+26]
    push word [pcb+bx+18]
    push word [pcb+bx+16]
    push word [pcb+bx+20]

    mov  al, 0x20
    out  0x20, al                 ; End of interrupt

    mov  ax, [pcb+bx+0]
    mov  bx, [pcb+bx+2]
    pop  ds
    iret

; ---------------------------------------------------------------------------
; Program entry point and keystroke handler
; ---------------------------------------------------------------------------
start:
    xor  ax, ax
    mov  es, ax
    cli
    mov  word [es:8*4], timer
    mov  [es:8*4+2], cs
    sti

nextkey:
    xor  ah, ah
    int  0x16                    ; Wait for key
    push cs
    mov  ax, mytask
    push ax
    push word [lineno]
    call initpcb
    inc  word [lineno]
    jmp  nextkey
