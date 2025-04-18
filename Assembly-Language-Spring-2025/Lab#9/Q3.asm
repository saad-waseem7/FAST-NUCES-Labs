[org 0x0100]

jmp start

name    times 30 db 0
        db '$'

rollno  times 15 db 0
        db '$'

course  times 20 db 0
        db '$'

secchar     db '?', '$'

prompt1     db 'Enter your name: $'
prompt2     db 13,10,'Enter your roll number: $'
prompt3     db 13,10,'Enter course name: $'
prompt4     db 13,10,'Enter section: $'
msg_out     db 13,10,'Entered Information:',13,10,'$'
newline     db 13,10,'$'

start:
    ; Prompt Name
    mov dx, prompt1
    mov ah, 9
    int 21h
    mov si, name
    call input_string

    ; Prompt Roll Number
    mov dx, prompt2
    mov ah, 9
    int 21h
    mov si, rollno
    call input_string

    ; Prompt Course
    mov dx, prompt3
    mov ah, 9
    int 21h
    mov si, course
    call input_string

    ; Prompt Section
    mov dx, prompt4
    mov ah, 9
    int 21h
    mov ah, 01h
    int 21h
    mov [secchar], al

    call clear_screen

    ; Move to Row 12, Column 30
    mov ah, 02h
    mov bh, 0
    mov dh, 11     ; row (12th line)
    mov dl, 29     ; column (30th col)
    int 10h

    ; Show Output
    mov dx, msg_out
    mov ah, 9
    int 21h

    mov dx, name
    int 21h
    mov dx, newline
    int 21h

    mov dx, rollno
    int 21h
    mov dx, newline
    int 21h

    mov dx, course
    int 21h
    mov dx, newline
    int 21h

    mov ah, 02h
    mov dl, [secchar]
    int 21h

    ; Exit
    mov ax, 4C00h
    int 21h

; -----------------------
; Reads a line from keyboard into [SI]
; Ends with '$'
input_string:
    mov cx, 0
read_loop:
    mov ah, 01h
    int 21h
    cmp al, 13
    je done_input
    mov [si], al
    inc si
    inc cx
    cmp cx, 49
    je done_input
    jmp read_loop
done_input:
    mov byte [si], '$'
    ret

; -----------------------
clear_screen:
    mov ax, 0600h
    mov bh, 07h
    mov cx, 0
    mov dx, 184Fh
    int 10h
    ret
