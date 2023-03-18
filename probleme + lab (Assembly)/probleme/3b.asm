;3. Sa se citeasca de la tastatura un sir de caractere S si sa se inlocuiasca toate cifrele cu simbolul '%'. Sa se afiseze sirul rezultat pe ecran.
;Exemplu:
;S: "Ana are 3 mere si 4 pere."
;rezultat: "Ana are % mere si % pere."

assume cs:code, ds:data
data segment
s db 40, ?, 40 dup (?)
ls db 0
data ends
code segment
start: 
    mov ax, data
    mov ds, ax
    
    mov ax, 0
    mov dx, offset s
    mov ah, 0Ah
    int 21h
    
    mov cl, byte ptr s[1]
    mov ch, 0
    mov ls, cl
    mov si, 2
    cauta:
        mov al, byte ptr s[si]
        cmp al, '0'
        jae mai_verifica
        jb next
    mai_verifica:
        cmp al, '9'
        jbe inlocuieste
        ja next
    inlocuieste:
        mov al, '%'
        mov byte ptr s[si], al
    next:
        inc si
    loop cauta
    
    inc si
    mov byte ptr s[si], '$'
    
    mov dx, offset s + 2
    mov ah, 09h
    int 21h
    
    mov ax, 4c00h
    int 21h
    code ends
    end start