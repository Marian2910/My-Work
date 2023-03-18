;14. Se dau A si B de tip byte, C word si D doubleword. Sa se calculeze expresia: C+(A*B-D+3)/(B*B-C) si sa se afiseze rezultatul pe ecran.
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
aux dd ?
zece dw 10
data ends
code segment
start:
    mov ax, data
    mov ds, ax
    
    ;C+(A*B-D+3)/(B*B-C)
    
    mov ax, 0
    mov dx, 0
    mov al, b
    mov bx, c
    imul b ; ax = b*b
    sub ax, c ;ax = (b*b-c)
    mov c, ax ; c = (b*b-c)
    
    mov ax, 0
    mov dx, 0
    
    mov al, 3
    cbw
    cwd
    add word ptr d[1], ax
    adc word ptr d[0], dx ; D = D + 3
    mov ax, 0
    mov dx, 0
    mov al, a
    imul b ; ax = a * b
    cwd 

    sub ax, word ptr d[1]
    sbb dx, word ptr d[0] ; (a * b - d + 3)

    idiv c
    
    mov word ptr d[1], ax
    mov word ptr d[0], dx
    
    mov ax, bx
    cwd
    
    add ax, word ptr d[1]
    adc dx, word ptr d[0]
    
    mov bx, ax
    mov ax, dx
    mov cx, 0
    repeta1:
        cwd
        idiv zece
        push dx
        inc cx
        cmp ax, 0
        je print1
        jne repeta1
    print1:
        pop dx
        add dx, '0'
        mov ah, 02h
        int 21h
    loop print1
    mov ax, bx
    mov cx, 0
    repeta2:
        cwd
        idiv zece
        push dx
        inc cx
        cmp ax, 0
        je print2
        jne repeta2
    print2:
        pop dx
        add dx, '0'
        mov ah, 02h
        int 21h
    loop print
    

    mov ax, 4C00h
    int 21h
    code ends
    end start