.model small
.486
.stack 100h
.data
a     dw        1000
b     dw        -1
x     dw        1000
yQuo  dd        0
yRem  dw        0
temp  dd        0

.code
Start:
mov   ax,       @data
mov   ds,       ax
mov   ax,       0

mov   ax,       b
mov   dx,       3
imul  dx
cwde
mov   ebx,      eax
mov   eax,      0

mov   ax,       a
imul  a
mov   si,       offset temp
mov   [si],     ax
mov   [si] + 2, dx
movsx eax,      x
add   eax,      temp
mov   edx,      2
imul  edx
mov   ecx,      eax
mov   eax,      0
mov   edx,      0

mov   ax,       x
imul  x
mov   [si],     ax
mov   [si] + 2, dx
mov   eax,      temp
imul  ebx
mov   temp,     eax
mov   eax,      0
mov   edx,      0

mov   eax,      ecx
sub   eax,      temp
mov   ecx,      eax
mov   eax,      0

mov   ax,       bx
mov   ebx,      0
mov   bx,       2
imul  bx
cwde
mov   ebx,      eax
mov   eax,      0

mov   eax,      ecx
cdq
idiv  ebx

mov   yQuo,     eax
mov   yRem,     dx

mov   ax,       4C00h
int   21h
end start
END