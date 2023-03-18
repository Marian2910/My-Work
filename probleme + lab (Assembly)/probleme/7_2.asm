;8. Sa se citeasca un sir de caractere si un caracter sa se afiseze daca apare acel caracter in sir.
;Exemplu:
;S: "ana are 3 mere!"
;s: "a"
;rezultat: "DA"


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
    
    mov ah, 08h
    int 21h
    
    mov cl, byte ptr s[1]
    mov ch, 0
    mov dx, 0
    mov si, 2
    cauta:
        cmp byte ptr s[si], al
        je afirmativ
        jne negativ
    afirmativ:
        mov dx, 1
    negativ:
        inc si
    loop cauta
    
    cmp dx, 1
        je mesaj1
        jne mesaj2
    
    mesaj1:
        mov ah, 02h
        mov dx, 'D'
        int 21h
        mov dx, 'A'
        int 21h
        jmp next
        
    mesaj2:
        mov ah, 02h
        mov dx, 'N'
        int 21h
        mov dx, 'U'
        int 21h
    next:
    
    mov ax, 4c00h
    int 21h
    code ends
    end start