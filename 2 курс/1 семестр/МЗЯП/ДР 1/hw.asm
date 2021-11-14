.model small
.stack 100h
.386
.data
buffer                db          5 dup(0)
matrix                db          5 dup(5 dup(0))
rows                  db          0
columns               db          0

s_rows                db          'Input number of rows (3-5): ', '$'
s_columns             db          'Input number of columns (3-5): ', '$'
s_inputMatrix         db          'Input matrix:', 10, 13, '$'
s_range               db          'a <= x[i] <= b', 10, 13, '$'
s_input_a             db          'Input a: ', '$'
s_input_b             db          'Input b: ', '$'
s_column              db          ' column: ', '$'
s_mean                db          ' line mean: ', '$'
s_positive            db          'First positive: ', '$'
s_menu                db          '1. Transpose matrix', 10, 13
                      db          '2. Numbers in the range', 10, 13
                      db          '3. Arithmetic mean', 10, 13
                      db          '4. Positive number', 10, 13
                      db          '0. Exit', 10, 13
                      db          '>>> ', '$'
s_error               db          'The matrix is not square', '$'

mSetColorMode     macro
   push              ax
   push              bx

   mov               ah,         10h
   mov               al,         3
   sub               bl,         bl
   int               10h

   pop               bx
   pop               ax
endm

mClearScreen      macro
   push              ax
   push              bx
   push              cx
   push              dx

   mov               ah,         6
   sub               al,         al
   mov               bh,         0F0h
   sub               cx,         cx
   mov               dx,         184Fh
   int               10h

   pop               dx
   pop               cx
   pop               bx
   pop               ax
endm

mClearPlace       macro       frsRow,   frsCol, lstRow,   lstCol
   push              ax
   push              bx
   push              cx
   push              dx

   mov               ah,         6
   sub               al,         al
   mov               bh,         0F0h
   mov               ch,         frsRow
   mov               cl,         frsCol
   mov               dh,         lstRow
   mov               dl,         lstCol
   int               10h

   pop               dx
   pop               cx
   pop               bx
   pop               ax
endm

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
   mov               bl,         0F0h
   mov               cx,         1
   int               10h

   pop               cx
   pop               bx
   pop               ax
endm

mMoveCursor      macro        row,      column
   push              ax
   push              bx
   push              dx

   mov               ah,         2
   mov               dh,         row
   mov               dl,         column
   sub               bh,         bh
   int               10h

   pop               dx
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
   sub               cx,         cx
   mov               cl,         rows

   JUMPS
   ROW:
      push              cx
      sub               si,         si
      sub               cx,         cx
      mov               cl,         columns

      COLUMN:
         mInput            buffer,     2
         mov               matrix[bx][si],   al
         inc               si
         mShiftCurcor      0,          3

         loop              COLUMN

      add               bl,         columns
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
   sub               cx,         cx
   mov               cl,         rows

   JUMPS
   ROW:
      push              cx
      sub               si,         si
      sub               cx,         cx
      mov               cl,         columns

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

      add               bl,         columns
      mNextLine

      pop               cx
      loop              ROW
   NOJUMPS

   pop               si
   pop               cx
   pop               bx
   pop               ax
endm

mTranspose        macro       matrix,   rows,   columns
   LOCAL             ROW
   LOCAL             COLUMN
   LOCAL             ONE_SPACE
   LOCAL             TWO_SPACES
   LOCAL             END_ROW
   
   push              ax
   push              bx
   push              cx
   push              si

   sub               si,         si
   sub               cx,         cx
   mov               cl,         columns

   COLUMN:
      push              cx
      sub               bx,         bx
      sub               cx,         cx
      mov               cl,         rows

      ROW:
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
            jmp               END_ROW

         ONE_SPACE:
            mIncCursor

         END_ROW:

         add               bl,         columns
         dec               cx
         cmp               cx,         0
         jg                ROW

      mNextLine
      inc               si
      pop               cx
      dec               cx
      cmp               cx,         0
      jg                COLUMN

   pop               si
   pop               cx
   pop               bx
   pop               ax
endm

mFindQuantity     macro       matrix,   rows,   columns
   LOCAL             ROW
   LOCAL             COLUMN
   LOCAL             CMP_B
   LOCAL             CMP_END
   LOCAL             INCREMENT
   
   push              ax
   push              bx
   push              cx
   push              dx
   push              si

   mPrintString      s_range
   mPrintString      s_input_a
   mInput            buffer,     2
   mov               dh,         al
   mNextLine
   mPrintString      s_input_b
   mInput            buffer,     2
   mov               dl,         al
   mNextLine
   mNextLine

   sub               si,         si
   sub               cx,         cx
   mov               cl,         columns

   COLUMN:
      push              cx
      sub               bx,         bx
      sub               ax,         ax
      sub               cx,         cx
      mov               cl,         rows

      ROW:
         cmp               dh,         matrix[bx][si]
         jle               CMP_B
         jmp               CMP_END

         CMP_B:
            cmp               matrix[bx][si], dl
            jle               INCREMENT
            jmp               CMP_END

            INCREMENT:
               inc               ax

         CMP_END:

         add               bl,         columns
         dec               cx
         cmp               cx,         0
         jg                ROW

      push              ax
      mov               ax,         si
      mOutput
      mPrintString      s_column
      pop               ax
      mOutput
      mNextLine

      inc               si
      pop               cx
      dec               cx
      cmp               cx,         0
      jg                COLUMN

   pop               si
   pop               dx
   pop               cx
   pop               bx
   pop               ax
endm

mFindMean         macro       matrix,   rows,   columns
   LOCAL             ROW
   LOCAL             COLUMN
   LOCAL             REMAINDER
   LOCAL             END_ROW
   
   push              ax
   push              bx
   push              cx
   push              dx
   push              si

   sub               bx,         bx
   mov               bl,         columns
   sub               cx,         cx
   mov               cl,         rows
   dec               cx

   ROW:
      push              cx
      sub               si,         si
      sub               ax,         ax
      sub               cx,         cx
      mov               cl,         columns

      COLUMN:
         mov               dl,         matrix[bx][si]
         xchg              ax,         dx
         cbw
         xchg              ax,         dx
         add               ax,         dx

         inc               si
         dec               cx
         cmp               cx,         0
         jg                COLUMN

      pop               cx
      push              ax
      sub               ax,         ax
      mov               al,         rows
      sub               al,         cl
      mOutput
      mPrintString      s_mean
      pop               ax

      mov               dl,         columns
      idiv              dl
      push              ax
      cbw
      mOutput
      pop               ax

      cmp               ah,         0
      jne               REMAINDER
      jmp               END_ROW

      REMAINDER:
         mIncCursor
         mov               al,         ah
         cbw
         mOutput
         mPrintSymbol      '/'
         mIncCursor
         sub               ax,         ax
         mov               al,         columns
         mOutput

      END_ROW:
      mNextLine

      add               bl,         columns
      dec               cx
      cmp               cx,         0
      jg                ROW

   pop               si
   pop               dx
   pop               cx
   pop               bx
   pop               ax
endm

mFindPlus         macro       matrix,   dimension
   LOCAL             ROW
   LOCAL             COLUMN
   LOCAL             FOUND
   LOCAL             END_MAC
   
   push              ax
   push              bx
   push              cx
   push              si

   mPrintString      s_positive

   sub               bx,         bx
   sub               cx,         cx
   mov               cl,         dimension

   ROW:
      push              cx
      sub               si,         si
      mov               ax,         cx
      mov               cl,         dimension
      sub               cx,         ax
      inc               cx

      COLUMN:
         cmp               byte ptr matrix[bx][si],   0
         jg                FOUND

         inc               si
         dec               cx
         cmp               cx,         0
         jg                COLUMN

      add               bl,         dimension
      pop               cx
      dec               cx
      cmp               cx,         0
      jg                ROW

   mPrintSymbol      '-'
   jmp               END_MAC

   FOUND:
      mov               al,         matrix[bx][si]
      cbw
      mOutput

   END_MAC:
   mNextLine

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

mSetColorMode
mClearScreen
mMoveCursor       0,          0

mPrintString      s_rows
mInput            buffer,     1
mov               rows,       al
mNextLine

mPrintString      s_columns
mInput            buffer,     1
mov               columns,    al
mNextLine

mPrintString      s_inputMatrix
mInputMatrix      matrix,     rows,      columns

mClearScreen
mMoveCursor       0,          0

mOutputMatrix     matrix,     rows,      columns
mNextLine
mPrintString      s_menu

mov               ah,         3
sub               bh,         bh
int               10h

CYCLE:
   mClearPlace       dh,         dl,       dh,     6
   mInput            buffer,     1
   inc               dh
   mClearPlace       dh,         0,        18h,    4FH
   dec               dh
   mNextLine
   mNextLine

   cmp               al,         1
   je                TASK_1
   cmp               al,         2
   je                TASK_2
   cmp               al,         3
   je                TASK_3
   cmp               al,         4
   je                TASK_4
   cmp               al,         0
   je                END_PROG
   jmp               CYCLE

   TASK_1:
      mTranspose        matrix,   rows, columns
      mMoveCursor       dh,       dl
      jmp               CYCLE

   TASK_2:
      mFindQuantity     matrix,   rows, columns
      mMoveCursor       dh,       dl
      jmp               CYCLE

   TASK_3:
      mFindMean         matrix,   rows, columns
      mMoveCursor       dh,       dl
      jmp               CYCLE

   TASK_4:
      mov               al,         rows
      cmp               al,         columns
      je                SQUARE
         mPrintString      s_error
         mMoveCursor       dh,       dl
         jmp               CYCLE

      SQUARE:
         mFindPlus         matrix,   rows
         mMoveCursor       dh,       dl
         jmp               CYCLE

END_PROG:
mov               ax,         4C00h
int               21h
end               start
END