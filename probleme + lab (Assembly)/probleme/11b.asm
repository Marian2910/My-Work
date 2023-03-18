;11. Se da un sir de dublucuvinte. Sa se genereze sirul D care sa contina toti octetii inferiori ai word-urilor superioare care au valoare divizibila cu 10. Sa se afiseze sirul D (in baza 10) pe ecran.
;Exemplu:
;S: 120A3478h, AB32CDABh, C5F3B1E5h
;D: 0Ah, 32h
;rezultat: 10, 50

assume cs:code, ds:data
data segment
s dd 120A3478h, 0AB32CDABh, 0C5F3B1E5h; s in memorie: (78)(34)[0A](12), (AB)(CD)[32](AB)...
ls equ ($-s)/4
d db ls dup (?)
ld dw 0
zeceb db 0Ah
zece dw 10
m db 'nu exista$'
lm db 9
data ends
code segment
start: 
    mov ax, data
    mov ds, ax
    
    mov ax, 0
    mov si, 2
    mov di, 0
    mov cx, ls
    cautare:
        mov al, byte ptr s[si]
        idiv zeceb
        cmp ah, 0
        je adauga
        jne next
    adauga:
        mov al, byte ptr s[si]
        mov byte ptr d[di], al
        inc di
        inc ld
    next:
        add si, 4
    loop cautare
    
    cmp di, 0
    jne exista
    je nuexista
    
    exista:
        mov cx, ld
        mov di, 0
        mov ax, 0
    afisare:
        mov bx, cx
        mov al, byte ptr d[di]
        mov cx, 0
        mov dx, 0
        cbw
    prelucrare:
        cwd
        idiv zece
        push dx
        inc cx
        cmp ax, 0
        je print
        jne prelucrare
    print:
        pop dx
        add dx, '0'
        mov ah, 02h
        int 21h
    loop print
        mov ah, 02h
        mov dx, ' '
        int 21h
        mov cx, bx
        inc di
    loop afisare
    
    jmp myendif
    
    nuexista:
        mov ah, 09h
        mov dx, offset m
        int 21h
        
    myendif:
    
    
    mov ax, 4c00h
    int 21h
    code ends
    end start