;10. Se citeste un sir de caractere de la tastatura. Se da o constanta K reprezentand o litera. Sa se determine numarul de aparitii a lui K in sirul citit. Sa se afiseze acest numar pe ecran.

assume cs:code, ds:data
data segment
  s db 50, ?, 50 dup(?)
  k db ?
  contor dw 0
  zecew dw 10
data ends

code segment
start:
    mov ax, data
    mov ds, ax
    
    mov ah, 01h
    int 21h ; in al se afla codul ascii a caracterului introdus
    mov k, al
    
    mov ah, 0Ah
    mov dx, offset s ; punem in dx adresa de inceput a sirului s
    int 21h
    mov bl, byte ptr s[1]; in bl punem numarul efectiv de termeni ai sirului s
    mov si, 2
    mov cl, bl
    mov ch, 0
    mov al, k ; punem pe k intr-un registru ca sa-l putem compara
    repeta:
        cmp al, s[si]
        je numara
        jne myendif
        
    numara:
        inc contor ; daca k (=al) = s[si] vom numara acel caracter
    myendif:
        inc si
loop repeta
    
    
    mov ax, contor
    mov cx, 0
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
        add dl ,'0'
        mov ah, 02h
        int 21h
    loop printeaza

mov ax, 4C00h 
int 21h
code ends
end start
    