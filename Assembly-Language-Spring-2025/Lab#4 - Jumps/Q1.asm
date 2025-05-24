[org 0x0100]

jmp start  

bx_val dw 0B189h   
ax_val dw 0ABA5h   

start:
    mov bx, [bx_val]  
    mov ax, [ax_val]  

    mov cx, 16      
    mov dl, 0       

count_one:
    rcr bx, 1       
    jnc skip_inc    
    inc dl          

skip_inc:
    loop count_one 

    mov cl, dl      
    mov ch, 0       

comp_bit:
    xor ax, 1       
    ror ax, 1       
    loop comp_bit  

    mov ax, 0x4c00
    int 0x21
