;------------------------------------
;Assembly language Lab 1.4
;Create by Haodong Lu on 2022/3/17 
;------------------------------------
.686P    
.model flat, c
ExitProcess proto stdcall : dword 
includelib  kernel32.lib  ; ExitProcess is implemented in kernel32.lib
printf proto : ptr sbyte, : vararg 	; function ¡°printf¡± returns the length of the output information!
scanf proto : ptr sbyte, : vararg
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
.DATA
; -------------------------- Display Module Start-------------------------------------- 
Hello_msg  DB "Welcome to the computer running status monitoring system!", 10, 0
Input_msg0 DB "Please enter your SAMID first!", 10, 0
Input_msg1 DB "Please enter three status information in the order of a,b,c!", 10, 0
Remark_msg DB "Remarks: Please enter a number followed by an Enter key!", 10, 0
exit_msg   DB "Bye!", 10, 0
; -------------------------- Display Module End ---------------------------------------
format db '%s', 0
format_short db '%hd', 0
format_int db '%d', 0
SAMID DB 9 DUP(0) ; Serial number of each group of data (can start numbering from 1)
SDA DD 256809     ; status information a
SDB DD -1023      ; status information b
SDC DD 1265       ; status information c
SF  DD ?          ; process result f
DIVISOR DD 128	  ; the divisor of the model
LOWF DB 25 dup(?)
MIDF DB 25 dup(?)
HIGHF DB 25 dup(?)
; ------------------------------------------------------------------------------------- 
.STACK 200 
.CODE 
data_processing proc c
	push ebp
	mov ebp, esp
	push esi
	push edi
	push ebx
	mov esi, [ebp + 16] ; offset SDA
	mov edi, [ebp + 12] ; offset SDB
	mov ebx, [ebp + 08] ; offset SDC

processing:
	mov eax, [esi]
	imul eax, 5
	adc eax, [edi]
	sbb eax, [ebx]
	adc eax, 100
	idiv DIVISOR
	mov SF, eax
	jmp data_processing_exit

data_processing_exit:
	pop ebx
	pop edi
	pop esi
	pop ebp
	ret 
data_processing endp

main proc c

SAMID_input:
	invoke	printf, offset format, offset Hello_msg
	invoke	printf, offset format, offset Input_msg0
	invoke	scanf, offset format, offset SAMID

status_input:
	invoke	printf, offset format, offset Input_msg1
	invoke	printf, offset format, offset Remark_msg
	invoke	scanf, offset format_int, offset SDA
	invoke	scanf, offset format_int, offset SDB
	invoke	scanf, offset format_int, offset SDC

processing:
	push offset SDA
	push offset SDB
	push offset SDC
	call data_processing
	add esp, 12
	mov eax, 0
	cmp SF, 100
	jz mid_f_mov_id
	ja high_f_mov_id
	jmp low_f_mov_id

mid_f_mov_id:
	mov bl, SAMID[eax]
	mov MIDF[eax], bl
	inc eax
	cmp eax, 9
	jb low_f_mov_id
	jmp low_f_status

mid_f_status:
	mov ebx, SDA
	mov dword ptr [MIDF[eax]], ebx
	add eax, 4
	mov ebx, SDB
	mov dword ptr [MIDF[eax]], ebx
	add eax, 4
	mov ebx, SDC
	mov dword ptr [MIDF[eax]], ebx
	add eax, 4
	mov ebx, SF
	mov dword ptr [MIDF[eax]], ebx
	jmp exit

low_f_mov_id:
	mov bl, SAMID[eax]
	mov LOWF[eax], bl
	inc eax
	cmp eax, 9
	jb low_f_mov_id
	jmp low_f_status

low_f_status:
	mov ebx, SDA
	mov dword ptr [LOWF[eax]], ebx
	add eax, 4
	mov ebx, SDB
	mov dword ptr [LOWF[eax]], ebx
	add eax, 4
	mov ebx, SDC
	mov dword ptr [LOWF[eax]], ebx
	add eax, 4
	mov ebx, SF
	mov dword ptr [LOWF[eax]], ebx
	jmp exit

high_f_mov_id:
	mov bl, SAMID[eax]
	mov HIGHF[eax], bl
	inc eax
	cmp eax, 9
	jb high_f_mov_id
	jmp high_f_status

high_f_status:
	mov ebx, SDA
	mov dword ptr [HIGHF[eax]], ebx
	add eax, 4
	mov ebx, SDB
	mov dword ptr [HIGHF[eax]], ebx
	add eax, 4
	mov ebx, SDC
	mov dword ptr [HIGHF[eax]], ebx
	add eax, 4
	mov ebx, SF
	mov dword ptr [HIGHF[eax]], ebx
	jmp exit
	
exit:
	invoke printf, offset format, offset exit_msg 
	invoke ExitProcess, 0
main endp
end