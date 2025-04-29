[org 0x100]  
jmp start  

; Data section
status_msg:     db 'PIC Status: 0x$'          ; Message for displaying PIC status
write_msg:      db 'Value written to PIC: 0x$' ; Message for displaying written value
hex_chars:      db '0123456789ABCDEF'         ; Lookup table for hex conversion
pic_value:      db 0x1F                       ; Value to write to PIC
newline:        db 0x0D, 0x0A, '$'            ; CRLF string for new line

; Function to clear the screen using BIOS video services
cls:  
    mov ax, 0x0003      ; Video mode 3 (text mode 80x25)
    int 0x10            ; Call BIOS video interrupt
    ret  

; Function to print a byte in hexadecimal format
; Input: AL = byte to print
print_hex:  
    pusha                   
    mov bx, hex_chars       ; Load address of hex characters lookup table
    mov cl, al             ; Copy input byte
    shr cl, 4              ; Shift right to get high nibble
    and cl, 0x0F           ; Mask off high bits
    mov si, bx             ; Get base of lookup table
    add si, cx             ; Add offset for high nibble
    mov dl, [si]           ; Get ASCII character
    mov ah, 02h            
    int 21h                
    
    mov cl, al             ; Get original byte again
    and cl, 0x0F           ; Mask to get low nibble
    mov si, bx             ; Get base of lookup table
    add si, cx             ; Add offset for low nibble
    mov dl, [si]           ; Get ASCII character
    mov ah, 02h            
    int 21h                
    popa                   
    ret  

; Program entry point
start:  
    ; Setup segment register
    mov ax, cs  
    mov ds, ax  
    
    ; Clear screen before displaying output
    call cls  
    
    ; Read current PIC status
    in al, 0x61           ; Read from PIC port 0x61
    mov dx, status_msg    ; Display status message
    mov ah, 09h  
    int 21h  
    call print_hex        ; Print current value
    mov dx, newline  
    mov ah, 09h  
    int 21h  
    
    ; Write new value to PIC
    mov al, [pic_value]   ; Get value to write
    out 0x61, al          ; Write to PIC port 0x61
    mov dx, write_msg     ; Display write message
    mov ah, 09h  
    int 21h  
    call print_hex        ; Print written value
    mov dx, newline  
    mov ah, 09h  
    int 21h  
    
    ; Wait for key press before exit
    mov ah, 01h  
    int 21h  

    mov ax, 0x4C00        
    int 21h
