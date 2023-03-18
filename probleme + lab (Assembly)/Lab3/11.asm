;11. Se dau octetii A si B. Sa se obtina cuvântul C:
;- bitii 0-2 ai lui C au valoarea 110
;- bitii 3-6 ai lui C coincid cu bitii 0-3 ai lui A
;- bitii 7-10 ai lui C au valoarea 0
;- bitii 11-15 ai lui C coincid cu bitii 0-4 ai lui B

assume cs:code, ds:data
data segment
  a db 01110111b
  b db 10011011b
  c dw ?
data ends

code segment
start:
mov ax, data
mov ds, ax

shr cx, 15; cx = 0000000000000000h
mov bl, b ; bl = b = 10011011b
or ch, bl; ch = 10011011b
shl ch, 3; ch = 11011000b

mov al, a; al = 01110111b
or cl, al; cl = al
shl cl, 4; cl = 01110000b
;shr cl, 2; cl = 00011100b
mov dl, 00000110b
or cl, dl
;stc; CF=1
;rcl cl, 1
;rcl cl, 1; adaugam 1 pe ultimele 2 pozitii cl = 00111011b
;rol cl, 1; rotim bitii la stanga cu o pozitie pentru a obtine 110 cl = 01110110b


mov c, cx; rezultatul este in c = 1101100001110110b = D876h

mov ax, 4c00h
int 21h
code ends
end start