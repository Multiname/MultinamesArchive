.486
model use16 small
.stack 100h
.data
VIDEOR DB ?
old_data dd 0
exit_code db 0
workCode db 0
currentX dd -200

x dd 0.0
y dw 0

two dd 2.0
three dd 3.0
threeFifths dd 0.6
hundred dd 100.0

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

	fdivr ST(0), ST(4)    ; ST(0) = y

	fld hundred           ; ST(0) = 100,                                  ST(1) = y
	fmul ST(0), ST(1)     ; ST(0) = 100y
	fnstcw fsttmp
	and [fsttmp], 0F3FFh
	fldcw fsttmp
	frndint

	fist y
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
	fadd ST(0), ST(5)     ; ST(0) = y

	fld hundred           ; ST(0) = 100,                       ST(1) = y
	fmul ST(0), ST(1)     ; ST(0) = 100y
	fnstcw fsttmp
	and [fsttmp], 0F3FFh
	fldcw fsttmp
	frndint

	fist y
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

	fscale                ; ST(0) = y

	fld hundred           ; ST(0) = 100,                          ST(1) = y
	fmul ST(0), ST(1)     ; ST(0) = 100y
	fnstcw fsttmp
	and [fsttmp], 0F3FFh
	fldcw fsttmp
	frndint

	fist y
endm

mMovX macro num
	finit
	fld hundred
	fidivr num
	fst x
endm

mDrawMinus macro x, y
	mov cx, x
	mov dx, y
	int 10h
	dec cx
	int 10h
	dec cx
	int 10h
endm

mDrawZero macro x, y
	mov cx, x
	mov dx, y
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
endm

mDrawOne macro x, y
	mov cx, x
	mov dx, y
	int 10h
	inc dx
	int 10h
	inc dx
	int 10h
	inc dx
	int 10h
	inc dx
	int 10h
endm

mDrawTwo macro x, y
	mov cx, x
	mov dx, y
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
endm

mDrawFive macro x, y
	mov cx, x
	mov dx, y
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
endm

Start:
jmp PROG_START

HANDLE:
	cmp workCode, 1
	jne HANDLE_END

	cmp currentX, -99
	jl FIRST_FUNC
	cmp currentX, 0
	jl SECOND_FUNC
	cmp currentX, 101
	jl THIRD_FUNC
	jmp END_PROG

	FIRST_FUNC:
		mMovX currentX
		mFirstFunc

		mov dx, 260
		sub dx, y
		mov cx, word ptr currentX
		add cx, 210
		mov ax, 0C01h
		int 10h

		inc currentX
		jmp HANDLE_END

	SECOND_FUNC:
		mMovX currentX
		mSecondFunc

		mov dx, 260
		sub dx, y
		mov cx, word ptr currentX
		add cx, 210
		mov ax, 0C04h
		int 10h

		inc currentX
		jmp HANDLE_END

	THIRD_FUNC:
		mMovX currentX
		mThirdFunc

		mov dx, 260
		sub dx, y
		mov cx, word ptr currentX
		add cx, 210
		mov ax, 0C02h
		int 10h

		inc currentX
		jmp HANDLE_END

	END_PROG:
		mov exit_code, 1

	HANDLE_END:
	jmp cs:old_data
	iret

PROG_START:
mov ax, @data
mov ds, ax

MOV AH, 0Fh
INT 10h
MOV VIDEOR, AL

MOV AX, 0013h
INT 10h 

PUSH 0A000h
POP ES

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

mDrawMinus 9, 195
mDrawTwo 11, 193
mDrawMinus 110, 195
mDrawOne 112, 193
mDrawZero 209, 193
mDrawOne 310, 193
mDrawOne 201, 158
mDrawTwo 205, 58
mDrawTwo 199, 8
mDrawFive 207, 8

mov cx, 203
mov dx, 12
int 10h

xor ax, ax
mov es, ax
mov ah, 35h
mov al, 1Ch
int 21h
mov word ptr old_data, bx
mov word ptr old_data + 2, es
xor ax, ax
mov es, ax

push ds
push dx
mov dx, offset HANDLE
mov ax, seg HANDLE
mov ds, ax
mov ah, 25h 
mov al, 1Ch
int 21h
pop dx
pop ds

mov workCode, 1
CYCLE:
	mov cl, exit_code
	cmp cl, 1
	jne CYCLE

push ds
mov dx, word ptr old_data
mov ax, word ptr old_data + 2
mov ds, ax
mov ah, 25h 
mov al, 1Ch
int 21h
pop ds

XOR AX, AX
INT 16h 

MOV AH, 0
MOV AL, VIDEOR
INT 10h

mov ax, 4c00h
int 21h
end Start
end