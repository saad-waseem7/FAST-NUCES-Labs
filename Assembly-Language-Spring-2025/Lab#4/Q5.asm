[org 0x0100]

start:
    mov ax, 0B25Dh 

    mov bl, al      
    mov bh, ah      

    mov cl, al      
    and cl, 0Fh     
    and al, 0F0h    
    shr al, 4       
    shl cl, 4       
    or al, cl       

    mov cl, ah      
    and cl, 0Fh     
    and ah, 0F0h    
    shr ah, 4       
    shl cl, 4       
    or ah, cl       

    mov ax, 0x4c00
    int 0x21
