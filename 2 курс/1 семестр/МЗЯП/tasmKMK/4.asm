.model small
.stack 100h
.data
x     db     10011000b

.code
Start:
mov   ax,    @data
mov   ds,    ax

mov   al,    x
and   al,    00001000b
shl   al,    2

mov   ah,    x
and   ah,    00100000b
shr   ah,    2

and   x,     11010111b
or    x,     al
or    x,     ah

sub   ax,    ax
mov   al,    x
sal   ax,    3
not   ax

mov   ax,     4C00h
int   21h
end start