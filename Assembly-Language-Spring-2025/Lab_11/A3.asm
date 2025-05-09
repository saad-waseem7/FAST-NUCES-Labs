; Multitasking And Dynamic Thread Registration
[org 0x0100]
jmp start

; PCB Layout:
; ax,bx,cx,dx,si,di,bp,sp,ip,cs,ds,ss,es,flags,next,dummy
; 0, 2, 4, 6, 8,10,12,14,16,18,20,22,24, 26 , 28 , 30

pcb:        times 8*16 dw 0      ; Space For 32 PCBs
stack:      times 8*256 dw 0     ; Space For 32 512 Byte Stacks
nextpcb:    dw 1                 ; Index Of Next Free PCB
current:    dw 0                 ; Index Of Current PCB
colno:      dw 79                ; Line Number For Next Thread

;---------------------------------------------------------------------------
sleep:      push cx

            mov cx, 0xFFFF

delay:      loop delay

            pop cx
            ret

;---------------------------------------------------------------------------
; Subroutine To Clear The Screen
;---------------------------------------------------------------------------
clrscr:     push es
            push ax
            push di

            mov ax, 0xb800
            mov es, ax                  ; Point ES To Video Base
            mov di, 0                   ; Point DI To Top Left Column

nextloc:    mov word [es:di], 0x0720    ; Clear Next Char On Screen
            add di, 2                   ; Move To Next Screen Location
            cmp di, 4000                ; Has The Whole Screen Cleared?
            jne nextloc                 ; If No, Clear Next Position

            pop di
            pop ax
            pop es
            ret

;---------------------------------------------------------------------------
; MyTask Subroutine To Be Run As A Thread
; Takes Line Number As Parameter
;---------------------------------------------------------------------------
mytask:     push bp
            mov bp, sp

            push ax
            push bx
            push cx
            push di
            push es

            mov ax, 0xb800
            mov es, ax

            mov di, [bp+4]              ; Column Number 
            shl di, 1

            mov cx, 0
            mov al, '*'
            mov ah, 0x07

printagain: cmp cx, 24
            jne noupdate

            mov cx, 0
            mov di, [bp+4]
            shl di, 1

noupdate:   mov al, '*'
            mov word [es:di], ax
            call sleep
            mov al, ' '
            mov word [es:di], ax
            add di, 160
            add cx, 1
            jmp printagain              ; Infinitely Print

            pop es
            pop di
            pop cx
            pop bx
            pop ax
            mov sp, bp
            pop bp
            ret

;---------------------------------------------------------------------------
; Subroutine To Register A New Thread
; Takes The Segment, Offset, Of The Thread Routine And A Parameter
; For The Target Thread Subroutine
;---------------------------------------------------------------------------
initpcb:    push bp
            mov bp, sp
            push ax
            push bx
            push cx
            push si

            mov bx, [nextpcb]           ; Read Next Available PCB Index
            cmp bx, 8                   ; Are All PCBs Used?
            je exit                     ; Yes, Exit

            mov cl, 5
            shl bx, cl                  ; Multiply By 32 For PCB Start
            mov ax, [bp+8]              ; Read Segment Parameter
            mov [pcb+bx+18], ax         ; Save In PCB Space For CS
            mov ax, [bp+6]              ; Read Offset Parameter
            mov [pcb+bx+16], ax         ; Save In PCB Space For IP
            mov [pcb+bx+22], ds         ; Set Stack To Our Segment

            mov si, [nextpcb]           ; Read This PCB Index
            mov cl, 9
            shl si, cl                  ; Multiply By 512
            add si, 256*2+stack         ; End Of Stack For This Thread

            mov ax, [bp+4]              ; Read Parameter For Subroutine
            sub si, 2                   ; Decrement Thread Stack Pointer
            mov [si], ax                ; Pushing Param On Thread Stack
            sub si, 2                   ; Space For Return Address
            mov [pcb+bx+14], si         ; Save SI In PCB Space For SP
            mov word [pcb+bx+26], 0x0200; Initialize Thread Flags

            mov ax, [pcb+28]            ; Read Next Of 0th Thread In AX
            mov [pcb+bx+28], ax         ; Set As Next Of New Thread
            mov ax, [nextpcb]           ; Read New Thread Index
            mov [pcb+28], ax            ; Set As Next Of 0th Thread
            inc word [nextpcb]          ; This PCB Is Now Used

exit:       pop si
            pop cx
            pop bx
            pop ax
            pop bp
            ret 6

;---------------------------------------------------------------------------
; Timer Interrupt Service Routine
;---------------------------------------------------------------------------
timer:      push ds
            push bx
            push cs
            pop ds                      ; Initialize DS To Data Segment

            mov bx, [current]           ; Read Index Of Current In BX
            shl bx, 1
            shl bx, 1
            shl bx, 1
            shl bx, 1
            shl bx, 1                   ; Multiply By 32 For PCB Start

            mov [pcb+bx+0], ax          ; Save AX In Current PCB
            mov [pcb+bx+4], cx          ; Save CX In Current PCB
            mov [pcb+bx+6], dx          ; Save DX In Current PCB
            mov [pcb+bx+8], si          ; Save SI In Current PCB
            mov [pcb+bx+10], di         ; Save DI In Current PCB
            mov [pcb+bx+12], bp         ; Save BP In Current PCB
            mov [pcb+bx+24], es         ; Save ES In Current PCB

            pop ax                      ; Read Original BX From Stack
            mov [pcb+bx+2], ax          ; Save BX In Current PCB
            pop ax                      ; Read Original DS From Stack
            mov [pcb+bx+20], ax         ; Save DS In Current PCB
            pop ax                      ; Read Original IP From Stack
            mov [pcb+bx+16], ax         ; Save IP In Current PCB
            pop ax                      ; Read Original CS From Stack
            mov [pcb+bx+18], ax         ; Save CS In Current PCB
            pop ax                      ; Read Original Flags From Stack
            mov [pcb+bx+26], ax         ; Save CS In Current PCB
            mov [pcb+bx+22], ss         ; Save SS In Current PCB
            mov [pcb+bx+14], sp         ; Save SP In Current PCB

            mov bx, [pcb+bx+28]         ; Read Next PCB Of This PCB
            mov [current], bx           ; Update Current To New PCB

            mov cl, 5
            shl bx, cl                  ; Multiply By 32 For PCB Start

            mov cx, [pcb+bx+4]          ; Read CX Of New Process
            mov dx, [pcb+bx+6]          ; Read DX Of New Process
            mov si, [pcb+bx+8]          ; Read SI Of New Process
            mov di, [pcb+bx+10]         ; Read DI Of New Process
            mov bp, [pcb+bx+12]         ; Read BP Of New Process
            mov es, [pcb+bx+24]         ; Read ES Of New Process
            mov ss, [pcb+bx+22]         ; Read SS Of New Process
            mov sp, [pcb+bx+14]         ; Read SP Of New Process

            push word [pcb+bx+26]       ; Push Flags Of New Process
            push word [pcb+bx+18]       ; Push CS Of New Process
            push word [pcb+bx+16]       ; Push IP Of New Process
            push word [pcb+bx+20]       ; Push DS Of New Process

            mov al, 0x20
            out 0x20, al                ; Send EOI To PIC

            mov ax, [pcb+bx+0]          ; Read AX Of New Process
            mov bx, [pcb+bx+2]          ; Read BX Of New Process
            pop ds                      ; Read DS Of New Process
            iret                        ; Return To New Process

;---------------------------------------------------------------------------
start:      call clrscr

            xor ax, ax
            mov es, ax                  ; Point ES To IVT Base

            cli
            mov word [es:8*4], timer
            mov [es:8*4+2], cs          ; Hook Timer Interrupt
            sti

nextkey:    xor ah, ah                  ; Service 0 – Get Keystroke
            int 0x16                    ; BIOS Keyboard Services

            push cs                     ; Use Current Code Segment
            mov ax, mytask
            push ax                     ; Use MyTask As Offset
            push word [colno]           ; Thread Parameter
            call initpcb                ; Register The Thread
            sub word [colno], 5         ; Update Column Number
            jmp nextkey                 ; Wait For Next Keypress