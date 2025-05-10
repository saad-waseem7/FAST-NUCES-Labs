[org 0x0100]
jmp start
; AND Gate Subroutine
AND_GATE:
    cmp al, 0  
    jz and_zero
    cmp bl, 0  
    jz and_zero
    mov al, 1  
    ret
and_zero:
    mov al, 0
    ret
; OR Gate Subroutine

OR_GATE:
    cmp al, 1  
    jz or_one
    cmp bl, 1  
    jz or_one
    mov al, 0  
    ret
or_one:
    mov al, 1
    ret

; XOR Gate Subroutine
XOR_GATE:
    cmp al, bl  
    jz xor_zero
    mov al, 1  
    ret
xor_zero:
    mov al, 0
    ret
; NOT Gate Subroutine
NOT_GATE:
    cmp al, 0  
    jz not_one
    mov al, 0  
    ret
not_one:
    mov al, 1
    ret
start: ; Main 
    mov al, 1  ; First input
    mov bl, 0  ; Second input
    call AND_GATE  
    mov dl, al  ; Store AND result in DL

    mov al, 1  
    mov bl, 0  
    call OR_GATE  
    mov dh, al  ; Store OR result in DH

    mov al, 1  
    mov bl, 0  
    call XOR_GATE  
    mov cl, al  ; Store XOR result in CL

    mov al, 1  
    call NOT_GATE  
    mov ch, al  ; Store NOT result in CH
    mov ax, 0x4c00
