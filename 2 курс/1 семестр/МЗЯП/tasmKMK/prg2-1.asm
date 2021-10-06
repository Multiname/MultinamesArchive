.model small
.stack 100h
.data
	A	db	?
	B	db	?
	C	db	?
	D	db	?

.code
Start:
	mov		ax, @data
	mov		ds, ax
	mov 	A, 12h		
	mov		B, 12
	mov		C, 05h
	mov 	D, 9
	mov		al, A
	mov 	ah, B
	xchg	al, ah
	mov		bx, 3E10h
	mov		cx, bx
	push	bx
	push	cx
	push	ax
	lea		si, C
	mov		ax, si
	lea		di, D 
	mov		bx, di
	pop		ax
	pop		cx
	pop		bx
	mov 	bx, ax
	mov		A, al
	mov		B, al
	mov 	C, 0
	mov 	ax, 4C00h
	int		21h
end Start
END