;8. Sa se citeasca un sir de caractere si sa se afiseze cate litere contine.
;Exemplu:
;S: "ana are 3 mere!"
;rezultat: 10


assume cs:code, ds:data
data segment
s db 50, ?, 50 dup (?)
data ends
code segment
start:
    mov ax, data
    mov ds, ax
    
    mov dx, offset s
    mov ah, 0Ah
    int 21h
    
    mov cl, byte ptr s[1]
    mov ch, 0
    mov dx, 0
    mov si, 2
    cauta:
        cmp byte ptr s[si], 'A'
        jae verifica
        jb next
    verifica:
        cmp byte ptr s[si], 'z'
        ja next
        jbe numara
    numara:
        inc dx
    next:
        inc si
    loop cauta
    
    mov ax, dx
    mov cx, 0
    mov dx, 0
    mov bx, 10
    prelucrare:
    cwd
    div bx
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
    
    
    mov ax, 4c00h
    int 21h
    code ends
    end start