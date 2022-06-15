;------------------------------------
;Assembly language Lab 1.3
;Create by Haodong Lu on 2022/3/18 
;------------------------------------
.386
.686P    
.model flat, c
ExitProcess proto stdcall : dword 
includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
printf proto : ptr sbyte, : vararg
scanf proto : ptr sbyte, : vararg
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
.DATA
; --------------------------Display Module Start-------------------------- 
Input_msg DB "Iput Your Password:  ", 10, 0
Hello_msg DB "Hello, U202010755", 10, 0
exit_msg DB "GoodBye, U202010755!", 10,0
Password_ok DB "OK!", 10, 0
Password_err1 DB "Incorrect Password!", 10, 0
Password_err2 DB "Password Too Long!", 10, 0
Password_err3 DB "Password Too Short!", 10, 0
; -------------------------- Display Module End --------------------------
format db '%s', 0
format_short db '%hd', 0
Password_input DB 100 dup(0) ; Save the password you type in!
Password DB 'U202010755', 0 ; Correct password!
Is_length_right DB 1 dup(0)
;------------------------------------------------------------------------- 
;item Example:
.STACK 200 
.CODE 

strlen proc
	lea esi, Password_input ; record the offset address of the string
	xor cx, cx ; cx records the number of characters
	mov cl, 0

flag:
	mov eax, [esi]
	cmp eax, 0
	jz strlen_judge
	inc cl
	inc esi
	jmp flag

strlen_judge:
	cmp cl, 10
	jz strlen_exit
	cmp cl, 10
	jg strlen_err_long
	jmp strlen_err_short

strlen_err_long:
	invoke printf, offset format, offset Password_err2;
	mov Is_length_right, 1
	jmp strlen_exit

strlen_err_short:
	invoke printf, offset format, offset Password_err3;
	mov Is_length_right, 1
	jmp strlen_exit

strlen_exit:
	mov ax, 0
	ret
strlen endp

main proc
invoke printf, offset format, offset Hello_msg
invoke printf, offset format, offset Input_msg
invoke scanf, offset format, offset Password_input ; Type in password
call strlen
cmp Is_length_right, 0
jnz exit

mov ebx, 0 ; calculate the data
mov al, 0 

check_password:
	; byte comparison
	;mov al, [Password + ebx]
	;cmp al, [password_input + ebx]
	;jne password_err
	;inc ebx
	;cmp ebx, 10
	;jl check_password

	; word comparison
	mov ax, word ptr [[Password + ebx]]
	cmp ax, word ptr [[password_input + ebx]]
	jne password_err
	add ebx, 2
	cmp ebx, 10
	jl check_password

correct:
	invoke printf, offset format, offset Password_ok
	jmp exit

password_err:
	invoke printf, offset format, offset Password_err1
	jmp	exit

exit:
	invoke printf, offset format, offset exit_msg 
	mov	ebx, 0
	mov al, 0
	invoke ExitProcess, 0

main endp 
end