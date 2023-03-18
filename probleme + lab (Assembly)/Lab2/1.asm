;z=1/(a*a+b*b-5)+2/(a*a-b*b+4)
assume cs:code,ds:data
data segment
a db 4
b db 3
z dw ?
data ends
code segment
start:
mov ax,data
mov ds,ax

mov al,a
mul a; ax=a*a
mov bx,ax; bx=a*a
mov al,b
mul b; ax=b*b
add ax,bx
sub ax,5; ax=a*a+b*b-5
mov bx,ax; bx=a*a+b*b-5
mov ax,1
mov dx,0
div bx; ax=1/(a*a+b*b-5)

mov cx,ax; cx=1/(a*a+b*b-5)

mov al,a
mul a; ax=a*a
mov bx,ax; bx=a*a
mov al,b
mul b; ax=b*b
sub bx,ax
add bx,4; bx=a*a-b*b+4
mov ax,2
mov dx,0;
div bx; ax=2/(a*a-b*b+4)

add ax,cx
mov z,ax; z=1/(a*a+b*b-5)+2/(a*a-b*b+4)

mov ax,4C00h
int 21h
code ends
end start