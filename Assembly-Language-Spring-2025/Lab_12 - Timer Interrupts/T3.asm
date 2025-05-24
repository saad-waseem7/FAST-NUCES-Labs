[org 0x0100]
jmp start

CurrentRow: dw 0
CurrentCol: dw 0
Direction: db 'R'
buffer: dw 0
oldkb: dd 0 
timerflag: dw 0
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
;--------------------------------------------------------
; keyboard interrupt service routine
;--------------------------------------------------------
kbisr:		
    push ax
    in al, 0x60 ; read char from keyboard port

    cmp al, 0x2a ; has the left shift pressed
    jne nextcmp ; no, try next comparison
    
    mov word [cs:timerflag], 1; set flag to start printing
			
			
nextcmp:	
    cmp al, 0x36 ; has the left shift released
    jne nomatch ; no, chain to old ISR
    mov word [cs:timerflag], 0; reset flag to stop printing
        
			
nomatch:	
    pop ax
    jmp far [cs:oldkb] ; call original ISR


;--------------------------------------------------------------------
printstr:
    push bp
    mov bp, sp
    pusha
    mov ax, 0xb800
    mov es, ax ; point es to video base
    mov al, 80 ; load al with columns per row

    mul byte [cs:CurrentRow] ; 80 x r
    add ax, [cs:CurrentCol] ; word number (80xr) + c
    shl ax, 1 ; byte no (((80xr) + c)x2)


    mov di, ax ; point di to required location
    mov ax, word[cs:buffer]

    cmp byte[cs:CurrentRow], 0
    jne go
    mov word[es:di-2], ax
    jmp go3
go:
    cmp byte[cs:CurrentRow], 24
    jne go1
    mov word[es:di+2], ax
    jmp go3
go1:
    cmp byte[cs:CurrentCol], 0
    jne go2
    mov word[es:di+160], ax
    jmp go3
go2:
    cmp byte[cs:CurrentCol], 79
    jne go3
    mov word[es:di-160], ax
go3:

    mov ax, word[es:di]
    mov [cs:buffer], ax
    mov word[es:di], 0x072A ; show this char on screen

        
    cmp byte[cs:Direction],'R'
    jne skip


    cmp byte[cs:CurrentCol],79
    jne cont
    mov byte[cs:Direction],'D'
    add byte[cs:CurrentRow],1
    jmp exit

cont:
    add byte[cs:CurrentCol],1
    jmp exit

skip:
    cmp byte[cs:Direction],'D'
    jne skip2

    cmp byte[cs:CurrentRow],24
    jne cont2
    mov byte[cs:Direction],'L'
    sub byte[cs:CurrentCol],1
    jmp exit

cont2:
    add byte[cs:CurrentRow],1
    jmp exit


skip2:

    cmp byte[cs:Direction],'L'
    jne skip3

    cmp byte[cs:CurrentCol],0
    jne cont3
    cmp byte[cs:CurrentCol],0
    mov byte[cs:Direction],'U'
    jmp exit

cont3:
    sub byte[cs:CurrentCol],1
    jmp exit


skip3:

    cmp byte[cs:Direction],'U'
    jne exit
    cmp byte[cs:CurrentRow],0
    jne cont4
    cmp byte[cs:CurrentRow],0
    mov byte[cs:Direction],'R'
    jmp exit

cont4:
    sub byte[cs:CurrentRow],1

exit:

    pop bp
    popa
    ret

;------------------------------------------------------
; timer interrupt service routine
;------------------------------------------------------
timer:
    push ax                              ; save ax register on stack
    
    cmp word [cs:timerflag], 1          ; check if printing is enabled
    jne next                            ; if not enabled, skip to next
    call printstr                       ; call routine to print character
    
next:
    mov al, 0x20                        ; load End Of Interrupt command
    out 0x20, al                        ; send EOI to PIC
    pop ax                              ; restore ax register
    iret                                ; return from interrupt

;--------------------------------------------------------------------
; program initialization and TSR setup
;--------------------------------------------------------------------
start:
    xor ax, ax                          ; clear ax register
    mov es, ax                          ; set es to beginning of IVT
    
    mov ax, [es:9*4]                    ; get keyboard ISR offset
    mov [oldkb], ax                     ; store old keyboard offset
    mov ax, [es:9*4+2]                  ; get keyboard ISR segment
    mov [oldkb+2], ax                   ; store old keyboard segment
    
    cli                                 ; disable all interrupts
    mov word [es:9*4], kbisr            ; set new keyboard ISR offset
    mov [es:9*4+2], cs                  ; set new keyboard ISR segment
    mov word [es:8*4], timer            ; set new timer ISR offset
    mov [es:8*4+2], cs                  ; set new timer ISR segment
    sti                                 ; enable all interrupts
    
    mov dx, start                       ; get end of resident code
    add dx, 15                          ; round up to next paragraph
    mov cl, 4                           ; prepare to divide by 16
    shr dx, cl                          ; convert bytes to paragraphs
    
    mov ax, 0x3100                      ; DOS TSR function
    int 0x21                            ; make program resident