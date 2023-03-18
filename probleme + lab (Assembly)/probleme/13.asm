;12. Se citesc de la tastatura doua cuvinte A si B. Sa se calculeze si sa se afiseze cuvantul pe ecran cuvantul C astfel:
;- bitii 0-3 ai lui C coincid cu bitii 6-9 ai lui A
;- bitii 4-6 ai lui C au valoarea 1
;- bitii 7-10 ai lui C coincid cu bitii 0-3 ai lui A
;- bitii 11-15 ai lui C coincid cu bitii 3-7 ai lui B
;Exemplu:
;A = 42590; {1010}01(1001)011110 ; {1011}01(0101)011110
;B = 15955; 111|11001|010011
;C = 80305?; (1001)[111]{1010}|11110|

assume cs:code, ds:data
data segment
a dw 8, ?, 8 dup (?)
an dw ?
b dw 8, ?, 8 dup (?)
bn dw ?
c dw ?
zece dw 10
doi dw 2
data ends
code segment
start:
    mov ax, data
    mov ds, ax
    
    mov ax, 0
    mov dx, offset a
    mov ah, 0Ah
    int 21h
    
    mov ax, 0
    mov dx, 0
    
    mov dx, offset b
    mov ah, 0Ah
    int 21h
    
    mov cl, byte ptr a[1]
    mov si, 2
    mov ax, 0
    repeta1:
        mov bl, byte ptr a[si]
        sub bl, '0'
        imul zece
        add al, bl
        inc si
    loop repeta1
    
    mov an, ax
    
    mov cl, byte ptr b[1]
    mov si, 2
    mov ax, 0
    repeta2:
        mov bl, byte ptr b[si]
        sub bl, '0'
        imul zece
        add al, bl
        inc si
    loop repeta2
    
    mov bn, ax
    mov ax, 0
        
    mov cx, 0
    mov bx, an
    mov dx, bn
    
    shr bx, 6 ; 000000101101(0101)
    shl bx, 12; (0101)0000000000
    or cx, bx; c = (0101)0000000000
    mov ax, 0000111000000000b
    or cx, ax; (0101)1110000000
    mov bx, an
    shr bx, 12; 000000000000{1011}
    shl bx, 5; (0000)[000]{1011}00000
    or cx, bx; (0101)[111]{1011}00000
    shl dx, 3; |11110|00000000000
    shr dx, 11; 00000000000|11110|
    or cx, dx; (0101)[111]{1011}|11110|
    
    mov ax, cx
    mov cx, 0
    mov dx, 0
    prelucrare:
        cwd
        idiv doi
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