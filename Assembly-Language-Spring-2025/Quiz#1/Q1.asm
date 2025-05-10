[org 0x0100]
JMP start

oldisr:     dd 0
pressFlag:  dw 0
releaseFlag: dw 0
altPF:      dw 0
altRF:      dw 0
entFlag:    dw 0

screen1:    resw 4000

initS1:     ; initializes screen 1 
            push ax
            push ds
            push es
            push cx
            push di

            push ds
            pop es

            mov di, screen1
            mov ax, 0x0f2a

            mov cx, 2000

            rep stosw

            pop di
            pop cx
            pop es
            pop ds
            pop ax
            ret

printS1:    ; prints screen 1
            push ds
            push es
            push si
            push di
            push ax
            push cx

            mov ax, 0xb800
            mov es, ax

            mov si, screen1
            mov di, 0

            mov cx, 2000

            rep movsw

            pop cx
            pop ax
            pop di
            pop si
            pop es
            pop ds
            ret

initS2:     ; initializes screen 2
            push ax
            push ds
            push es
            push cx
            push di

            push ds
            pop es

            mov di, screen1
            add di, 4000
            mov ax, 0x702b

            mov cx, 2000

            rep stosw

            pop di
            pop cx
            pop es
            pop ds
            pop ax
            ret

printS2:    ; prints screen 2
            push ds
            push es
            push si
            push di
            push ax
            push cx

            mov ax, 0xb800
            mov es, ax

            mov si, screen1
            add si, 4000
            mov di, 0

            mov cx, 2000

            rep movsw

            pop cx
            pop ax
            pop di
            pop si
            pop es
            pop ds
            ret

kbisr:      
            push ax
            push es

            mov ax, 0xb800
            mov es, ax

            in al, 0x60

        checkAltPressed:
            cmp al, 0x2d ; 38
            jnz checkAltReleased
            mov word [altPF], 1

        checkAltReleased:
            cmp al, 0xad ; b8
            jnz checkEnterPressed
            mov word [altPF], 0

        checkEnterPressed:
            cmp al, 0x2c ; 0f
            jnz security
            mov word [entFlag], 1

        security:
            cmp word [altPF], 1
            jnz exit
            cmp word [entFlag], 1
            jnz exit

        callCLS:
            cmp word [pressFlag], 1
            jz callRES
            call printS1
            mov word [pressFlag], 1
            jmp exit

        callRES:
            cmp word [pressFlag], 0
            jz exit
            call printS2
            mov word [pressFlag], 0

        exit:
            mov word [entFlag], 0
            mov al, 0x20
            out 0x20, al
            pop es
            pop ax
            ;jmp far [cs:oldisr]
            iret

start:

    call initS1
    call initS2

    xor ax, ax
    mov es, ax

    mov ax, [es:9*4]
    mov [oldisr], ax
    mov ax, [es:9*4+2]
    mov [oldisr+2], ax

    cli
    mov word [es:9*4], kbisr
    mov word [es:9*4+2], cs
    sti

    mov dx, start
    add dx, 15
    mov cl, 4
    shr dx, cl

testLoop:
    jmp testLoop

return0:
    mov ax, 0x3100
    ;mov ax, 0x4c00
    int 0x21