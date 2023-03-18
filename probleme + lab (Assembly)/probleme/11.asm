;11. Se da un sir de dublucuvinte. Sa se genereze sirul D care sa contina toti octetii inferiori ai word-urilor superioare care au ultima cifra egala cu 8. Sa se afiseze sirul D (in baza 10) pe ecran.
;Exemplu:
;S: 12443478h, AB32CDABh, C576B1E5h
;D: 44h, 76h
;rezultat: 68, 118

assume cs:code, ds:data
data segment
s dd 12443478h, 0AB32CDABh, 0C576B1E5h ; in memorie (78)(34)[44](12), (AB)(CD)[32](AB)
ls equ ($-s)/4
d db ls dup (?)
ld dw 0
zece dw 10
zeceb db 10
data ends

code segment
start:
    mov ax, data
    mov ds, ax
    
    mov ax, 0
    mov si, 2
    mov di, 0
    mov cx, ls
    repeta:
        mov al, byte ptr s[si]
        cbw
        idiv zeceb
        cmp ah, 8
        je adauga
        jne next
    adauga:
        mov al,byte ptr s[si] 
        mov byte ptr d[di], al
        inc di
        inc ld
    next:
        add si, 4
    loop repeta
        mov cx, ld
        mov di, 0
    afisare:
        mov bx, cx
        mov cx, 0
        mov dx, 0
        mov al, byte ptr d[di]
        cbw
    prelucrare:
        cwd
        idiv zece
        push dx
        inc cx
        cmp ax, 0
        je printeaza
        jne prelucrare
    printeaza:
        pop dx
        add dx, '0'
        mov ah, 02h
        int 21h
    loop printeaza
        mov dx, ' '
        mov ah, 02h
        int 21h
        mov cx, bx
        inc di
    loop afisare
    
    mov ax, 4C00h
    int 21h
    code ends
    end start