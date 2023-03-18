;10. Se da un sir de dublucuvinte. Sa se calculeze si sa se salveze in sirul D toti octetii superiori ai wordurilor inferioare care au valoare impara si pozitiva.



assume cs:code, ds:data
data segment
  s dd 12340578h, 1A2B3C4Dh, 0FE37DC76h; 11111111h, 10011300h, 21911011h, 10011300h, 10010700h
  l equ ($-s)/4
  d db l dup (?)
data ends

code segment
    start:
    mov ax, data
    mov ds, ax

    mov si, 1 
    mov di, 0
        
    mov cx, l
    
    repeta:
        mov bx, word ptr s[si]
        cmp bh, 0
        jg impar_par
        jle nuadauga  
    impar_par:
        mov al, bh
        cbw
        mov dx, 0
        mov dl, 2 ; dl = 2
        idiv dl ; ax = ax/2 ( ah -restul, al - catul)
        cmp ah, 1
        je adauga
        jne nuadauga
        
    adauga: 
        mov byte ptr d[di], bl
        inc di
        add si, 4
        jmp myendif
    
    nuadauga: 
        add si, 4
    myendif:
    loop repeta
    
        
    mov ax, 4c00h ; terminam programul
    int 21h
code ends
end start
    