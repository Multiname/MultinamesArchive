.model small
.stack 100h
.data
x     db     3
a     db     1

y     db     0
y1    db     0
y2    db     0

.code
Start:
mov   ax,    @data
mov   ds,    ax
mov   ax,    0

;проверка х на знак
cmp   x,     0
JL    Y_1_1
JMP   Y_1_2

Y_1_1:
;вычисление модуля х
mov   al,    x
mov   bl,    -1
imul  bl
mov   y1,    al
JMP   Y_1_END

Y_1_2:
;вычисление разности х и а
mov   al,    x
sub   al,    a
mov   y1,    al

Y_1_END:
;проверка остатка от деления х на 3
mov   al,    x
mov   bx,    3
idiv  bl
cmp   ah,    1
JE    Y_2_1
JMP   Y_2_2

Y_2_1:
;вычисление суммы а и х
mov   al,    x
add   al,    a
mov   y2,    al
JMP   Y_2_END

Y_2_2:
;приравнивание у2 7
mov   y2,    7

Y_2_END:
;вычисление разности у1 и у2
mov   al,    y1
sub   al,    y2
mov   y,     al

mov   ax,    4C00h
int   21h
end start
END