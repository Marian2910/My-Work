;Sa se citeasca de la tastatura un nr n intre 0 si 256 (byte) sa se genereze si sa se ;afiseze pe ecran secventa 1, 2, 3, ..., n-1, n

assume cs:code, ds:data
data segment
n db ?
zecew db 10
data ends

code segment
start:
    mov ax, data
    mov ds, ax
    
    mov ah, 01h
    int 21h
    mov n, al
    sub n, '0'
    
    mov bl, n
    dec bl
    mov cl, bl
    mov ch, 0
    
    mov dl, 1
    lucru:
        cmp dl, n
        ja afiseaza
        jb stop


        afiseaza:
            cmp dl, 9
            ja afiseaza_cu_stiva
            jb afiseaza_cifra

        afiseaza_cu_stiva:
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
        afiseaza_cifra:
            mov ah, 02h
        stop:
            inc dl
    loop lucru
            
        int 21h
    loop printeaza
    
    
    mov ax, 4C00h 
int 21h
code ends
end start
