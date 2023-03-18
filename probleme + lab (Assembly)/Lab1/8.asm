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
        cmp byte ptr s[si], 'a'
        ja verifica
        jb next
    verifica:
        cmp byte ptr s[si], 'Z'
        ja next
        jb numara
    numara:
        inc dx
    next:
        inc si
    loop cauta
    
    add dx, '0'
    mov ah, 02h
    int 21h
    
    
    mov ax, 4c00h
    int 21h
    code ends
    end start