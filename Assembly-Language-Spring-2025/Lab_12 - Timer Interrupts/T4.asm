org 100h

start:
    jmp initialize

old_timer_int    dd 0
old_keyboard_int dd 0
seconds_count    dw 0
keystroke_count  dw 0
timer_enabled    db 1
last_key         db 0
msg_installed    db 'TSR Seconds Display installed. Press any key to continue...$'
tsr_signature    db 'SDTS'

initialize:
    call save_interrupts
    call install_handlers
    call display_message
    call wait_for_key
    call make_resident

save_interrupts:
    mov ah, 35h
    mov al, 08h
    int 21h
    mov word [old_timer_int], bx
    mov word [old_timer_int+2], es

    mov ah, 35h
    mov al, 09h
    int 21h
    mov word [old_keyboard_int], bx
    mov word [old_keyboard_int+2], es
    ret

install_handlers:
    cli
    mov ah, 25h                        ; set interrupt vector
    mov al, 08h                        ; timer interrupt
    mov dx, new_timer_int              ; address of new handler
    int 21h                            ; DOS interrupt

    mov ah, 25h                        ; set interrupt vector
    mov al, 09h                        ; keyboard interrupt
    mov dx, new_keyboard_int           ; address of new handler
    int 21h                            ; DOS interrupt
    sti                                ; enable interrupts
    ret

;--------------------------------------------------------------------
; display installation message
;--------------------------------------------------------------------
display_message:
    mov ah, 09h                        ; DOS print string function
    mov dx, msg_installed              ; message to display
    int 21h
    ret

;--------------------------------------------------------------------
; wait for any keypress
;--------------------------------------------------------------------
wait_for_key:
    mov ah, 0                          ; BIOS keyboard read
    int 16h
    ret

;--------------------------------------------------------------------
; make program resident in memory
;--------------------------------------------------------------------
make_resident:
    mov dx, tsr_end                    ; end of resident portion
    add dx, 15                         ; round up to next paragraph
    shr dx, 4                          ; convert to paragraphs
    mov ah, 31h                        ; DOS TSR function
    mov al, 00h                        ; return code
    int 21h

;--------------------------------------------------------------------
; timer interrupt handler
;--------------------------------------------------------------------
new_timer_int:
    push ax                            ; save all registers
    push bx
    push cx
    push dx
    push si
    push di
    push ds
    push es

    push cs                            ; setup data segment
    pop ds

    cmp byte [timer_enabled], 0        ; check if timer is enabled
    je skip_increment                  ; skip if disabled

    inc word [seconds_count]           ; increment seconds counter

skip_increment:
    call update_display

    pushf
    call far [old_timer_int]

    pop es
    pop ds
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    iret

new_keyboard_int:
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push ds
    push es

    push cs
    pop ds

    in al, 60h
    mov ah, al

    test al, 80h
    jnz key_released

    and al, 7Fh
    mov [last_key], al
    jmp end_keyboard

key_released:
    and ah, 7Fh
    cmp ah, [last_key]
    jne end_keyboard

    inc word [keystroke_count]

    mov ax, word [keystroke_count]
    test ax, 1
    jz enable_timer

    mov byte [timer_enabled], 0
    jmp end_keyboard

enable_timer:
    mov byte [timer_enabled], 1

end_keyboard:
    mov al, 20h
    out 20h, al

    pop es
    pop ds
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    jmp dword [old_keyboard_int]

update_display:
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push es

    mov ax, 0B800h
    mov es, ax

    mov ah, 0Fh
    int 10h
    xor ah, ah
    mov si, ax
    mov di, 160

    mov ax, word [seconds_count]
    mov bx, 10
    xor cx, cx

convert_loop:
    xor dx, dx
    div bx
    push dx
    inc cx
    or ax, ax
    jnz convert_loop

    cmp cx, 0
    jne calculate_position
    push word 0
    inc cx

calculate_position:
    mov ax, cx
    add ax, 4
    mov bx, 80
    sub bx, ax
    shl bx, 1

display_loop:
    pop ax
    add al, '0'
    mov [es:bx], al
    mov byte [es:bx+1], 07h
    add bx, 2
    loop display_loop

    mov byte [es:bx], ' '
    mov byte [es:bx+1], 07h
    add bx, 2
    mov byte [es:bx], 's'
    mov byte [es:bx+1], 07h
    add bx, 2
    mov byte [es:bx], 'e'
    mov byte [es:bx+1], 07h
    add bx, 2
    mov byte [es:bx], 'c'
    mov byte [es:bx+1], 07h

    pop es
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret

tsr_end:
