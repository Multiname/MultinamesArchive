.model small
.486
.stack 100h
.data
a     db     100
b     db     -1
x     db     100
yQuo  dw     0
yRem  dw     0
temp  dd     0

.code
Start:
mov   ax,    @data
mov   ds,    ax
mov   ax,    0

mov   al,    b
mov   dx,    3
imul  dl
mov   bx,    ax
mov   ax,    0

mov   al,    a
imul  a
movsx cx,    x
add   ax,    cx
mov   dx,    2
imul  dx
mov   cx,    ax
mov   ax,    0

mov   al,    x
imul  x
imul  bx
mov   si,    offset temp
mov   [si], ax
mov   [si] + 2, dx

mov   ax,     cx
cwde
sub   eax,    temp
mov   temp,   eax
mov   eax,    0

mov   ax,     bx
mov   bx,     2
imul  bx
mov   bx,     ax
mov   ax,     0

mov   ax,     [si]
mov   dx,     [si] + 2
idiv  bx

mov   yQuo,   ax
mov   yRem,   dx

mov   ax,     4C00h
int   21h
end start
END