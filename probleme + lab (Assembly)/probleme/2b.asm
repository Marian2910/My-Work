;2. Sa se citeasca de la tastatura un sir de octeti S si sa se afiseze pe ecran suma lor.
;Exemplu:
;S: 1, 2, 3, 4
;Suma: 10

assume cs:code, ds:data
data segment
s db 50, ?, 50 dup (?)
zece dw 10
zeceb db 10
data ends
code segment
start:
    mov ax, data
    mov ds, ax
    
    mov ah, 0Ah
    mov dx, offset s
    int 21h
    
    mov cl, byte ptr s[1]
    mov ch, 0
    mov si, 2
    mov bx, 0
    mov ax, 0
    mov dx, 0

    suma:
        mov bl, byte ptr s[si]
        mov bh, 0
        cmp bl, ' '
        je next
        jne creeaza
    next:
        add dx, ax
        mov ax, 0
        mov bx, '0'
    creeaza:
        sub bl, '0'
        imul zeceb
        add ax, bx
        inc si
    loop suma
        mov bx, dx
        
        mov dx, 10
        mov ah, 02h
        int 21h
        mov ax, 0
        
        mov ax, bx
        mov cx, 0
        mov dx, 0
    
    prelucrare:
        cwd
        idiv zece
        push dx
        inc cx
        cmp ax, 0
        je adauga
        jne prelucrare
        
    adauga:
        pop dx
        add dx, '0'
        mov ah, 02h
        int 21h
    loop adauga
    
    mov ax, 4c00h
    int 21h
    code ends
    end start