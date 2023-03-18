;10. Se dau 2 siruri de octeti S1 si S2 de aceeasi lungime. Sa se construiasca sirul D astfel incat fiecare element din D sa ;reprezinte maximul dintre elementele de pe pozitiile ;corespunzatoare din S1 si S2. 
;Exemplu:
;S1: 1, 3, 6, 2, 3, 7
;S2: 6, 3, 8, 1, 2, 5
;D: 6, 3, 8, 2, 3, 7

assume cs:code, ds:data
data segment
  s1 db 1h, 3h, 6h, 2h, 3h, 7h
  l equ ($-s1)
  s2 db 6h, 3h, 8h, 1h, 2h, 5h
  d db l dup (?)
data ends

code segment
    start:
    mov ax, data
    mov ds, ax

    mov si, 0 
    ;mov di, 0
        
    mov cx, l
    repeta:
        mov al, byte ptr s1[si]
        mov bl, byte ptr s2[si]
        cmp al, bl
        ja adaugas1
        jb adaugas2  
    adaugas1: 
        mov al, byte ptr s1[si]
        mov byte ptr d[si], al
        inc si
        jmp myendif
        
    adaugas2: 
        mov al, byte ptr s2[si]
        mov byte ptr d[si], al
        inc si
    myendif:
    loop repeta
    
    
        
    mov ax, 4c00h ; terminam programul
    int 21h
code ends
end start
    