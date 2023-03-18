;2. Sa se citeasca de la tastatura un sir de octeti S si sa se afiseze pe ecran diferenta lor.
;Exemplu:
;S: 12, 3, 4, 6
;Diferenta: -1

assume cs:code, ds:data
data segment
    ;s db 10, ?, 10 dup (?)
    s db 100, 100, 10, 10
    ls equ $-s
    d db ?
    zece dw 10
data ends

code segment
start:
    mov ax, data
    mov ds, ax
    
    ;cld
    ;mov ah, 0Ah
    ;mov dx, offset s
    ;int 21h
    
    ;mov si, 2
    mov si, offset s
    ;mov cl, byte ptr s[1]
    mov cl, ls
    mov ch, 0
        
    mov ax, 0
    lodsb
    cbw
    ;sub ax, '0'
    mov d, al
    
    mov ax, 0
    dec cx
    repeta:
        lodsb
        ;cbw
        ;sub ax, '0'
        sub d, al
    loop repeta
    
    cmp d, 0
    jge afisare_fara_semn
    jl printeaza_semn
    
    printeaza_semn:
    mov bl, 0
    sub bl, d
    mov d, bl
    mov dx, '-'
    mov ah, 02h
    int 21h
  
    afisare_fara_semn: 
    mov al, d
    cbw
    mov cx, 0
    mov dx, 0
    prelucrare:
        cwd
        idiv zece
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

        
        