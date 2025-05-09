; Multitasking and dynamic thread registration
[org 0x0100]
jmp start

; PCB layout:
; ax,bx,cx,dx,si,di,bp,sp,ip,cs,ds,ss,es,flags,next,dummy
; 0, 2, 4, 6, 8,10,12,14,16,18,20,22,24, 26 , 28 , 30
pcb:   times 8*16 dw 0
stack: times 8*256 dw 0


nextpcb: dw 1                   ; Index of next free pcb
current: dw 0                   ; Index of current pcb
lineno:  dw 0                   ; Line number for next thread

;;;;; COPY LINES 028-071 FROM EXAMPLE 10.1 (printnum) ;;;;;

; Subroutine to print a number on screen
; Takes the row no, column no, and number to be printed as parameters
printnum: 
    push bp
    mov bp, sp
    push es
    push ax
    push bx
    push cx
    push dx
    push di
    mov di, 80              ; Load di with columns per row
    mov ax, [bp+8]          ; Load ax with row number
    mul di                  ; Multiply with columns per row
    mov di, ax              ; Save result in di
    add di, [bp+6]          ; Add column number
    shl di, 1               ; Turn into byte count
    add di, 8               ; To end of number location
    mov ax, 0xb800
    mov es, ax              ; Point es to video base
    mov ax, [bp+4]          ; Load number in ax
    mov bx, 16              ; Use base 16 for division
    mov cx, 4               ; Initialize count of digits

nextdigit: 
    mov dx, 0               ; Zero upper half of dividend
    div bx                  ; Divide by 10
    add dl, 0x30            ; Convert digit into ascii value
    cmp dl, 0x39            ; Is the digit an alphabet
    jbe skipalpha           ; No, skip addition
    add dl, 7               ; Yes, make in alphabet code

skipalpha: 
    mov dh, 0x07            ; Attach normal attribute
    mov [es:di], dx         ; Print char on screen
    sub di, 2               ; To previous screen location
    loop nextdigit          ; If no divide it again
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    pop es
    pop bp
    ret 6

; Mytask subroutine to be run as a thread
; Takes line number as parameter
mytask: 
    push bp
    mov bp, sp
    sub sp, 2               ; Thread local variable
    push ax
    push bx
    mov ax, [bp+4]          ; Load line number parameter
    mov bx, 70              ; Use column number 70
    mov word [bp-2], 0      ; Initialize local variable

printagain: 
    push ax                 ; Line number
    push bx                 ; Column number
    push word [bp-2]        ; Number to be printed
    call printnum           ; Print the number
    inc word [bp-2]         ; Increment the local variable
    jmp printagain          ; Infinitely print

    pop bx
    pop ax
    mov sp, bp
    pop bp
    ret

; Subroutine to register a new thread
; Takes the segment, offset, of the thread routine and a parameter
; For the target thread subroutine
initpcb: 
    push bp
    mov bp, sp
    push ax
    push bx
    push cx
    push si
    mov bx, [nextpcb]       ; Read next available pcb index
    cmp bx, 8

    je exit                 ; Yes, exit
    mov cl, 5
    shl bx, cl              ; Multiply by 32 for pcb start
    mov ax, [bp+8]          ; Read segment parameter
    mov [pcb+bx+18], ax     ; Save in pcb space for cs
    mov ax, [bp+6]          ; Read offset parameter
    mov [pcb+bx+16], ax     ; Save in pcb space for ip
    mov [pcb+bx+22], ds     ; Set stack to our segment
    mov si, [nextpcb]       ; Read this pcb index
    mov cl, 9
    shl si, cl              ; Multiply by 512
    add si, 256*2+stack     ; End of stack for this thread
    mov ax, [bp+4]          ; Read parameter for subroutine
    sub si, 2               ; Decrement thread stack pointer
    mov [si], ax            ; Pushing param on thread stack
    sub si, 2               ; Space for return address
    mov [pcb+bx+14], si     ; Save si in pcb space for sp
    mov word [pcb+bx+26], 0x0200 ; Initialize thread flags
    mov ax, [pcb+28]        ; Read next of 0th thread in ax
    mov [pcb+bx+28], ax     ; Set as next of new thread
    mov ax, [nextpcb]       ; Read new thread index
    mov [pcb+28], ax        ; Set as next of 0th thread
    inc word [nextpcb]      ; This pcb is now used

exit: 
    pop si
    pop cx
    pop bx
    pop ax
    pop bp
    ret 6

; Timer interrupt service routine
timer: 
    push ds
    push bx
    push cs
    pop ds                  ; Initialize ds to data segment
    mov bx, [current]       ; Read index of current in bx
    shl bx, 1
    shl bx, 1
    shl bx, 1
    shl bx, 1
    shl bx, 1              ; Multiply by 32 for pcb start
    mov [pcb+bx+0], ax      ; Save ax in current pcb
    mov [pcb+bx+4], cx      ; Save cx in current pcb
    mov [pcb+bx+6], dx      ; Save dx in current pcb
    mov [pcb+bx+8], si      ; Save si in current pcb
    mov [pcb+bx+10], di     ; Save di in current pcb
    mov [pcb+bx+12], bp     ; Save bp in current pcb
    mov [pcb+bx+24], es     ; Save es in current pcb
    pop ax                  ; Read original bx from stack
    mov [pcb+bx+2], ax      ; Save bx in current pcb
    pop ax                  ; Read original ds from stack
    mov [pcb+bx+20], ax     ; Save ds in current pcb
    pop ax                  ; Read original ip from stack
    mov [pcb+bx+16], ax     ; Save ip in current pcb
    pop ax                  ; Read original cs from stack
    mov [pcb+bx+18], ax     ; Save cs in current pcb
    pop ax                  ; Read original flags from stack
    mov [pcb+bx+26], ax     ; Save cs in current pcb
    mov [pcb+bx+22], ss     ; Save ss in current pcb
    mov [pcb+bx+14], sp     ; Save sp in current pcb
    mov bx, [pcb+bx+28]     ; Read next pcb of this pcb
    mov [current], bx       ; Update current to new pcb
    mov cl, 5
    shl bx, cl              ; Multiply by 32 for pcb start
    mov cx, [pcb+bx+4]      ; Read cx of new process
    mov dx, [pcb+bx+6]      ; Read dx of new process
    mov si, [pcb+bx+8]      ; Read si of new process
    mov di, [pcb+bx+10]     ; Read diof new process
    mov bp, [pcb+bx+12]     ; Read bp of new process
    mov es, [pcb+bx+24]     ; Read es of new process
    mov ss, [pcb+bx+22]     ; Read ss of new process
    mov sp, [pcb+bx+14]     ; Read sp of new process
    push word [pcb+bx+26]   ; Push flags of new process
    push word [pcb+bx+18]   ; Push cs of new process
call initpcb ; register the thread
inc word [lineno] ; update line number
jmp nextkey ; wait for next keypress