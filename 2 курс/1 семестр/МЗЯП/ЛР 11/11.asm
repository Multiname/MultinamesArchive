.MODEL SMALL
.STACK 100h
.386
.DATA
    old_data    dd  0
    exit_code   db  0
    line_1 db 'It is a dark time for the Rebellion.', '$'
    line_2 db 'Although the Death Star has been', '$'
    line_3 db 'destroyed, Imperial troops have driven', '$'
    line_4 db 'the Rebel forces from their hidden base', '$'
    line_5 db 'and pursued them across the galaxy', '$'

.CODE
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
   mov               bh,         14
   sub               cx,         cx
   mov               dx,         184Fh
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
   lea               dx,         string
   int               21h

   pop               dx
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

mShiftCursor     macro        row,      column
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

mPrintText macro
   push dx
   mPrintString line_1
   pop dx
   inc dh
   mMoveCursor dh, dl

   push dx
   mPrintString line_2
   pop dx
   inc dh
   mMoveCursor dh, dl

   push dx
   mPrintString line_3
   pop dx
   inc dh
   mMoveCursor dh, dl

   push dx
   mPrintString line_4
   pop dx
   inc dh
   mMoveCursor dh, dl

   push dx
   mPrintString line_5
   pop dx
endm

START:
    jmp PROG_START

    handle:
    in al, 60h
    cmp al, 0Bh
    je END_PROG
    cmp al, 2
    je BUTTON_1
    cmp al, 3
    je BUTTON_2
    jmp finish

    BUTTON_1:
       cmp dl, 0
       je finish
       mClearScreen
       xor dh, dh
       dec dl
       mMoveCursor dh, dl
       mPrintText 
       jmp finish

    BUTTON_2:
       cmp dl, 41
       je finish
       mClearScreen
       xor dh, dh
       inc dl
       mMoveCursor dh, dl
       mPrintText 
       jmp finish

    END_PROG:
       mov exit_code, 1
 
    finish:
    jmp cs:old_data
    iret

    PROG_START: 
    mov ax, @data
    mov ds, ax
    
    xor ax, ax
    mov es, ax

    mSetColorMode
    mClearScreen
    mMoveCursor 0, 18
    mov               ah,         3
    sub               bh,         bh
    int               10h
    mPrintText
    
    mov ah, 35h
    mov al, 9
    int 21h
    mov word ptr old_data, bx
    mov word ptr old_data + 2, es
    xor ax, ax
    mov es, ax

    push ds
    push dx
    mov dx, offset handle
    mov ax, seg handle
    mov ds, ax
    mov ah, 25h 
    mov al, 9
    int 21h
    pop dx
    pop ds

    cycle:
    mov cl, exit_code
    cmp cl, 1
    jne cycle

    mov dx, word ptr old_data
    mov ax, word ptr old_data + 2
    mov ds, ax
    mov ah, 25h 
    mov al, 9
    int 21h
 
    mov ah, 4ch
    int 21h
END START