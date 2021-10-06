.model small
.stack 100h
.data
    _array     dw        0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    fio        db        'Karelsky Mikhail Konstantinovich$'
    fPtr       dw        fio
    iPtr       dw        fio[9]
    oPTR       dw        fio[17]
    _const     dw        1103h
    _name      db        'Mishka$'
    symbol     db        24
    birthDay   db        '11032002$'
    namePtr    dw        _name
.code
Start:
    mov	       ax,       @data
    mov	       ds,       ax
    mov        ax,       0000

    mov        ax,       _array[2]
    mov        bx,       _array + 2
    mov        cx,       _array
    mov        dx,       _array[3*2]
    mov        si,       _array + 4
    mov        di,       _array[0]
    mov        bp,       _array
    mov        sp,       _array[2*2]

    mov        al,       fio[15]
    mov        ds:1103,  2002h
    mov        cx,       _const

    mov        ax,       4c00h
    int        21h
end Start
END