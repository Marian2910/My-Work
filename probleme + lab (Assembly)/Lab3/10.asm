;10. Se dau cuvintele A si B. Se cere cuvântul C:
;- bitii 0-2 ai lui C au valoarea 1
;- bitii 3-8 ai lui C coincid cu bitii 0-5 ai lui A
;- bitii 9-12 ai lui C coincid cu bitii 11-14 ai lui B
;- bitii 13-15 ai lui C au valoarea 0
;000(B14B13B12B11A5)|(A4A3A2A1A0)111b

assume cs:code, ds:data
data segment
  a dw 0A5C3h ; 1010010111000011
  b dw 0CE39h ; 1100111000111001
  c dw ?
data ends

code segment
start:
mov ax, data
mov ds, ax

shr cx, 15; cx = 0000000000000000b
mov ax, a ;
or cl, al; 
stc; CF = 1
rcl cl, 1; 
stc; CF = 1
rcl cl, 1; 
stc; CF = 1
rcl cl, 1; cl = A4A3A2A1A0111b

mov bx, b; 
mov dl, al; dl = A7A6A5A4A3A2A1A0b
shl dl, 2; dl = A5A4A3A2A1A000b
shr dl, 7; dl = 0000000A5b

shl bh, 1; bh = 10110110b
or ch, bh; ch = bh ; ch = B14B13B12B11B10B9B80b
shr ch, 4 ; ch = 0000B14B13B12B11b
clc; cf = 0
rcr dl, 1; cf = A5
rcl ch, 1; ch = 000B14B13B12B1A5b



mov c, cx; rezultatul este in c = 121Fh
mov ax, 4C00h
int 21h
code ends
end start