.model small
.stack 100h
.data
X1   db     99
X2   db     0B6h
X3   db     201
a    db     21
b    db     36h
c    db     7
d    db     2

sum  db     3 dup(0)
dif  db     3 dup(0)
pro  dw     3 dup(1)
rem  dw     3 dup(?)
quo  dw     3 dup(?)

res  dw     3 dup(0)

.code
Start:
mov  ax,    @data
mov  ds,    ax

mov  ax,    0

mov  al,    X1
sub  al,    a
mov  dif,   al

add  al,    b
mov  sum,   al

mov  al,    c
mul  sum
mov  pro,   ax

mov  dx,    0
mov  bx,    0
mov  bl,    d
div  bx
mov  rem,   dx
mov  quo,   ax

inc  ax
dec  dx
mov  bx,    ax
add  bx,    dx
mov  res,   bx


mov  ax,  0

mov  al,    X2
sub  al,    a
mov  dif+1, al

add  al,    b
mov  sum+1, al

mov  al,    c
mul  sum+1
mov  pro+2, ax

mov  dx,    0
mov  bx,    0
mov  bl,    d
div  bx
mov  rem+2, dx
mov  quo+2, ax

inc  ax
dec  dx
mov  bx,    ax
add  bx,    dx
mov  res+2, bx


mov  ax,  0

mov  al,    X3
sub  al,    a
mov  dif+2, al

add  al,    b
mov  sum+2, al

mov  al,    c
mul  sum+2
mov  pro+4, ax

mov  dx,    0
mov  bx,    0
mov  bl,    d
div  bx
mov  rem+4, dx
mov  quo+4, ax

inc  ax
dec  dx
mov  bx,    ax
add  bx,    dx
mov  res+4, bx

mov  ax,  4C00h
int  21h
end start
END