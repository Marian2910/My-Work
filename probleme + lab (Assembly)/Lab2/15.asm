;z=((a+b*c-d)/f+h)/g

assume cs:code, ds:data
data segment
a dw 2
b db 3
c db 2
d dw 4
f dw 2
h dw 2
g dw 2
data ends
code segment
start:
mov ax,data
mov ds,ax

mov al,b
mul c; ax=b*c
add ax,a
sub ax,d

mov dx,0
div f
add ax, h
mov dx, 0
div g
;in ax este rezultatul

mov ax,4C00h
int 21h
code ends
end start