;Sa se citeasca un sir de cuvinte si sa se afiseze pe ecran suma octetilor superiori in ;baza 2.
;Sa se citeasca de la tastatura un nr n intre 0 si 256 (byte) sa se genereze si sa se ;afiseze pe ecran secventa 1, 2, 3, ..., n-1, n
assume cs:code, ds:data
data segment
  s dw 50, ?, 50 dup(?)
  bytez db 10
  d dw 50, ?, 50 dup(?)
  zecew dw 10
  ls db ?
data ends

code segment
start:
    mov ax, data
    mov ds, ax
    
    
    mov ah, 0Ah
    mov dx, offset s ; punem in dx adresa de inceput a sirului s
    int 21h
    mov bl, byte ptr s[1]; in bl punem numarul efectiv de termeni ai sirului s
    mov si, 2
    mov ls, bl
    
    mov cl, ls
    mov ch, 0
    
    mov ax, 0
    repeta1:
    mov bl,byte ptr s[si]
    sub bl, '0'
    imul bytez
    mov bl, 0
    add ax, bx
    inc si
    cmp s[si], ' '
    jne repeta1
    je adauga
    
    mov di, 0
    adauga:
        mov d[di], ax
        inc di
    
    mov dl, 0
    mov si, 2
    mov cl, ls
    mov ch, 0
    repeta:
    add dl, byte ptr d[si]
    add si, 2
    loop repeta
    
    mov al, dl
    cbw
    mov cx, 0
    mov dx, 0
    prelucrare:
        cwd
        idiv zecew
        push dx
        inc cx
        cmp ax, 0
        jne prelucrare
        je printeaza
        
    printeaza:
        pop dx
        add dx ,'0'
        mov ah, 02h
        int 21h
    loop printeaza
    
    mov ax, 4C00h 
int 21h
code ends
end start