;z=(5*a-b/7)/(3/b+a*a)
assume cs:code,ds:data
data segment
a db 1
b db 7
z dw ?
data ends

code segment
start:
mov ax,data
mov ds,ax

mov al,5
mul a;ax=5*a
mov dx,ax
mov al,b
mov ah,0
mov ch,7
div ch ;ax=b/7
sub dx,ax ;dx=5*a-b/7
mov ax,3
div b;al=3/b
mov ah,0
mov bx,ax;bx=3/b
mov al,a
mul a;ax=a*a
add bx,ax ;bx=3/b+a*a
mov ax,dx;ax=5*a-b/7
mov dx,0
div bx
mov z,ax 

mov ax, 4C00h
int 21h
code ends
end start