.model small
.stack 100h
.data
message   db   'Run the program in the debugger', '$'
nm        db   10, 13, 'My name is Karelsky', '$'
grp       db   10, 13, 'My group is IUK4-32B', '$'
perem_1   db   0ffh
perem_2   dw   3a7fh
perem_3   dd   0f54d567ah
mas       db   10 dup (' ')
pole_1    db   5 dup (?)
adr       dw   perem_3
adr_full  dd   perem_3
numbers   db   11, 34, 56, 23
fin       db   'End of the program data segment $'
Pa        db   5BH
Pb        dw   0BA21H
Pc        dd   0FA4A32BCH
Masv      db   4, 5, 6, 5 dup (0)
Pole      db   6 dup (?)
Adrs      dw   Pc
Adrs_full dd   Pc
.code
start:
     mov   ax, @data
     mov   ds, ax
     mov   ah, 09h
     mov   dx, offset message
     int   21h
     mov   ah, 7h
     int   21h
     mov   ah, 09h
     mov   dx, offset nm
     int   21h
     mov   ah, 7h
     int   21h
     mov   ah, 09h
     mov   dx, offset grp
     int   21h
     mov   ah, 7h
     int   21h
     mov   ax, 4c00h
     int   21h
end start