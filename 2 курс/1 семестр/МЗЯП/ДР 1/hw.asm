.model small
.stack 100h
.data
buffer                db          5 dup(0)
baseMatrix            db          5 dup(5 dup(0))
ResultMatrix          db          5 dup(5 dup(0))

matrixInput           db          'Input matrix:', 10, 13, '$'

mPrintString      macro       string
   push              ax
   push              dx

   mov               ah,         09h
   mov               dx,         offset string
   int               21h

   pop               dx
   pop               ax
endm

mPrintSymbol      macro       symbol
   push              ax
   push              bx
   push              cx

   mov               ah,         9
   mov               al,         symbol
   mov               bl,         0Fh
   mov               cx,         1
   int               10h

   pop               cx
   pop               bx
   pop               ax
endm

mShiftCurcor     macro        row,      column
   push              ax
   push              bx
   push              cx
   push              dx

   mov               ah,         3
   sub               bh,         bh
   int               10h

   add               dh,         row
   add               dl,         column
   mov               ah,         2
   int               10h

   pop               dx
   pop               cx
   pop               bx
   pop               ax
endm

mIncCursor       macro
   push              ax
   push              bx
   push              cx
   push              dx

   mov               ah,         3
   sub               bh,         bh
   int               10h

   inc               dl
   mov               ah,         2
   int               10h

   pop               dx
   pop               cx
   pop               bx
   pop               ax
endm

mNextLine        macro
   push              ax
   push              bx
   push              cx
   push              dx

   mov               ah,         3
   sub               bh,         bh
   int               10h

   inc               dh
   mov               dl,         0
   mov               ah,         2
   int               10h

   pop               dx
   pop               cx
   pop               bx
   pop               ax
endm

mInput            macro       buffer,   size
   LOCAL             NEGATIVE
   LOCAL             POSITIVE
   LOCAL             CALCULATION
   LOCAL             POWER
   LOCAL             CYCLE
   LOCAL             END_CALCULATION
   LOCAL             END_INPUT

   push              bx
   push              cx
   push              dx
   push              si

   mov               ah,         3
   mov               bh,         0
   int               10h
   push              dx

   mov               buffer,     size
   inc               buffer
   mov               ah,         0Ah
   lea               dx,         buffer
   int               21h

   pop               dx
   mov               ah,         2
   int               10h

   sub               ax,         ax
   cmp               buffer+1,   0
   je                END_INPUT

   mov               ax,         1
   sub               dx,         dx
   mov               dl,         buffer+1
   dec               dx
   mov               bx,         10

   cmp               buffer+2,   '-'
   je                NEGATIVE
   jmp               POSITIVE

   NEGATIVE:
      push              -1
      mov               si,         3
      dec               dx
      jmp               POWER

   POSITIVE:
      push              1
      mov               si,         2

   POWER:
      cmp               dx,         0
      jle               CALCULATION

      mul               bl
      dec               dx

      jmp               POWER

   CALCULATION:
      mov               cx,         ax
      sub               bx,         bx

      CYCLE:
         sub               ax,         ax
         mov               al,         buffer[si]
         sub               al,         30h
         mul               cx
         add               bx,         ax

         mov               ax,         cx
         mov               cx,         10
         div               cx
         mov               cx,         ax

         inc               si

         mov               dx,         si
         sub               dl,         buffer+1
         
         cmp               dl,         2
         je                END_CALCULATION
         jmp               CYCLE

   END_CALCULATION:
      pop               dx
      mov               ax,         bx
      imul              dx

   END_INPUT:
   pop               si
   pop               dx
   pop               cx
   pop               bx
endm

mOutput           macro
   LOCAL             NEGATIVE
   LOCAL             SPLIT
   LOCAL             OUTPUT
   
   push              dx
   push              si
   push              di

   mov               si,         10
   sub               di,         di

   cmp               ax,         0
   jl                NEGATIVE
   jmp               SPLIT

   NEGATIVE:
      neg               ax
      push              ax

      mPrintSymbol      '-'
      mIncCursor

      pop               ax

   SPLIT:
      inc               di
      sub               dx,         dx
      div               si
      add               dx,         30h
      push              dx
      
      cmp               ax,         0
      jg                SPLIT

   OUTPUT:
      pop               ax
      mPrintSymbol      al
      mIncCursor

      dec               di
      cmp               di,         0
      jg                OUTPUT

   pop               di
   pop               si
   pop               dx
endm

mInputMatrix      macro       matrix,   rows,   columns
   LOCAL             ROW
   LOCAL             COLUMN
   
   push              ax
   push              bx
   push              cx
   push              si

   sub               bx,         bx
   mov               cx,         rows

   JUMPS
   ROW:
      push              cx
      sub               si,         si
      mov               cx,         columns

      COLUMN:
         mInput            buffer,     2
         mov               matrix[bx][si],   al
         inc               si
         mShiftCurcor      0,          3

         loop              COLUMN

      add               bx,         columns
      mNextLine

      pop               cx
      loop              ROW
   NOJUMPS

   pop               si
   pop               cx
   pop               bx
   pop               ax
endm

mOutputMatrix     macro       matrix,   rows,   columns
   LOCAL             ROW
   LOCAL             COLUMN
   LOCAL             ONE_SPACE
   LOCAL             TWO_SPACES
   LOCAL             END_COLUMN
   
   push              ax
   push              bx
   push              cx
   push              si

   sub               bx,         bx
   mov               cx,         rows

   JUMPS
   ROW:
      push              cx
      sub               si,         si
      mov               cx,         columns

      COLUMN:
         sub               ax,         ax
         mov               al,         matrix[bx][si]
         cbw
         mOutput

         sub               ax,         ax
         mov               al,         matrix[bx][si]
         cmp               ax,         10
         jl                TWO_SPACES
         jmp               ONE_SPACE

         TWO_SPACES:
            mShiftCurcor      0,          2
            jmp               END_COLUMN

         ONE_SPACE:
            mIncCursor

         END_COLUMN:
         inc               si
         loop              COLUMN

      add               bx,         columns
      mNextLine

      pop               cx
      loop              ROW
   NOJUMPS

   pop               si
   pop               cx
   pop               bx
   pop               ax
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

mInputMatrix      baseMatrix,   3,      3
mOutputMatrix     baseMatrix,   3,      3

mov               ax,         4C00h
int               21h
end               start
END