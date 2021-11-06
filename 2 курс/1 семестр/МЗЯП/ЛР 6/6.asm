.model small
.386
.stack 100h
.data
buffer            db          7 dup(0)
number            dw          0
N                 db          0
K                 db          0
C                 dw          0
D                 dw          0
inputN            db          'N: ', '$'
inputK            db          'K: ', '$'
inputC            db          'C: ', '$'
inputD            db          'D: ', '$'
inputNumber       db          '>>> ', '$'
result            db          'Result: ', '$'
sum               dw          0

mPrint             macro       string
   mov               ah,         09h
   mov               dx,         offset string
   int               21h
endm

mMoveCursor       macro       row,      column
   mov               ah,         2
   mov               dh,         row
   mov               dl,         column
   mov               bh,         0
   int               10h
endm

mIncCursor       macro
   mov               ah,         3
   mov               bh,         0
   int               10h

   inc               dl
   mov               ah,         2
   int               10h
endm

mNextLine        macro
   mov               ah,         3
   mov               bh,         0
   int               10h

   inc               dh
   mov               ah,         2
   int               10h
endm

mInput            macro       buffer,   size
   LOCAL             INPUT_ONE_DIGIT
   LOCAL             INPUT_TWO_DIGIT
   LOCAL             INPUT_THREE_DIGIT
   LOCAL             INPUT_FOUR_DIGIT
   LOCAL             END_INPUT

   mov               buffer,     size
   inc               buffer
   mov               ah,         0Ah
   lea               dx,         buffer
   int               21h

   mov               ax,         0
   cmp               buffer+1,   1
   je                INPUT_ONE_DIGIT
   cmp               buffer+1,   2
   je                INPUT_TWO_DIGIT
   cmp               buffer+1,   3
   je                INPUT_THREE_DIGIT
   cmp               buffer+1,   4
   je                INPUT_FOUR_DIGIT
   jmp               END_INPUT

   INPUT_ONE_DIGIT:
      mInputOneDigit    buffer
      jmp               END_INPUT

   INPUT_TWO_DIGIT:
      mInputTwoDigit    buffer
      jmp               END_INPUT

   INPUT_THREE_DIGIT:
      mInputThreeDigit  buffer
      jmp               END_INPUT

   INPUT_FOUR_DIGIT:
      mInputFourDigit   buffer

   END_INPUT:
endm

mInputOneDigit    macro       buffer
   mov               al,         buffer+2
   sub               al,         30h
endm

mInputTwoDigit    macro       buffer
   mov               al,         buffer+2
   sub               al,         30h
   mov               bl,         10
   mul               bl

   add               al,         buffer+3
   sub               al,         30h
endm

mInputThreeDigit  macro       buffer
   mov               al,         buffer+2
   sub               al,         30h
   mov               bl,         100
   mul               bl

   mov               bl,         buffer+3
   sub               bl,         30h
   xchg              ax,         bx
   mov               cl,         10
   mul               cl
   add               bx,         ax
   
   mov               ax,         0
   mov               al,         buffer+4
   sub               al,         30h
   add               bx,         ax
   xchg              ax,         bx
endm

mInputFourDigit   macro       buffer
   mov               al,         buffer+2
   sub               al,         30h
   mov               bx,         1000
   mul               bx

   mov               bl,         buffer+3
   sub               bl,         30h
   xchg              ax,         bx
   mov               cl,         100
   mul               cl
   add               bx,         ax
   
   mov               ax,         0
   mov               al,         buffer+4
   sub               al,         30h
   mov               cl,         10
   mul               cl
   add               bx,         ax

   mov               al,         buffer+5
   sub               al,         30h
   add               bx,         ax
   xchg              ax,         bx
endm

mOutput           macro       number
   LOCAL             OUTPUT_ONE_DIGIT
   LOCAL             OUTPUT_TWO_DIGIT
   LOCAL             OUTPUT_THREE_DIGIT
   LOCAL             OUTPUT_FOUR_DIGIT
   LOCAL             END_OUTPUT

   cmp               number,     10
   jl                OUTPUT_ONE_DIGIT
   cmp               number,     100
   jl                OUTPUT_TWO_DIGIT
   cmp               number,     1000
   jl                OUTPUT_THREE_DIGIT
   cmp               number,     10000
   jl                OUTPUT_FOUR_DIGIT
   jmp               END_OUTPUT

   OUTPUT_ONE_DIGIT:
      mOutputOneDigit   number
      jmp               END_OUTPUT

   OUTPUT_TWO_DIGIT:
      mOutputTwoDigit   number
      jmp               END_OUTPUT

   OUTPUT_THREE_DIGIT:
      mOutputThreeDigit number
      jmp               END_OUTPUT

   OUTPUT_FOUR_DIGIT:
      mOutputFourDigit  number

   END_OUTPUT:
      mIncCursor
endm

mOutputOneDigit   macro       number
   mov               ax,         number
   mov               ah,         9
   add               al,         30h
   mov               bl,         0Fh
   mov               cx,         1
   int               10h
endm

mOutputTwoDigit   macro       number
   mov               ax,         number
   mov               bx,         10
   div               bl
   push              ax
   add               al,         30h

   mov               ah,         9
   mov               bl,         0Fh
   mov               cx,         1
   int               10h

   mIncCursor

   pop               ax
   mov               al,         ah
   add               al,         30h

   mov               ah,         9
   mov               bl,         0Fh
   mov               cx,         1
   int               10h
endm

mOutputThreeDigit macro       number
   mov               ax,         number
   mov               bx,         10
   div               bl
   push              ax
   mov               ah,         0
   div               bl
   push              ax
   add               al,         30h

   mov               ah,         9
   mov               bl,         0Fh
   mov               cx,         1
   int               10h

   mIncCursor

   pop               ax
   mov               al,         ah
   add               al,         30h

   mov               ah,         9
   mov               bl,         0Fh
   mov               cx,         1
   int               10h

   mIncCursor

   pop               ax
   mov               al,         ah
   add               al,         30h

   mov               ah,         9
   mov               bl,         0Fh
   mov               cx,         1
   int               10h
endm

mOutputFourDigit  macro       number
   mov               ax,         number
   mov               bx,         10
   mov               dx,         0
   div               bx
   push              dx
   div               bl
   push              ax
   mov               ah,         0
   div               bl
   push              ax
   add               al,         30h

   mov               ah,         9
   mov               bl,         0Fh
   mov               cx,         1
   int               10h

   mIncCursor

   pop               ax
   mov               al,         ah
   add               al,         30h

   mov               ah,         9
   mov               bl,         0Fh
   mov               cx,         1
   int               10h

   mIncCursor

   pop               ax
   mov               al,         ah
   add               al,         30h

   mov               ah,         9
   mov               bl,         0Fh
   mov               cx,         1
   int               10h

   mIncCursor

   pop               ax
   add               al,         30h

   mov               ah,         9
   mov               bl,         0Fh
   mov               cx,         1
   int               10h
endm

.code
Start:
mov               ax,         @data
mov               ds,         ax
sub               ax,         ax

mov               ax,         600h
mov               bh,         7
mov               cx,         0
mov               dx,         184Fh
int               10h

mov               ah,         2
mov               dh,         0
mov               dl,         0
mov               bh,         0
int               10h

mPrint            inputN
mInput            buffer,     1
mov               N,          al
mNextLine

mPrint            inputK
mInput            buffer,     1
mov               K,          al
mNextLine

mPrint            inputC
mInput            buffer,     4
mov               C,          ax
mNextLine

mPrint            inputD
mInput            buffer,     4
mov               D,          ax
mNextLine

CYCLE:
   mPrint            inputNumber
   mInput            buffer,     4

   cmp               K,          0
   jg                CONDITION_1
   jmp               END_CYCLE

   CONDITION_1:
      cmp               C,          ax
      jle               CONDITION_2
      jmp               END_CYCLE
   
      CONDITION_2:
         cmp               ax,         D
         jle               ADDITION
         jmp               END_CYCLE

         ADDITION:
            add               sum,        ax
            dec               K

   END_CYCLE:
      dec               N
      mNextLine
      cmp               N,        0
      jg                CYCLE

mPrint            result
mOutput           sum

mov              ax,         4C00h
int               21h
end               start
END