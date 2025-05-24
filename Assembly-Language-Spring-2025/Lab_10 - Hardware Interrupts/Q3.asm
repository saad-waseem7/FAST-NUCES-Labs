[org 0x0100]
; Jump to TSR installation routine
jmp tsr_install

; Data section
old_keyboard_isr     dd 0                    ; Storage for original keyboard ISR
screen_buffer        times 4000 db 0         ; Buffer to store screen contents (80x25x2 bytes)
b_key_pressed        db 0                    ; Flag to track if 'B' key is pressed
message_displayed    db 0                    ; Flag to track if installation message shown

; Keyboard scan codes
SCAN_B_PRESS        equ 48                  ; Scan code for 'B' key press
SCAN_B_RELEASE      equ 176                 ; Scan code for 'B' key release

; TSR installation routine
tsr_install:
    mov dx, install_message                 ; Display installation message
    mov ah, 09h
    int 21h
    mov ah, 01h                            ; Wait for keypress
    int 21h
    mov byte [message_displayed], 1
    mov ax, 3509h                          ; Get original INT 09h vector
    int 21h
    mov word [old_keyboard_isr], bx        ; Save original ISR address
    mov word [old_keyboard_isr+2], es
    mov dx, keyboard_interrupt_handler     ; Install new keyboard handler
    mov ax, 2509h
    int 21h
    mov dx, end_of_resident                ; Calculate resident size
    sub dx, 0x0100
    add dx, 15
    shr dx, 4
    mov ax, 3100h                          ; Terminate and stay resident
    int 21h

; Main keyboard interrupt handler
keyboard_interrupt_handler:
    pushf                                  ; Save all registers and flags
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push ds
    push es
    push cs
    pop ds                                ; Set DS to code segment
    in al, 60h                           ; Read scancode from keyboard port
    cmp al, SCAN_B_PRESS                 ; Check for 'B' key press
    je b_key_pressed_handler
    cmp al, SCAN_B_RELEASE               ; Check for 'B' key release
    je b_key_released_handler
    jmp chain_to_original_isr            ; Pass other keys to original handler

; Handle 'B' key press event
b_key_pressed_handler:
    cmp byte [b_key_pressed], 1          ; Check if already pressed
    je skip_key_handling
    mov byte [b_key_pressed], 1          ; Set pressed flag
    call save_screen_buffer              ; Save current screen contents
    call clear_screen_buffer             ; Clear the screen
    jmp skip_key_handling

; Handle 'B' key release event
b_key_released_handler:
    cmp byte [b_key_pressed], 1          ; Check if was pressed
    jne skip_key_handling
    mov byte [b_key_pressed], 0          ; Clear pressed flag
    call restore_screen_buffer           ; Restore screen contents
    jmp skip_key_handling

; Chain to original keyboard handler
chain_to_original_isr:
    mov al, 20h                          ; Send EOI to PIC
    out 20h, al
    pop es                               ; Restore registers
    pop ds
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    popf
    jmp far [cs:old_keyboard_isr]        ; Jump to original handler

; Skip to end of interrupt handler
skip_key_handling:
    mov al, 20h                          ; Send EOI to PIC
    out 20h, al
    pop es                               ; Restore registers
    pop ds
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    popf
    iret

; Function to save current screen contents
save_screen_buffer:
    push ax
    push cx
    push si
    push di
    push es
    push ds
    mov ax, 0xB800                      ; Video memory segment
    mov es, ax
    xor di, di                          ; Start of video memory
    push cs
    pop ds
    mov si, screen_buffer               ; Point to our buffer
    mov cx, 2000                        ; 80x25 characters (word each)

save_loop:
    mov ax, [es:di]                     ; Copy character and attribute
    mov [si], ax
    add di, 2
    add si, 2
    loop save_loop
    pop ds
    pop es
    pop di
    pop si
    pop cx
    pop ax
    ret

; Function to clear the screen
clear_screen_buffer:
    push ax
    push cx
    push di
    push es
    mov ax, 0xB800                       ; Video memory segment
    mov es, ax
    xor di, di
    mov ax, 0x0020                      ; Space character with black attribute
    mov cx, 2000                        ; 80x25 characters
    rep stosw                           ; Clear entire screen
    pop es
    pop di
    pop cx
    pop ax
    ret

; Function to restore saved screen contents
restore_screen_buffer:
    push ax
    push cx
    push si
    push di
    push es
    push ds
    mov ax, 0xB800                       ; Video memory segment
    mov es, ax
    xor di, di
    push cs
    pop ds
    mov si, screen_buffer               ; Point to saved buffer
    mov cx, 2000                        ; 80x25 characters

restore_loop:
    mov ax, [si]                        ; Restore character and attribute
    mov [es:di], ax
    add di, 2
    add si, 2
    loop restore_loop
    pop ds
    pop es
    pop di
    pop si
    pop cx
    pop ax
    ret

; Data strings
install_message db 'B-Screen TSR installed. Press B to hide screen, release to restore.', 0Dh, 0Ah
                db 'Press any key to continue...', 0Dh, 0Ah, '$'

end_of_resident db 0                     
