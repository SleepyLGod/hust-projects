;--------------------------------------
;Assembly language Lab 4.2
;Create by Haodong Lu on 2022/04/22
;main.asm
;--------------------------------------
.386
.686P    
.model flat, c
includelib  kernel32.lib  ; ExitProcess is implemented in kernel32.lib
includelib  ucrt.lib
ExitProcess proto stdcall : dword 
printf proto c : ptr sbyte, : vararg 	; function ¡°printf¡± returns the length of the output information!
scanf proto c : ptr sbyte, : vararg
clock proto c
QueryPerformanceCounter proto stdcall : dword
strcmp_pass proto : dword, : dword, :dword
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
; ----------------------------- pubic variable definition -------------------------------
public format_
public format_int_
public MIDF
public sf_
public mid_cnt_
public midf_print_msg_
public flag
; ---------------------------------- macro definition -----------------------------------
; Is str1 equals to str2 or not?
strcmp_username_ macro str1, str2, flag
	local continue_, differ_, exit_m_
	push eax
	push ebx
	mov bh, 0
	mov eax, 0
continue_:
	mov bh, str1[eax]
	cmp bh, str2[eax]
	jne differ_
	inc eax
	cmp bh, 0
	jne continue_
	mov flag, 1
	jmp exit_m_
differ_:
	mov flag, 0
exit_m_:
	pop ebx
	pop eax
endm
; ----------------------- the Struct of the Input Information -------------------------- 
S struct
	SAMID DB 9 DUP(0) ; Serial number of each group of data (can start numbering from 1)
	SDA DD 256809     ; status information a
	SDB DD -1023      ; status information b
	SDC DD 1265       ; status information c
	SF  DD 0          ; process result f9
S ENDS
SLen EQU TYPE S
.DATA
; -------------------------- Display Module Start --------------------------------------- 
hello_msg_ DB "Welcome to the computer running status monitoring system, U202010755!", 0
input_name_msg_ DB "Please input Your name:  ", 0
input_password_msg_ DB "Please input Your password:  ", 0
password_ok_ DB "OK!", 0
username_err_ DB "Incorrect username!", 0ah, 0
password_err_ DB "Incorrect password!", 0ah, 0
midf_print_msg_ DB "Here is the group of MIDF:", 0
option_msg_ DB "Rerun or Quit (R / Q) ?", 0
exit_msg_ DB "Goodbye, U202010755!", 0
Input_msg_0_ DB "Please enter your SAMID first!", 0ah, 0
Input_msg_1_ DB "Please enter three status information in the order of a,b,c!", 0
Remark_msg_ DB "Remarks: Please enter a number followed by an Enter key!", 0
option_err_msg_ DB "Invalid key! Please input R / Q / r / q!", 0ah, 0
; -------------------------- Display Module End -----------------------------------------
format_ db '%s', 0ah, 0dh, 0
format_2_ db '%s', 0
format_short_ db '%hd', 0ah, 0dh, 0
format_int_ db '%d', 0ah, 0dh, 0
format_msg_ db "%s: %s", 0ah, 0dh, 0
format_time_msg_ db "Time elapsed is : %d ¦Ìs!", 0ah, 0dh, 0
name_input_ db 100 dup(0) ; Save the name you type in!
password_input_ db 100 dup(0) ; Save the password you type in!
username_ db 'luhaodong', 0
password_ db 'U' XOR 'L','2' XOR 'U', '0' XOR 'H', '2' XOR 'A', '0' XOR 'O', '1' XOR 'D', '0' XOR 'O', '7' XOR 'N', '5' XOR 'G', '5' XOR 'I', 0 ; Correct password!
; f = (a * 1024 + b * 256 - c * 64 + 255) / 256
INPUT S <'00000000', 2539, 6, 1, >, 
	    <'00000001', 2539, 6, 1, >, 
	    <'00000002', 2540, 1, 1, >, 
	    <'00000003', 2540, 1000, 1, >, 	
	    <'00000004', 2540, 44, 44, >, 
	    <'00000005', 2540, 666, 666, >, 
	    <'00000006', 5, 4, 1, >
LOWF S 5 dup(<>)
MIDF S 5 dup(<>)
HIGHF S 5 dup(<>)
input_len_ dd 6 ; The length of the input
flag dd 0 ; Return value of the strcmp macro
error_cnt_ db 0 ; The quantity of the input errors
input_addr_ dd 0 ; The address of the input
input_cnt_ dd 0 ; The quantity of the input S
low_cnt_ dd 0 ; The quantity of the input S with low SF
mid_cnt_ dd 0 ; The quantity of the input S with mid SF
high_cnt_ dd 0 ; The quantity of the input S with high SF
sf_ dd 0 ; The result of the calculation of SF
des_addr_ dd 0 ; destination address
option_ db ? ; r or q
start_time_ dd  0 ; the start time to check
end_time_   dd  0 ; the end time to check
used_time_  dd  0 ; the total time used in the process of checking
func_map_ dd 4 dup(0);the map of all the functions to be used
.STACK	200
.code
main proc c
   invoke printf, offset format_, offset hello_msg_
login_name_:
   invoke printf, offset format_, offset input_name_msg_
   invoke scanf, offset format_2_, offset name_input_
   ;cli
   ;push dword ptr offset login_password_
   strcmp_username_ username_, name_input_, flag
   cmp flag, 1
   ;pop eax
   ;mov ebx, dword ptr [esp - 4]
   ;sti
   jne name_error_
   mov error_cnt_, 0
login_password_:
   invoke printf, offset format_, offset input_password_msg_
   invoke scanf, offset format_2_, offset password_input_
   call clock
   mov start_time_, eax
   invoke strcmp_pass, offset password_, offset password_input_, 10
   call clock
   sub eax, start_time_
   cmp eax, 55 ; == 55ms
   jg main_exit_
   cmp flag, 1
   jne password_error_
   jmp init_
   db 'Hey man, 这是 the first interferenceis coming呀 @$%^&$%^！', 0ah, 0
name_error_:
	invoke printf, offset format_, offset username_err_
	inc error_cnt_
	cmp error_cnt_, 3
	je main_exit_
	jmp login_name_
	db 'Wow, $%^%^&$@ this is 第二个 interference!!!', 0ah, 0
password_error_:
	invoke printf, offset format_, offset password_err_
	inc error_cnt_
	cmp error_cnt_, 3
	je main_exit_
	jmp login_password_
	db '走过路过不要$%^$&$@错过 The third interference, little baby!', 0ah, 0
init_:
	;func_map_
	mov func_map_[0], s_copy
	mov func_map_[4], f_calculate
	mov func_map_[8], midf_print
	mov func_map_[12], main_exit_
	;func_map_ end
	mov input_cnt_, 0
	mov low_cnt_, 0
	mov mid_cnt_, 0
	mov high_cnt_, 0
	mov sf_, 0
reduce_input_:
    cmp input_cnt_, 6
	je print_
	mov eax, input_cnt_
	imul eax, SLen
	lea esi, INPUT[eax]
	mov input_addr_, esi
	mov sf_, 0
	invoke QueryPerformanceCounter, offset start_time_
	mov ebx, func_map_[4]
	call ebx
	invoke QueryPerformanceCounter, offset end_time_
	push ebx
	mov ebx, end_time_
	sub ebx, start_time_
	cmp ebx, 55000
	pop ebx
	jg main_exit_
	inc input_cnt_
	cmp sf_, 100
	je mid_mov_
	jg high_mov_
low_mov_:
	mov eax, low_cnt_
	imul eax, SLen
	lea esi, LOWF[eax]
	inc low_cnt_
	mov des_addr_, esi
	mov ebx, func_map_[0]
	call ebx
	jmp reduce_input_
mid_mov_:
	mov eax, mid_cnt_
	imul eax, SLen
	lea esi, MIDF[eax]
	inc mid_cnt_
	mov des_addr_, esi
	mov ebx, func_map_[0]
	call ebx
	jmp reduce_input_
high_mov_:
	mov eax, high_cnt_
	imul eax, SLen
	lea esi, HIGHF[eax]
	inc high_cnt_
	mov des_addr_, esi
	mov ebx, func_map_[0]
	call ebx
	jmp reduce_input_
print_:
	mov ebx, func_map_[8]
	call ebx
option_input_:
	invoke printf, offset format_, offset option_msg_
	invoke scanf, offset format_msg_, offset option_
	mov al, option_
	cmp al, 82 ; R
	je init_
	cmp al, 114 ; r
	je init_
	cmp al, 81 ; Q
	je main_exit_
	cmp al, 113 ; q
	je main_exit_
	invoke printf, offset format_, offset option_err_msg_
	jmp option_input_
main_exit_:
	invoke printf, offset format_, offset exit_msg_
    invoke ExitProcess, 0
main endp

f_calculate proc c
	push esi
	push ebx
	mov	ebx, [esi + 9]
	;imul ebx, 5
	mov ecx, ebx
	shl ebx, 2
	add ebx, ecx
	sbb ebx, [esi + 17]
	adc ebx, [esi + 13]
	adc	ebx, 100
	shr ebx, 7 ; Bitwise block is faster than division!
	mov [esi + 21], ebx
	mov sf_, ebx
	pop ebx
	pop esi
	ret
f_calculate endp

; copy the struct from address2 to address10
; another function: 25 bytes equals to 4 * 6 bytes + 1 byte
s_copy proc c
	push esi
	push edi
	push eax
	push ebx
	mov ebx, 0
	mov esi, input_addr_
	mov edi, des_addr_
bytes_mov_:
	mov eax, [esi + ebx * 4]
	mov [edi + ebx * 4], eax
	inc ebx
	cmp ebx, 6
	jne bytes_mov_
	mov al, [esi + 24] ; the last byte of S
	mov [edi + 24], al
	pop ebx
	pop eax
	pop edi
	pop esi
	ret
s_copy endp

midf_print proc c
	local mid_size_ : dword
	mov eax, mid_cnt_
	imul eax, SLen
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
	add ebx, SLen
	add esi, SLen
	cmp ebx, mid_size_
	jne print_
	pop ebx
	pop esi
	ret
midf_print endp
END