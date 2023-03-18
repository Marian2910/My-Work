;15. Se dau A si B de tip byte, C word si D doubleword. Sa se calculeze expresia: C+(A*B-D+3)/(B*B-C) si sa se afiseze rezultatul pe ecran.
;Exemplu:
;A = 12
;B = 104
;C = 12325
;D = 75412
;rezultat: 12374

assume cs:code, ds:data
data segment
    a db 12
    b db 104
    c dw 12325
    d dd 75412
    zece dw 10
data ends
code segment
start:
    mov ax, data
    mov ds, ax
    
    mov ax, 0
    mov al, a
    imul b ; ax = a*b
    mov bx, ax; bx = ax = a*b
    
    mov al, 3
    cbw
    cwd
    add word ptr d[1], ax
    adc word ptr d[0], dx
    
    mov ax, bx
    cwd
    
    sbb ax, word ptr d[1]
    sub dx, word ptr d[0] ; ax:dx = a*b-d+3
    
    mov word ptr d[1], ax
    mov word ptr d[0], dx; d = a*b-d+3
    mov al , b
    mov ah , 0
    imul b; ax = b*b
    sub ax, c
    mov cx, ax; cx = ax = b*b - c
    
    mov ax, word ptr d[1]
    mov dx, word ptr d[0]; d = a*b-d+3
    idiv cx
    add ax, c
    mov cx, 0
    mov dx, 0
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
    
    mov ax, 4C00h
    int 21h
    code ends
    end start