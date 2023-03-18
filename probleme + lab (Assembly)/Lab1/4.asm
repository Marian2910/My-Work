;4. Se da un numar n (0<n<256) in segmentul de date. Sa se genereze si sa se afiseze pe ecran secventa 3, 6, 9, ..., 3n-3, 3n.
;Exemplu:
;n = 6
;rezultat: 3, 6, 9, 12, 15, 18
assume cs:code, ds:data
data segment
n db 3, ?, 3 dup (?)
data ends
code segment:
start:
    mov ax, data
    mov ds, ax
    
    mov dx, offset n
    mov ah, 0Ah
    int 21h
    
    mov cl, byte ptr n[2]
    sub cl, '0'
    mov ch, 0
    mov dx, 0
    calculeaza:
        add dl, 3
        mov ah, 02h
        int 21h
    loop calculeaza
    
    mov ax, 4C00h
    int 21h
    code ends
    end start