;3. Sa dau doua sirurui de octeti A si B. Sa se construiasca sirul D1 care sa contina doar numerele impare si pozitive din A si B si sirul D2 care sa contina numerele negative divizibile cu 5 din sirurile A si B. Sa se afiseze pe ecran sirurile rezultat.
;Exemplu:
;A: 2, 1, -3, 3, -5, 2, 6
;B: 4, 5, 7, -15, 2, 1
;D1: 1, 3, 5, 7, 1
;D2: -5, -15

assume cs:code, ds:data
data segment
a db 2, -1, -3, 3, -5, 2, 6
la equ $-a
b db 4, 5, 7, -15, 2, 1
lb equ $-b
d1 db la+lb dup (?)
d2 db la+lb dup (?)
ld1 db 0
ld2 db 0
zece dw 10
data ends

code segment
start:
    mov ax, data
    mov ds, ax
    
    mov ax, 0
    mov si, offset a; a[si]
    mov di, 0; d1[di]
    mov bp, 0; d2[bp]
    
    mov cx, la
    repeta:
        cmp byte ptr a[si], 0
        jge pozitiv
        jl negativ
        
    pozitiv:
        mov al, byte ptr a[si]
        cbw
        mov bl, 2
        idiv bl
        cmp ah, 0
        je myendif
        jne impar
        
    impar:
        mov al, byte ptr a[si]
        mov byte ptr d1[di], al
        inc di
        inc ld1
        jmp myendif
        
    negativ:
        mov al, byte ptr a[si]
        cbw
        mov bl, 5
        idiv bl
        cmp ah, 0
        je div5
        jne myendif
        
    div5:
        mov al, byte ptr a[si]
        mov byte ptr d2[bp], al
        inc bp
        inc ld2
        jmp myendif
    
    myendif:
        inc si
    loop repeta
    
        mov si, offset b
        mov cx, lb
    repeta2:
        cmp byte ptr b[si], 0
        jge pozitiv2
        jl negativ2
        
    pozitiv2:
        mov al, byte ptr b[si]
        cbw
        mov bl, 2
        idiv bl
        cmp ah, 0
        je myendif2
        jne impar2
        
    impar2:
        mov al, byte ptr b[si]
        mov byte ptr d1[di], al
        inc di
        inc ld1
        jmp myendif2
        
    negativ2:
        mov al, byte ptr b[si]
        cbw
        mov bl, 5
        idiv bl
        cmp ah, 0
        je div5_2
        jne myendif
        
    div5_2:
        mov al, byte ptr b[si]
        mov byte ptr d2[bp], al
        inc bp
        inc ld2
        jmp myendif2
    
    myendif2:
        inc si
    loop repeta2
    
        mov cl, ld1
        mov ch, 0
    dec cx
    
    mov di, offset d2
        
    afisare_cu_semn:
        mov bl, 0
        sub bl, byte ptr d2[di]
        mov byte ptr d2[di], bl
        mov dx, '-'
        mov ah, 02h
        int 21h
    afisare_fara_semn:
        mov bx, cx
        mov cx, 0
        mov dx, 0
        mov al, byte ptr d1[di]
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
    loop afisare
        mov dx, ' '
        mov ah, 02h
        int 21h
        mov cx, bx
        inc di
    loop afisare_cu_semn
    
    mov ax, 4c00h
    int 21h
    code ends
    end start

