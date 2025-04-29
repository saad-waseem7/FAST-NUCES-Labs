[org 0x0100]
; Jump to TSR installation routine
jmp tsr_install

; Data section
old_kb_isr       dd 0                    ; Storage for original keyboard ISR
num_buf          times 6 db 0            ; Buffer for storing input digits
digit_count      db 0                    ; Current number of digits entered
input_active     db 0                    ; Flag to track input state

; Display messages
input_msg        db 'Input a number: $'
newline          db 0Dh, 0Ah, '$'        ; Carriage return + line feed
display_msg      db 'You entered: $'
is_pal_msg       db 'Yes, it is a palindrome.$'
not_pal_msg      db 'No, it is not a palindrome.$'

; Number storage for palindrome check
num_input        dw 0                    ; Original input number
num_reversed     dw 0                    ; Reversed number for comparison
 
; Lookup table for converting scancodes to ASCII
scancode_to_ascii:
    db 0,0,'1','2','3','4','5','6','7','8','9','0'

; Function to clear the screen using BIOS
clear_screen:
    mov ax, 0003h                        ; Video mode 3 (80x25 text)
    int 10h
    ret

; Function to display a string using DOS
; Input: DX = string address ending with '$'
display_string:
    mov ah, 09h
    int 21h
    ret

; Function to convert string buffer to number
convert_buffer_to_number:
    mov si, num_buf
    xor ax, ax
    mov [num_input], ax

.process_next_digit:
    mov al, [si]                        ; Load digit from buffer
    cmp al, 0                           ; Check for end of string
    je .conversion_complete
    mov ax, [num_input]
    mov bx, 10                          ; Multiply by 10
    mul bx
    mov [num_input], ax
    mov al, [si]
    sub al, '0'                         ; Convert ASCII to number
    mov ah, 0
    add [num_input], ax
    inc si
    jmp .process_next_digit
    
.conversion_complete:
    ret

; Keyboard interrupt handler (INT 09h)
keyboard_interrupt_handler:
    pusha
    push ds
    push es
    mov ax, cs
    mov ds, ax

    in al, 60h                          ; Read scancode from keyboard
    test al, 80h                        ; Check if key release
    jnz .exit_handler

    cmp al, 1Ch                         ; Check for Enter key
    jne .check_numeric_input

    cmp byte [input_active], 0
    je .start_number_input
    cmp byte [digit_count], 0
    je .exit_handler
    mov byte [input_active], 0
    call check_palindrome_number
    jmp .exit_handler

.start_number_input:
    mov byte [input_active], 1
    call clear_screen
    mov dx, input_msg
    call display_string
    mov byte [digit_count], 0
    mov di, num_buf
    mov cx, 6
    xor al, al
    rep stosb                           ; Clear input buffer
    jmp .exit_handler

.check_numeric_input:
    cmp byte [input_active], 0
    je .exit_handler
    cmp al, 02h                         ; Check if key is in numeric range
    jb .exit_handler
    cmp al, 0Bh
    ja .exit_handler
    cmp byte [digit_count], 5           ; Maximum 5 digits
    jae .exit_handler
    mov bx, scancode_to_ascii          ; Convert scancode to ASCII
    xlat
    mov di, num_buf
    movzx cx, byte [digit_count]
    add di, cx
    mov [di], al                       ; Store digit in buffer
    inc byte [digit_count]
    mov dl, al                         ; Echo character
    mov ah, 02h
    int 21h

.exit_handler:
    mov al, 20h                        ; Send EOI to PIC
    out 20h, al
    pop es
    pop ds
    popa
    iret

; Function to check if number is palindrome
check_palindrome_number:
    mov di, num_buf
    movzx cx, byte [digit_count]
    add di, cx
    mov byte [di], 0                   ; Null terminate buffer
    mov dx, newline
    call display_string
    mov dx, display_msg
    call display_string
    mov ah, 02h
    mov si, num_buf

.display_number:
    lodsb
    cmp al, 0
    je .display_complete
    mov dl, al
    int 21h
    jmp .display_number

.display_complete:
    mov dx, newline
    call display_string
    call convert_buffer_to_number
    mov word [num_reversed], 0
    mov ax, [num_input]

.reverse_number:
    cmp ax, 0
    je .reverse_complete
    xor dx, dx
    mov bx, 10                         ; Divide by 10 to get digits
    div bx
    push ax
    mov ax, [num_reversed]
    mov bx, 10                         ; Build reversed number
    mul bx
    add ax, dx
    mov [num_reversed], ax
    pop ax
    jmp .reverse_number

.reverse_complete:
    mov dx, newline
    call display_string
    mov ax, [num_input]
    mov bx, [num_reversed]
    cmp ax, bx                         ; Compare original and reversed
    jne .print_not_palindrome
    mov dx, is_pal_msg
    jmp .print_result

.print_not_palindrome:
    mov dx, not_pal_msg

.print_result:
    call display_string
    mov dx, newline
    call display_string
    mov byte [digit_count], 0          ; Reset input state
    mov byte [input_active], 0
    mov di, num_buf
    mov cx, 6
    xor al, al
    rep stosb                          ; Clear input buffer
    ret

; TSR installation routine
tsr_install:
    mov ax, 3509h                      ; Get original INT 09h vector
    int 21h
    mov [old_kb_isr], bx               ; Save original ISR address
    mov [old_kb_isr+2], es
    mov dx, keyboard_interrupt_handler  ; Set new keyboard handler
    mov ax, 2509h
    int 21h
    mov dx, tsr_install                ; Calculate resident size
    add dx, 15
    mov cl, 4
    shr dx, cl
    mov ax, 3100h                      ; Terminate and stay resident
    int 21h
