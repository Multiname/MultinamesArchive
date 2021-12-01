.586
.MODEL FLAT, C
.DATA
two dd 2.0
six dd 6.0

lowerBound dd 1.1
upperBound dd 5.1
nine       dd 9.0
fsttmp     dw 0

.CODE
calc proc C x:qword
finit
fld x               ; ST(0) = x
fld x               ; ST(0) = x, ST(1) = x
fmul ST(0), ST(1)   ; ST(0) = x^2, ST(1) = x
fmul ST(0), ST(1)   ; ST(0) = x^3, ST(1) = x
fmul ST(0), ST(1)   ; ST(0) = x^4, ST(1) = x

fld1                ; ST(0) = 1, ST(1) = x^4, ST(2) = x
fsub ST(1), ST(0)   ; ST(0) = 1, ST(1) = x^4 - 1, ST(2) = x

fxch ST(1)          ; ST(0) = x^4 - 1, ST(1) = 1, ST(2) = x
fsqrt               ; ST(0) = sqrt(x^4 - 1), ST(1) = 1, ST(2) = x

fld two             ; ST(0) = 2, ST(1) = sqrt(x^4 - 1), ST(2) = 1, ST(3) = x
fxch ST(1)          ; ST(0) = sqrt(x^4 - 1), ST(1) = 2, ST(2) = 1, ST(3) = x
fyl2x               ; ST(0) = 2 * log2(sqrt(x^4 - 1)), ST(1) = 1, ST(2) = x

fxch ST(2)          ; ST(0) = x, ST(1) = 1, ST(2) = 2 * log2(sqrt(x^4 - 1))
fsin                ; ST(0) = sin x, ST(1) = 1, ST(2) = 2 * log2(sqrt(x^4 - 1))

fldpi               ; ST(0) = pi, ST(1) = sin x, ST(2) = 1, ST(3) = 2 * log2(sqrt(x^4 - 1))
fld six             ; ST(0) = 6, ST(1) = pi, ST(2) = sin x, ST(3) = 1, ST(4) = 2 * log2(sqrt(x^4 - 1))
fdivr ST(0), ST(1)  ; ST(0) = pi / 6, ST(1) = pi, ST(2) = sin x, ST(3) = 1, ST(4) = 2 * log2(sqrt(x^4 - 1))

fadd ST(0), ST(2)   ; ST(0) = sin x + pi / 6, ST(1) = pi, ST(2) = sin x, ST(3) = 1, ST(4) = 2 * log2(sqrt(x^4 - 1))

fdivr ST(0), ST(1)  ; ST(0) = pi / (sin x + pi / 6), ST(1) = pi, ST(2) = sin x, ST(3) = 1, ST(4) = 2 * log2(sqrt(x^4 - 1))

fdivr ST(0), ST(4)  ; ST(0) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))

fld x               ; ST(0) = x, ST(1) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))
fld x               ; ST(0) = x, ST(1) = x, ST(2) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))
fmul ST(0), ST(1)   ; ST(0) = x^2, ST(1) = x, ST(2) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))

fsin                ; ST(0) = sin x^2, ST(1) = x, ST(2) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))

fsqrt               ; ST(0) = sqrt(sin x^2), ST(1) = x, ST(2) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))

fld1                ; ST(0) = 1, ST(1) = sqrt(sin x^2), ST(2) = x, ST(3) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))
fxch ST(1)          ; ST(0) = sqrt(sin x^2), ST(1) = 1, ST(2) = x, ST(3) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))
fyl2x               ; ST(0) = log2(sqrt(sin x^2)), ST(1) = x, ST(2) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))

fptan               ; ST(0) = 1, ST(1) = tg(log2(sqrt(sin x^2))), ST(2) = x, ST(3) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))

fxch ST(1)          ; ST(0) = tg(log2(sqrt(sin x^2))), ST(1) = 1, ST(2) = x, ST(3) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))
fst  ST(1)          ; ST(0) = tg(log2(sqrt(sin x^2))), ST(1) = tg(log2(sqrt(sin x^2))), ST(2) = x, ST(3) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))
fmul ST(1), ST(0)   ; ST(0) = tg(log2(sqrt(sin x^2))), ST(1) = tg^2(log2(sqrt(sin x^2))), ST(2) = x, ST(3) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6))

fxch ST(3)          ; ST(0) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6)), ST(1) = tg^2(log2(sqrt(sin x^2))), ST(2) = x, ST(3) = tg(log2(sqrt(sin x^2)))
fsub ST(0), ST(1)   ; ST(0) = 2 * log2(sqrt(x^4 - 1)) / (pi / (sin x + pi / 6)) - tg^2(log2(sqrt(sin x^2)))

ret
calc ENDP

compare proc C x:qword
finit
fld lowerBound      ; ST(0) = 1.1
fld x               ; ST(0) = x, ST(1) = 1.1
fcom
fstsw ax
sahf
jb CASE_1

fld upperBound      ; ST(0) = 5.1, ST(1) = x
fcom
fstsw ax
sahf
jae CASE_2

fld nine            ; ST(0) = 9, ST(1) = 5.1, ST(2) = x
fmul ST(0), ST(2)   ; ST(0) = 9x, ST(1) = 5.1, ST(2) = x
fmul ST(0), ST(2)   ; ST(0) = 9x^2
fld nine            ; ST(0) = 9, ST(1) = 9x^2
fadd ST(0), ST(1)   ; ST(0) = 9x^2 + 9
jmp CASE_END

CASE_2:
fxch ST(1)          ; ST(0) = x, ST(1) = 5.1
fnstcw fsttmp
or [fsttmp], 0C00h
fldcw fsttmp
frndint             ; ST(0) = цел(x)

fld x               ; ST(0) = x, ST(1) = цел(x)
fsub ST(0), ST(1)   ; ST(0) = ост(x), ST(1) = цел(x)
f2xm1               ; ST(0) = 2^ост(x) - 1, ST(1) = цел(x)
fxch ST(1)          ; ST(0) = цел(x), ST(1) = 2^ост(x) - 1
fld1                ; ST(0) = 1, ST(1) = цел(x), ST(2) = 2^ост(x) - 1
fadd ST(2), ST(0)   ; ST(0) = 1, ST(1) = цел(x), ST(2) = 2^ост(x)
fxch ST(2)          ; ST(0) = 2^ост(x), ST(1) = цел(x), ST(2) = 1

fscale              ; ST(0) = 2^x, ST(1) = цел(x), ST(2) = 1
fsub ST(0), ST(2)   ; ST(0) = 2^x - 1

jmp CASE_END

CASE_1:
fsincos             ; ST(0) = cos x, ST(1) = sin x
fadd ST(0), ST(1)   ; ST(0) = sin x + cos x

CASE_END:
ret
compare ENDP
END