
ASSUME cs:text_,ds:data_

data_ SEGMENT
a dw 1001
b dw 1003
rez dd ?
data_ ENDS

text_ SEGMENT

start:
mov ax, data_
mov ds, ax
; Evaluarea propriu-zisa a expresiei
mov ax, a ; ax = a
mul b ; ax = a*b

mov word ptr rez[2], dx
mov word ptr rez[1], ax ; rez= a*b
; Terminarea programului
mov ax, 4c00h
int 21h
text_ ENDS

END start