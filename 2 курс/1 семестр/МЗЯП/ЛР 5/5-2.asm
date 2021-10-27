.model small
.386
.stack 100h
.data
_buffer    db   3, 3 dup(0)
_x         db   4
_a         db   0
_y         db   0
_y1        db   0
_y2        db   0
_command   db   0
_secDig    db   0
_name      db   'Karelsky', '$'
_number    db   'IUK4-32.B', '$'
_faculty   db   'Informatics and control', '$'
_symbols   db   '!!!!!', '$'
_formula   db   '               { |x|,     x < 0', 13, 10
           db   '          y1 = {', 13, 10
           db   '               { x - a,   x >= 0', 13, 10, 13, 10
           db   '               { a + x,   x mod 3 == 1', 13, 10
           db   '          y2 = {', 13, 10
           db   '               { 7,       x mod 3 != 1', 13, 10, 13, 10
           db   '          y = y1 - y2', 13, 10, 13, 10
           db   '          x = 4', 13, 10
           db   '          a = 0', 13, 10
           db   '          y = 0', 13, 10, 13, 10
           db   '          1: Change x', 13, 10
           db   '          2: Change a', 13, 10
           db   '          0: Exit', 13, 10
           db   '          >>> ', '$'
_xInput    db   '          x = ', '$'
_aInput    db   '          a = ', '$'

.code
Start:
mov        ax,  @data
mov        ds,  ax
sub        ax,  ax

;�������� ����
mov        ax,  0600h
mov        bh,  5Fh
mov        cx,  0000
mov        dx,  184Fh
int        10h

;��������� ������� � ������� ����� ����
;�������� ������� � ������� ����� ����
mov        ah,  2
mov        dh,  0
mov        dl,  0
mov        bh,  0
int        10h

;����� ������
mov        ah,  09h
mov        dx,  offset _name
int        21h

;��������� ������� � ������� ������ ����
;�������� ������� � ������� ������ ����
mov        ah,  2
mov        dh,  0
mov        dl,  47h
mov        bh,  0
int        10h

;����� ������
mov        ah,  09h
mov        dx,  offset _number
int        21h

;��������� ������� � ������ ����� ����
;�������� ������� � ������ ����� ����
mov        ah,  2
mov        dh,  17h
mov        dl,  0
mov        bh,  0
int        10h

;����� ������
mov        ah,  09h
mov        dx,  offset _faculty
int        21h

;��������� ������� � ������ ������ ����
;�������� ������� � ������ ������ ����
mov        ah,  2
mov        dh,  17h
mov        dl,  4Bh
mov        bh,  0
int        10h

;����� ������
mov        ah,  09h
mov        dx,  offset _symbols
int        21h

;�������� ������ ������ �� ������� ����
mov        ax,  0701h
mov        bh,  5Fh
mov        cx,  1700h
mov        dx,  184Fh
int        10h

;��������� ����
;�������� �������
mov        ah,  2
mov        dh,  2
mov        dl,  0
mov        bh,  0
int        10h

;����� ����
mov        ah,  09h
mov        dx,  offset _formula
int        21h

INPUT:
   ;�������� ������� � ����� �����
   mov        ah,  2
   mov        dh,  19
   mov        dl,  14
   mov        bh,  0
   int        10h

   ;��������� ������� �������
   mov        ah,  1
   int        21h
   mov        _command, al

   ;�������� �����
   ;�������� ������� � ����� �����
   mov        ah,  2
   mov        dh,  19
   mov        dl,  14
   mov        bh,  0
   int        10h

   ;����� ������� � ����� �����
   mov        ah,  9
   mov        al,  ' '
   mov        bl,  5Fh
   mov        cx,  1
   int        10h

   ;��������� ����� ������� ����
   mov        al,  _command
   cmp        al,  '1'
   je         X_INPUT
   cmp        al,  '2'
   je         A_INPUT
   cmp        al,  '0'
   je         END_PROG
   JMP        INPUT


X_INPUT:
   ;��������� ����������� ������� ���� �����
   ;�������� ������� � ������ ����� �����
   mov        ah,  2
   mov        dh,  21
   mov        dl,  0
   mov        bh,  0
   int        10h

   ;����� ������
   mov        ah,  09h
   mov        dx,  offset _xInput
   int        21h

   ;���� �����
   mov        ah,  0Ah
   lea        dx,  _buffer
   int        21h

   ;�������� ����� �� ����
   mov        al,  _buffer + 2
   cmp        al,  '-'

   ;������� ����������� �����
   ;�������� ������� � ����� ����� �����
   mov        ah,  2
   mov        dh,  21
   mov        dl,  10
   mov        bh,  0
   int        10h

   ;���������� ������ ����� ���������
   mov        ah,  9
   mov        al,  ' '
   mov        bl,  5Fh
   mov        cx,  7
   int        10h

   ;��������, ��������� �� ����� �����
   je         MINUS_X
   jmp        PLUS_X

   MINUS_X:
      ;��������� ������� ������
      ;�������� ������� � ������ ������� ����
      mov        ah,  2
      mov        dh,  12
      mov        dl,  14
      mov        bh,  0
      int        10h

      ;����� ������
      mov        ah,  9
      mov        al,  '-'
      mov        bl,  5Fh
      mov        cx,  1
      int        10h

      ;����� �����
      ;�������� ������� � ���������� �������
      mov        ah,  2
      mov        dh,  12
      mov        dl,  15
      mov        bh,  0
      int        10h

      ;����� ����� �����
      mov        ah,  9
      mov        al,  _buffer + 3
      mov        bl,  5Fh
      mov        cx,  1
      int        10h

      ;������� ����� �� ������� � �������������, ����� ����� �� ����
      sub        al,  30h
      mov        bl,  -1
      imul       bl
      mov        _x,  al
      jmp        CALCULATE

   PLUS_X:
      ;��������� ������� ������ ����� �����
      ;�������� ������� � ������ �������
      mov        ah,  2
      mov        dh,  12
      mov        dl,  14
      mov        bh,  0
      int        10h
      
      ;����� ������ �����
      mov        ah,  9
      mov        al,  _buffer + 2
      mov        bl,  5Fh
      mov        cx,  1
      int        10h

      ;�������� ����� �����
      mov        al,  _buffer + 1
      cmp        al,  1
      JE         X_ONE_DIGIT
      JMP        X_TWO_DIGITS

      X_ONE_DIGIT:
         ;������� �������, ������� ����� ������ ����� �����
         ;�������� ������� � ������� ����� ������ ����� �����
         mov        ah,  2
         mov        dh,  12
         mov        dl,  15
         mov        bh,  0
         int        10h

         ;����� �������
         mov        ah,  9
         mov        al,  ' '
         mov        bl,  5Fh
         mov        cx,  1
         int        10h

         ;������� ����� �� ������� � �������������
         mov        al,  _buffer + 2
         sub        al,  30h
         mov        _x,  al
         jmp        CALCULATE

      X_TWO_DIGITS:
         ;��������� ������� ������ ����� �����
         ;�������� ������� � ������ �������
         mov        ah,  2
         mov        dh,  12
         mov        dl,  15
         mov        bh,  0
         int        10h

         ;����� ������ ����� �����
         mov        ah,  9
         mov        al,  _buffer + 3
         mov        bl,  5Fh
         mov        cx,  1
         int        10h

         ;������� ����� �� ������� � �������������
         mov        al,  _buffer + 2
         sub        al,  30h
         mov        bl,  10
         mul        bl
         add        al,  _buffer + 3
         sub        al,  30h
         mov        _x,  al
         jmp        CALCULATE

A_INPUT:
   ;��������� ����������� ������� ���� �����
   ;�������� ������� � ������ ����� �����
   mov        ah,  2
   mov        dh,  21
   mov        dl,  0
   mov        bh,  0
   int        10h

   ;����� ������
   mov        ah,  09h
   mov        dx,  offset _aInput
   int        21h

   ;���� �����
   mov        ah,  1
   int        21h

   ;��������� ����� � ������
   mov        _a,  al

   ;������� ����������� �����
   ;�������� ������� � ����� ����� �����
   mov        ah,  2
   mov        dh,  21
   mov        dl,  10
   mov        bh,  0
   int        10h

   ;���������� ������ ����� ���������
   mov        ah,  9
   mov        al,  ' '
   mov        bl,  5Fh
   mov        cx,  7
   int        10h

   ;��������� ������� ����� 
   ;�������� ������� � ������ �����
   mov        ah,  2
   mov        dh,  13
   mov        dl,  14
   mov        bh,  0
   int        10h

   ;����� �����
   mov        ah,  9
   mov        al,  _a
   mov        bl,  5Fh
   mov        cx,  1
   int        10h

   ;������� ����� �� ������� � �������������
   sub        _a,  30h

      CALCULATE:
         ;�������� � �� ����
         cmp        _x,  0
         JL         Y_1_1
         JMP        Y_1_2

         Y_1_1:
            ;���������� ������ �
            mov        al,  _x
            mov        bl,  -1
            imul       bl
            mov        _y1, al
            JMP        Y_1_END

         Y_1_2:
            ;���������� �������� � � �
            mov        al,  _x
            sub        al,  _a
            mov        _y1, al

         Y_1_END:
            ;�������� ������� �� ������� � �� 3
            mov        al,  _x
            mov        bx,  3
            mov        ah,  0
            idiv       bl
            cmp        ah,  1
            JE         Y_2_1
            JMP        Y_2_2

         Y_2_1:
            ;���������� ����� � � �
            mov        al,  _x
            add        al,  _a
            mov        _y2, al
            JMP        Y_2_END

         Y_2_2:
            ;������������� �2 7
            mov        _y2, 7

         Y_2_END:
            ;���������� �������� �1 � �2
            mov        al,  _y1
            sub        al,  _y2
            mov        _y,  al

            ;��������� ����� ��� ����� �
            ;�������� ������� � ������ �������
            mov        ah,  2
            mov        dh,  14
            mov        dl,  14
            mov        bh,  0
            int        10h
            
            ;����� ��������
            mov        ah,  9
            mov        al,  ' '
            mov        bl,  5Fh
            mov        cx,  3
            int        10h

            ;�������� � �� ����
            cmp        _y,  0
            JL         MINUS_Y

            PLUS_Y:
               ;�������� ����� �
               cmp        _y,  9
               JL         PLUS_Y_ONE_DIGIT
               jmp        PLUS_Y_TWO_DIGITS

               PLUS_Y_ONE_DIGIT:
                  ;��������� ������� ����� �
                  ;�������� ������� � ������ �������
                  mov        ah,  2
                  mov        dh,  14
                  mov        dl,  14
                  mov        bh,  0
                  int        10h

                  ;����� �
                  mov        ah,  9
                  mov        al,  _y
                  add        al,  30h
                  mov        bl,  5Fh
                  mov        cx,  1
                  int        10h

                  JMP INPUT

               PLUS_Y_TWO_DIGITS:
                  ;��������� ����� �
                  ;�������� ������� � ������ �������
                  mov        ah,  2
                  mov        dh,  14
                  mov        dl,  14
                  mov        bh,  0
                  int        10h

                  ;����� ������ �����
                  mov        ah,  0
                  mov        al,  _y
                  mov        bl,  10
                  div        bl
                  mov        _secDig,  ah
                  add        al,  30h
                  mov        bl,  5Fh
                  mov        cx,  1
                  mov        ah,  9
                  int        10h

                  ;�������� ������� � ���������� �������
                  mov        ah,  2
                  mov        dh,  14
                  mov        dl,  15
                  mov        bh,  0
                  int        10h

                  ;����� ������ �����
                  mov        al,  _secDig
                  add        al,  30h
                  mov        bl,  5Fh
                  mov        cx,  1
                  mov        ah,  9
                  int        10h

                  JMP INPUT

            MINUS_Y:
               ;�������� ����� �
               cmp        _y,  -10

               ;��������� ������� ������
               ;�������� ������� � ������ �������
               mov        ah,  2
               mov        dh,  14
               mov        dl,  14
               mov        bh,  0
               int        10h

               ;����� ������
               mov        ah,  9
               mov        al,  '-'
               mov        bl,  5Fh
               mov        cx,  1
               int        10h

               ;�������� ������� � ���������� �������
               mov        ah,  2
               mov        dh,  14
               mov        dl,  15
               mov        bh,  0
               int        10h

               ;����� ����� � �� ����
               mov        al,  _y
               mov        bl,  -1
               imul       bl

               JG         MINUS_Y_ONE_DIGIT
               jmp        MINUS_Y_TWO_DIGITS

               MINUS_Y_ONE_DIGIT:
                  ;����� �����
                  add        al,  30h
                  mov        bl,  5Fh
                  mov        cx,  1
                  mov        ah,  9
                  int        10h

                  JMP INPUT

               MINUS_Y_TWO_DIGITS:
                  ;����� �����
                  ;����� ������ �����
                  mov        ah,  0
                  mov        bl,  10
                  div        bl
                  mov        _secDig,  ah
                  add        al,  30h
                  mov        bl,  5Fh
                  mov        cx,  1
                  mov        ah,  9
                  int        10h

                  ;�������� ������� � ���������� �������
                  mov        ah,  2
                  mov        dh,  14
                  mov        dl,  16
                  mov        bh,  0
                  int        10h

                  ;����� ������ �����
                  mov        al,  _secDig
                  add        al,  30h
                  mov        bl,  5Fh
                  mov        cx,  1
                  mov        ah,  9
                  int        10h

                  JMP INPUT

END_PROG:
mov   ax,    4C00h
int   21h
end start
END