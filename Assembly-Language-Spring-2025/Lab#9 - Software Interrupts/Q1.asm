[org 0x0100]

start:
    ; Setup SI to source string
    mov si, string1
    mov di, string2

remove_punct:
    lodsb
    cmp al, '0'
    je reverse_prep     ; End of string
    cmp al, 'A'
    jb remove_punct     ; Skip if less than 'A'
    cmp al, 'Z'
    jbe store_char
    cmp al, 'a'
    jb remove_punct
    cmp al, 'z'
    jbe store_char
    jmp remove_punct     ; Skip punctuation

store_char:
    stosb
    jmp remove_punct

reverse_prep:
    ; Null-terminate String2
    mov al, '0'
    stosb

    ; Reverse String2 to String3
    mov si, string2
    call strlen
    mov cx, ax          ; CX = length
    mov si, string2
    mov di, string3
    add si, cx
    dec si              ; SI = last char

reverse_loop:
    lodsb
    mov [di], al
    inc di
    dec cx
    jnz reverse_loop
    mov byte [di], '0'

    ; Compare String2 and String3
    mov si, string2
    mov di, string3

compare_loop:
    mov al, [si]
    mov bl, [di]
    cmp al, '0'
    je is_palindrome
    cmp al, bl
    jne not_palindrome
    inc si
    inc di
    jmp compare_loop

is_palindrome:
    mov dx, msg_palindrome
    jmp print_msg

not_palindrome:
    mov dx, msg_not_palindrome

print_msg:
    mov ah, 09h
    int 21h

    mov ax, 4c00h
    int 21h

;-------------------------------------
; Subroutine: strlen (gets string length)
; Input: SI points to string ending in '0'
; Output: AX = length
;-------------------------------------
strlen:
    xor ax, ax
.len_loop:
    mov bx, ax                 ; Fix invalid address
    cmp byte [si + bx], '0'
    je .done
    inc ax
    jmp .len_loop
.done:
    ret

;-------------------------------------
; Data Section
;-------------------------------------
string1 db "A man, a plan, a canal, Panama!!!", '0'
string2 times 100 db 0            
string3 times 100 db 0

msg_palindrome db 13,10, "The given string is palindrome", 13,10, '$'
msg_not_palindrome db 13,10, "The given string is not a palindrome", 13,10, '$'
