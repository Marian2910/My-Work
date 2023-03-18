;6. Se da un numar n (0<n<256) in segmentul de date. Sa se genereze primii n termeni din sirul lui Fibonacci si sa se afiseze pe ecran al n-lea termen.
;Exemplu:
;n = 6
;rezultat: 8

assume cs:code, ds:data
data s
egment
n db ?
c db 1
zece dw 10
data ends

code segment
start:
    mov ax, data
    mov ds, ax
    
    mov ax, 0
    mov ah, 08h
    int 21h
    
    sub al, '0'
    cbw
    mov cx, ax
    
    mov bl, 1
    mov dx, 0
    cmp al, 2
    ja genereaza
    jb printeaza1
    
    printeaza1:
        mov dx, '1'
        mov ah, 02h
        int 21h
        jmp myendif
    
    genereaza:
    sub cx, 2
    repeta:
        mov dl, bl
        add bl, c;
        mov c, dl;
    loop repeta
    
    mov cx, 0
    mov dx, 0
    mov al, bl
    cbw
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
        
        myendif:
        
        mov ax, 4C00h 
        int 21h
        code ends
        end start
