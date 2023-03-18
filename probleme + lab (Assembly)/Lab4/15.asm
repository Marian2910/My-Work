;15. Se da un sir de dublucuvinte. Sa se salveze in sirul D in ordine inversa toate cuvintele din sirul initial.

assume cs:code, ds:data
data segment
  s dd 12345678h, 1A2B3C4Dh, 0FC98DC76h ;
  l equ ($-s)/4
  d dw 2*l dup (?)
data ends

code segment
    start:
    mov ax, data
    mov ds, ax
    
    mov si, l*4 - 4 
    mov di, 0
    mov cx, l
    
    repeta:
        mov ax, word ptr s[si] 
        mov dx, word ptr s[si + 2]
        mov word ptr d[di], ax
        mov word ptr d[di+ 2], dx
        sub si, 4
        add di, 4
    loop repeta
    
        
    mov ax, 4c00h
    int 21h
code ends
end start
    