;--------------------------------------
;Assembly language Lab 3.1
;Create by Haodong Lu on 2022/04/08
;midf_print
;--------------------------------------
.686     
.model flat, stdcall
includelib  ucrt.lib
printf proto c : ptr sbyte, : vararg 	; function ¡°printf¡± returns the length of the output information!
scanf proto c : ptr sbyte, : vararg
includelib  libcmt.lib
includelib  legacy_stdio_definitions.lib
; ----------------------- the Struct of the Input Information ------------------------- 
S struct
	SAMID DB 9 dup(0)
	SDA   DD 0
	SDB   DD 0
	SDC   DD 0
	SF    DD 0
S ENDS
s_len_ EQU TYPE S
;--------------------------- extern variable definition -------------------------------
extern format_: byte
extern format_int_: byte
extern mid_cnt_: dword
extern MIDF: S
extern midf_print_msg_: byte
.data
.stack 200
.code
midf_print proc c
	local mid_size_ : dword
	mov eax, mid_cnt_
	imul eax, s_len_
	mov mid_size_, eax
	push esi
	push ebx
	mov ebx, 0
	lea esi, MIDF
	invoke	printf, offset format_, offset midf_print_msg_
print_:
	invoke printf, offset format_, esi
	invoke printf, offset format_int_, MIDF[ebx].SDA
	invoke printf, offset format_int_, MIDF[ebx].SDB
	invoke printf, offset format_int_, MIDF[ebx].SDC
	invoke printf, offset format_int_, MIDF[ebx].SF
	add ebx, s_len_
	add esi, s_len_
	cmp ebx, mid_size_
	jne print_
	pop ebx
	lea esi, MIDF
	pop esi
	ret
midf_print endp
END