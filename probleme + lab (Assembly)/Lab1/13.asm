;13. Se citesc de la tastatura doua cuvinte A si B. Sa se calculeze si sa se afiseze cuvantul pe ecran, cuvantul C astfel:
;- bitii 0-3 ai lui C coincid cu bitii 4-7 ai lui A
;- bitii 4-7 ai lui C coincid cu bitii 1-4 ai lui B
;- bitii 8-10 ai lui C sunt 0
;- bitii 11-15 ai lui C coincid cu bitii 7-11 ai lui B
;Exemplu:
;A = 12487; 1100[0011]000111
;B = 35147; (1000)100101001011
;C = 36956

assume cs:code, ds:data
data segment
a dw 1, ?, 1 dup (?)
b dw 1, ?, 1 dup (?)
c dw ?
zece dw 10
data ends
code segment
start:
    mov ax, data
    mov ds, ax
    
    mov ax, 0
    mov dx, offset a
    mov ah, 0Ah
    int 21h
    
    mov dx, offset b
    int 21h
    
    mov c, 0
    mov bx, word ptr a[2]
    mov dx, word ptr b[2]
    
    shr bx, 6 ; 0000001100[0011]
    shl bx, 10; [0011]0000000000
    or c, bx; c = [0011]0000000000
    shr dx, 12;     000000000000(1000)
    shl dx, 8; 0000(1000)00000000
    or c, dx; c = [0011](1000)000{00000}
    mov dx, word ptr b[2] ;1000100{10100}1011
    shl dx, 11
    shr dx, 11
    or c, dx
    
    mov ax, c
    mov cx, 0
    mov dx, 0
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
    
    
    
    mov ax, 4C00h
    int 21h
    code ends
    end start