;1. Se da un sir de octeti in segmentul de date. Sa se construiasca sirul D care sa contina diferenta elementelor consecutive din sirul S si sa se afiseze acest sir pe ecran.
;Exemplu:
;S: 4, 2, 5, 3
;D: 2, -3, 2

assume cs:code, ds:data
data segment
s db 10, 8, 12, 13
ls equ $-s
d db ls-1 dup (?)
zece dw 10
data ends

code segment
start:
    mov ax, data
    mov ds, ax
    
    mov cx, ls
    
    mov si, offset s
    mov di, offset d
    
    dec cx
    repeta:
    mov bl, byte ptr s[si]
    sub bl, byte ptr s[si + 1]
    mov byte ptr d[di], bl
    inc si
    inc di
    loop repeta
    
    mov cx, ls
    dec cx
    
    mov di, offset d
    afiseaza:
        cmp byte ptr d[di], 0
        jl afisare_cu_semn
        jge afisare_fara_semn
        
    afisare_cu_semn:
        mov bl, 0
        sub bl, byte ptr d[di]
        mov byte ptr d[di], bl
        mov dx, '-'
        mov ah, 02h
        int 21h
    
    afisare_fara_semn:
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
        je afisare
        jne prelucrare
        
    afisare:
        pop dx
        add dx, '0'
        mov ah, 02h
        int 21h
    loop prelucrare
        mov dx, ' '
        mov ah, 02h
        int 21h
        mov cx, bx
        inc di
    loop afiseaza
    
    mov ax, 4C00h 
        int 21h
        code ends
        end start
        