.model small
.stack 100h
.data
a     db     1
b     db     1
x     db     1
y     dw     0

.code
Start:
mov   ax,    @data
mov   ds,    ax
mov   ax,    0

mov   al,    b
mov   dx,    3
mul   dl
mov   bx,    ax
mov   ax,    0

mov   al,    a
mul   a
add   al,    x
mov   dx,    2
mul   dl
mov   cx,    ax
mov   ax,    0

mov   al,    x
mul   x
mul   bl

sub   cx,     ax

mov   ax,     bx
mul   dl
mov   bx,     ax

mov   ax,     cx
div   bl

mov   y,      ax

mov   ax,     4C00h
int   21h
end start
END