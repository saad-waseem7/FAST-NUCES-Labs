[org 0x0100]

jmp start  

arr db 19, 10, 8, 17, 9, 15, -1  
arr_size db 0   
min_value db 0  
max_value db 0  
sum_value db 0  
avg_value db 0

start:
    mov si, arr      
    call SizeArray   
    mov [arr_size], cl  

    call FindMin     ; Find minimum
    mov [min_value], al

    call FindMax     ; Find maximum
    mov [max_value], al

    call CalcSum     ; Calculate sum
    mov [sum_value], al

    call CalcAvg     ; Calculate average
    mov [avg_value], al

    mov ax, 0x4c00
    int 0x21

; ----------------- Subroutine: Find Size -----------------
SizeArray:
    mov cl, 0   

count_loop:
    cmp byte [si], -1  
    je done_count
    inc si
    inc cl
    jmp count_loop

done_count:
    ret

; ----------------- Subroutine: Find Minimum -----------------
FindMin:
    mov al, [arr]  
    mov si, arr    

min_loop:
    cmp byte [si], -1
    je done_min
    cmp al, [si]   
    jle skip_min
    mov al, [si]   

skip_min:
    inc si
    jmp min_loop

done_min:
    ret

; ----------------- Subroutine: Find Maximum -----------------
FindMax:
    mov al, [arr]
    mov si, arr

max_loop:
    cmp byte [si], -1
    je done_max
    cmp al, [si]
    jge skip_max
    mov al, [si]   

skip_max:
    inc si
    jmp max_loop

done_max:
    ret

; ----------------- Subroutine: Calculate Sum -----------------
CalcSum:
    mov al, 0
    mov si, arr

sum_loop:
    cmp byte [si], -1
    je done_sum
    add al, [si] 
    inc si
    jmp sum_loop

done_sum:
    ret

; ----------------- Subroutine: Calculate Average -----------------
CalcAvg:
    mov ah, 0
    mov cl, [arr_size]
    div cl  ; AL = AL / CL (average)
    ret
