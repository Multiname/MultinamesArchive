.model small
.stack 100h
.data
message   db   'Run the program in the debugger', '$'
nm        db   10, 13, 'My name is Karelsky', '$'
grp       db   10, 13, 'My group is IUK4-32B', '$'
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