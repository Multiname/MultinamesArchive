.486
model use16 small
.stack 100h
.data

VIDEOR DB ?
x dd 0.0
two dd 2.0
three dd 3.0
threeFifths dd 0.6
fsttmp dw 0

.code 
mFirstFunc macro
	finit
	fld x                 ; ST(0) = x
	fabs                  ; ST(0) = |x|
	fld1                  ; ST(0) = 1,                                    ST(1) = |x|
	fadd ST(1), ST(0)     ; ST(0) = 1,                                    ST(1) = 1 + |x|

	fld x                 ; ST(0) = x,                                    ST(1) = 1,                              ST(2) = 1 + |x|
	fld x                 ; ST(0) = x,                                    ST(1) = x,                              ST(2) = 1,                                   ST(3) = 1 + |x|
	fmul ST(0), ST(1)     ; ST(0) = x^2,                                  ST(1) = x,                              ST(2) = 1,                                   ST(3) = 1 + |x|
	fadd ST(0), ST(1)     ; ST(0) = x + x^2,                              ST(1) = x,                              ST(2) = 1,                                   ST(3) = 1 + |x|
	fadd ST(0), ST(2)     ; ST(0) = 1 + x + x^2,                          ST(1) = x,                              ST(2) = 1,                                   ST(3) = 1 + |x|

	fld three             ; ST(0) = 3,                                    ST(1) = 1 + x + x^2,                    ST(2) = x,                                   ST(3) = 1,                                   ST(4) = 1 + |x|
	fdivr ST(0), ST(3)    ; ST(0) = 1/3,                                  ST(1) = 1 + x + x^2,                    ST(2) = x,                                   ST(3) = 1,                                   ST(4) = 1 + |x|
	fxch ST(1)            ; ST(0) = 1 + x + x^2,                          ST(1) = 1/3,                            ST(2) = x,                                   ST(3) = 1,                                   ST(4) = 1 + |x|
	fyl2x                 ; ST(0) = log2(1 + x + x^2)^1/3,                ST(1) = x,                              ST(2) = 1,                                   ST(3) = 1 + |x|
	fmul ST(2), ST(0)     ; ST(0) = log2(1 + x + x^2)^1/3,                ST(1) = x,                              ST(2) = log2(1 + x + x^2)^1/3,               ST(3) = 1 + |x|

	fnstcw fsttmp
	or [fsttmp], 0C00h
	fldcw fsttmp
	frndint               ; ST(0) = цел(log2(1 + x + x^2)^1/3),           ST(1) = x,                              ST(2) = log2(1 + x + x^2)^1/3,               ST(3) = 1 + |x|

	fsub ST(2), ST(0)     ; ST(0) = цел(log2(1 + x + x^2)^1/3),           ST(1) = x,                              ST(2) = ост(log2(1 + x + x^2)^1/3),          ST(3) = 1 + |x|
	fxch ST(2)            ; ST(0) = ост(log2(1 + x + x^2)^1/3),           ST(1) = x,                              ST(2) = цел(log2(1 + x + x^2)^1/3),          ST(3) = 1 + |x|
	f2xm1                 ; ST(0) = 2^ост(log2(1 + x + x^2)^1/3) - 1,     ST(1) = x,                              ST(2) = цел(log2(1 + x + x^2)^1/3),          ST(3) = 1 + |x|
	fxch ST(2)            ; ST(0) = цел(log2(1 + x + x^2)^1/3),           ST(1) = x,                              ST(2) = 2^ост(log2(1 + x + x^2)^1/3) - 1,    ST(3) = 1 + |x|
	fld1                  ; ST(0) = 1,                                    ST(1) = цел(log2(1 + x + x^2)^1/3),     ST(2) = x,                                   ST(3) = 2^ост(log2(1 + x + x^2)^1/3) - 1,    ST(4) = 1 + |x|
	fadd ST(0), ST(3)     ; ST(0) = 2^ост(log2(1 + x + x^2)^1/3),         ST(1) = цел(log2(1 + x + x^2)^1/3),     ST(2) = x,                                   ST(3) = 2^ост(log2(1 + x + x^2)^1/3) - 1,    ST(4) = 1 + |x|

	fscale                ; ST(0) = (1 + x + x^2)^1/3,                    ST(1) = цел(log2(1 + x + x^2)^1/3),     ST(2) = x,                                   ST(3) = 2^ост(log2(1 + x + x^2)^1/3) - 1,    ST(4) = 1 + |x|

	fdivr ST(0), ST(4)
endm

mSecondFunc macro
	finit
	fld x                 ; ST(0) = x
	fld x                 ; ST(0) = x,                         ST(1) = x
	fmul ST(0), ST(1)     ; ST(0) = x^2,                       ST(1) = x
	fld1                  ; ST(0) = 1,                         ST(1) = x^2,           ST(2) = x
	fadd ST(1), ST(0)     ; ST(0) = 1,                         ST(1) = x^2 + 1,       ST(2) = x
	fxch ST(1)            ; ST(0) = x^2 + 1,                   ST(1) = 1,             ST(2) = x

	fldln2                ; ST(0) = ln 2,                      ST(1) = x^2 + 1,       ST(2) = 1,              ST(3) = x
	fxch ST(1)            ; ST(0) = x^2 + 1,                   ST(1) = ln 2,          ST(2) = 1,              ST(3) = x
	fyl2x                 ; ST(0) = ln(x^2 + 1),               ST(1) = 1,             ST(2) = x

	fxch ST(2)            ; ST(0) = x,                         ST(1) = 1,             ST(2) = ln(x^2 + 1)
	fcos                  ; ST(0) = cos x,                     ST(1) = 1,             ST(2) = ln(x^2 + 1)
	fmul ST(1), ST(0)     ; ST(0) = cos x,                     ST(1) = cos x,         ST(2) = ln(x^2 + 1)
	fmul ST(1), ST(0)     ; ST(0) = cos x,                     ST(1) = cos^2 x,       ST(2) = ln(x^2 + 1)
	fmul ST(1), ST(0)     ; ST(0) = cos x,                     ST(1) = cos^3 x,       ST(2) = ln(x^2 + 1)
	fmul ST(1), ST(0)     ; ST(0) = cos x,                     ST(1) = cos^4 x,       ST(2) = ln(x^2 + 1)
	
	fld1                  ; ST(0) = 1,                         ST(1) = cos x,         ST(2) = cos^4 x,        ST(3) = ln(x^2 + 1)
	fadd ST(0), ST(2)     ; ST(0) = 1 + cos^4 x,               ST(1) = cos x,         ST(2) = cos^4 x,        ST(3) = ln(x^2 + 1)

	fld x                 ; ST(0) = x,                         ST(1) = 1 + cos^4 x,   ST(2) = cos x,          ST(3) = cos^4 x,        ST(4) = ln(x^2 + 1)
	fld two               ; ST(0) = 2,                         ST(1) = x,             ST(2) = 1 + cos^4 x,    ST(3) = cos x,          ST(4) = cos^4 x,        ST(5) = ln(x^2 + 1)
	fmul ST(5), ST(0)     ; ST(0) = 2,                         ST(1) = x,             ST(2) = 1 + cos^4 x,    ST(3) = cos x,          ST(4) = cos^4 x,        ST(5) = 2 ln(x^2 + 1)
	fadd ST(0), ST(1)     ; ST(0) = 2 + x,                     ST(1) = x,             ST(2) = 1 + cos^4 x,    ST(3) = cos x,          ST(4) = cos^4 x,        ST(5) = 2 ln(x^2 + 1)

	fdivr ST(0), ST(2)    ; ST(0) = (1 + cos^4 x) / (2 + x),   ST(1) = x,             ST(2) = 1 + cos^4 x,    ST(3) = cos x,          ST(4) = cos^4 x,        ST(5) = 2 ln(x^2 + 1)
	fadd ST(0), ST(5)
endm

mThirdFunc macro
	fld1                  ; ST(0) = 1
	fld x                 ; ST(0) = x,                            ST(1) = 1
	fadd ST(0), ST(1)     ; ST(0) = x + 1,                        ST(1) = 1

	fld threeFifths       ; ST(0) = 3/5,                          ST(1) = x + 1
	fxch ST(1)            ; ST(0) = x + 1,                        ST(1) = 3/5
	fyl2x                 ; ST(0) = log2(x + 1)^3/5
	fld1                  ; ST(0) = 1,                            ST(1) = log2(x + 1)^3/5
	fmul ST(0), ST(1)     ; ST(0) = log2(x + 1)^3/5,              ST(1) = log2(x + 1)^3/5

	fnstcw fsttmp
	or [fsttmp], 0C00h
	fldcw fsttmp
	frndint               ; ST(0) = цел(log2(x + 1)^3/5),         ST(1) = log2(x + 1)^3/5

	fsub ST(1), ST(0)     ; ST(0) = цел(log2(x + 1)^3/5),         ST(1) = ост(log2(x + 1)^3/5)
	fxch ST(1)            ; ST(0) = ост(log2(x + 1)^3/5),         ST(1) = цел(log2(x + 1)^3/5)
	f2xm1                 ; ST(0) = 2^ост(log2(x + 1)^3/5) - 1,   ST(1) = цел(log2(x + 1)^3/5)
	fxch ST(1)            ; ST(0) = цел(log2(x + 1)^3/5),         ST(1) = 2^ост(log2(x + 1)^3/5) - 1
	fld1                  ; ST(0) = 1,                            ST(1) = цел(log2(x + 1)^3/5),         ST(2) = 2^ост(log2(x + 1)^3/5) - 1
	fadd ST(0), ST(2)     ; ST(0) = 2^ост(log2(x + 1)^3/5),       ST(1) = цел(log2(x + 1)^3/5),         ST(2) = 2^ост(log2(x + 1)^3/5) - 1

	fscale
endm

Start:
mov ax, @data
mov ds, ax

MOV AH,0Fh ;запомнить текущий видеорежим 
INT 10h
MOV VIDEOR,AL ;видеорежим в переменную videor 

MOV AX, 0013h ;установить видеорежим 13h 
INT 10h 

PUSH 0A000h ;установить регистр ES на сегмент 
POP ES ;видеопамяти 

mov cx, 64000
FILL:
	dec cx
	mov di, cx
	MOV byte ptr ES:[DI], 15
	cmp cx, 0
	jne FILL

mov ah, 0Ch
xor al, al
xor bx, bx
mov cx, 10
mov dx, 190
OX:
	int 10h
	inc cx
	cmp cx, 311
	jne OX

mov cx, 210
mov dx, 10
OY:
	int 10h
	inc dx
	cmp dx, 189
	jne OY

mov cx, 10
mov dx, 189
OX_STREAKS:
	int 10h
	add dx, 2
	int 10h

	mov dx, 189
	add cx, 100

	cmp cx, 410
	jne OX_STREAKS

mov cx, 209
mov dx, 10
int 10h
add cx, 2
int 10h

mov cx, 209
mov dx, 60
int 10h
add cx, 2
int 10h

mov cx, 209
mov dx, 160
int 10h
add cx, 2
int 10h

mov cx, 9
mov dx, 195
int 10h
dec cx
int 10h
dec cx
int 10h

mov cx, 11
mov dx, 193
int 10h
inc cx
int 10h
inc cx
int 10h
inc dx
int 10h
inc dx
int 10h
dec cx
int 10h
dec cx
int 10h
inc dx
int 10h
inc dx
int 10h
inc cx
int 10h
inc cx
int 10h

mov cx, 110
mov dx, 195
int 10h
dec cx
int 10h
dec cx
int 10h

mov cx, 112
mov dx, 193
int 10h
inc dx
int 10h
inc dx
int 10h
inc dx
int 10h
inc dx
int 10h

mov cx, 209
mov dx, 193
int 10h
inc cx
int 10h
inc cx
int 10h
inc dx
int 10h
inc dx
int 10h
inc dx
int 10h
inc dx
int 10h
dec cx
int 10h
dec cx
int 10h
dec dx
int 10h
dec dx
int 10h
dec dx
int 10h

mov cx, 310
mov dx, 193
int 10h
inc dx
int 10h
inc dx
int 10h
inc dx
int 10h
inc dx
int 10h

mov cx, 207
mov dx, 158
int 10h
inc dx
int 10h
inc dx
int 10h
inc dx
int 10h
inc dx
int 10h

mov cx, 205
mov dx, 58
int 10h
inc cx
int 10h
inc cx
int 10h
inc dx
int 10h
inc dx
int 10h
dec cx
int 10h
dec cx
int 10h
inc dx
int 10h
inc dx
int 10h
inc cx
int 10h
inc cx
int 10h

mov cx, 199
mov dx, 8
int 10h
inc cx
int 10h
inc cx
int 10h
inc dx
int 10h
inc dx
int 10h
dec cx
int 10h
dec cx
int 10h
inc dx
int 10h
inc dx
int 10h
inc cx
int 10h
inc cx
int 10h

mov cx, 203
mov dx, 12
int 10h

mov cx, 207
mov dx, 8
int 10h
dec cx
int 10h
dec cx
int 10h
inc dx
int 10h
inc dx
int 10h
inc cx
int 10h
inc cx
int 10h
inc dx
int 10h
inc dx
int 10h
dec cx
int 10h
dec cx
int 10h

XOR AX,AX ;ожидание нажатия любой клавиши 
INT 16h 

MOV AH,0 ;восстановление видеорежима 
MOV AL,VIDEOR
INT 10h

mov ax, 4c00h
int 21h
end Start
end