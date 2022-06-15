;--------------------------------------
;Assembly language Lab 2.1
;Create by Haodong Lu on 2022/3/23 
;--------------------------------------
;�Ż�ָ�ϣ�
; ʹ��������λ����˳�
; add����inc
; �����м������ʹ��
; �Ż�Ѱַ��ʽ�Ӷ����Ч��
; ������תָ��ʹ��������
;	ȥ��tmp��֧
;	����ʱ����ѭ��������
;		�������������ֽڿ���
;	���ڲ���ʡȥ��������תָ��
;		->����ʹ��ָ����߲����еķ�֧
; ȥ���������ù���
; ->���ɺ����
; ->ȡ������ã�����һ��������
;--------------------------------------
;�ص���˵����
; ���Ը��ݶ����BUF�����е�����
;	�������ж��벢���㣨��΢��һ�´��룺
;		1.���Խ�BUF���Ƶ�INPUT��
;		2.���԰Ѻ�����INPUT��ΪBUF��
; Ҳ�����Լ�����������һ������
; ���㿽�������ظ�Ĭ��100000000��
; ���Ը����Լ���õ�fֵ���������ظ�����
;--------------------------------------
;���Լ����Ż�
; ʹ�ô���������xmm�Ĵ���ֱ�Ӵ���25�ֽ�
; ����������תָ����Ŀ
;--------------------------------------
; ���Ե�ʱ�����ʹ��BUF����
;--------------------------------------
.386
.686P    
.model flat, c
ExitProcess proto stdcall : dword 
includelib  kernel32.lib  ; ExitProcess is implemented in kernel32.lib
includelib  ucrt.lib
clock proto
QueryPerformanceCounter proto stdcall : dword
printf proto c : ptr sbyte, : vararg 	; function ��printf�� returns the length of the output information!
scanf proto c : ptr sbyte, : vararg
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
; ----------------------- the Struct of the Input Information ------------------------- 
S struct
	SAMID DB 9 DUP(0) ; Serial number of each group of data (can start numbering from 1)
	SDA DD 256809     ; status information a
	SDB DD -1023      ; status information b
	SDC DD 1265       ; status information c
	SF  DD 0          ; process result f
S ENDS
N  EQU 200
SLen EQU TYPE S
.DATA
; --------------------------Display Module Start--------------------------------------- 
Hello_msg DB "Welcome to the computer running status monitoring system!", 10, 0
Input_msg0 DB "Please enter your SAMID first!", 10, 0
Input_msg1 DB "Please enter three status information in the order of a,b,c!", 10, 0
Remark_msg DB "Remarks: Please enter a number followed by an Enter key!", 10, 0
exit_msg DB "Bye!", 10, 0
; -------------------------- Display Module End ---------------------------------------
format db '%s',  0
format_short db '%hd', 0
format_int db '%d', 0
format_time_msg db "Time elapsed is : %d ��s!", 10, 13, 0
buf S <'202203001', 10, 20, 30, 0>
    S <'202203002', 100, 200, 300, 0>
    S <'202203003', 1234, 456, 789, 0>
    S <'202203004', 123, 4567, 89, 0>
    S N-4 DUP(<>)
LOWF S 10000 dup(<>)
MIDF S 10000 dup(<>)
HIGHF S 10000 dup(<>)
INPUT S <>
start_time dd  0   
end_time   dd  0
used_time  dd  0
cnt dd 0
.STACK	200
.code
main proc c
Init:
	mov eax, 0
	mov ebx, 0
	mov edi, 0
	mov ebp, 0
	mov esi, 0
Input_struct:
	push eax
	invoke	printf, offset format, offset Hello_msg
	invoke	printf, offset format, offset Input_msg0
	pop eax
	lea ebx, INPUT
	push eax
	invoke	scanf,  offset format, ebx
	invoke	printf, offset format, offset Input_msg1
	invoke	printf, offset format, offset Remark_msg
	pop eax
	lea ebx, INPUT + 9
	push eax
	invoke	scanf, offset format_int, ebx
	pop eax
	lea ebx, INPUT + 13
	push eax
	invoke	scanf, offset format_int, ebx
	pop eax
	lea ebx, INPUT + 17
	push eax
	invoke	scanf, offset format_int, ebx
	pop eax
	mov ebx, 0
	; start timing!
	invoke QueryPerformanceCounter, offset start_time
	; push eax
	; invoke	clock
	; mov start_time, eax
	; pop eax
Repeat_:
	mov ecx, cnt
	inc ecx
	mov cnt, ecx
	cmp cnt, 10000
	je exit
	mov eax, 0
	mov ebx, 0
	mov edi, 0
	mov ebp, 0
	mov esi, 0
Calculate:
	mov eax, 0
	mov	ebx, (S ptr INPUT).SDA
	;imul ebx, 5
	mov ecx, ebx
	shl ebx, 2
	add ebx, ecx
	adc ebx, (S ptr INPUT).SDB
	sbb ebx, (S ptr INPUT).SDC
	adc	ebx, 100
	shr ebx, 7 ; Bitwise block is faster than division!
	mov (S ptr INPUT).SF, ebx
	cmp ebx, 100
	jl Low_f_id
	je Mid_f_id

High_f_id:
	mov bl, byte ptr INPUT[eax]
	mov byte ptr (S ptr HIGHF[edi])[eax], bl
	inc eax
	cmp eax, 9
	jne High_f_id
High_f:
	mov ebx, (S ptr INPUT).SDA
	mov (S ptr HIGHF[edi]).SDA, ebx
	mov ebx, (S ptr INPUT).SDB
	mov (S ptr HIGHF[edi]).SDB, ebx
	mov ebx, (S ptr INPUT).SDC
	mov (S ptr HIGHF[edi]).SDC, ebx
	mov ebx, (S ptr INPUT).SF
	mov (S ptr HIGHF[edi]).SF, ebx
	add edi, SLen
	cmp edi, 10000 * SLen
	; jmp Tmp
	; add eax, SLen
	; cmp eax, 10000 * SLen
	je Repeat_
	jl Calculate
	jmp exit
Low_f_id:
	mov bl, byte ptr INPUT[eax]
	mov byte ptr (S ptr LOWF[ebp])[eax], bl
	inc eax
	cmp eax, 9
	jne Low_f_id
Low_f:
	mov ebx, (S ptr INPUT).SDA
	mov (S ptr LOWF[ebp]).SDA, ebx
	mov ebx, (S ptr INPUT).SDB
	mov (S ptr LOWF[ebp]).SDB, ebx
	mov ebx, (S ptr INPUT).SDC
	mov (S ptr LOWF[ebp]).SDC, ebx
	mov ebx, (S ptr INPUT).SF
	mov (S ptr LOWF[ebp]).SF, ebx
	add ebp, SLen
	cmp ebp, 10000 * SLen
	; jmp Tmp
	; add eax, SLen
	; cmp eax, 10000 * SLen
	je Repeat_
	jl Calculate
	jmp exit
Mid_f_id:
	mov bl, byte ptr INPUT[eax]
	mov byte ptr (S ptr HIGHF[esi])[eax], bl
	inc eax
	cmp eax, 9
	jne Mid_f_id
Mid_f:
	mov ebx, (S ptr INPUT).SDA
	mov (S ptr MIDF[esi]).SDA, ebx
	mov ebx, (S ptr INPUT).SDB
	mov (S ptr MIDF[esi]).SDB, ebx
	mov ebx, (S ptr INPUT).SDC
	mov (S ptr MIDF[esi]).SDC, ebx
	mov ebx, (S ptr INPUT).SF
	mov (S ptr MIDF[esi]).SF, ebx
	add esi, SLen
	cmp esi, 10000 * SLen
	; jmp Tmp
	; add eax, SLen
	; cmp eax, 10000 * SLen
	je Repeat_
	jl Calculate
	jmp exit
; Tmp:
	; add eax, TYPE S
	; cmp eax, 10000 * (TYPE S)
	; jle Calculate
exit:
	; invoke clock
	; mov end_time, eax
	; sub eax, start_time
	invoke QueryPerformanceCounter, offset end_time
    mov eax, end_time
    sub eax, start_time
	invoke printf, offset format_time_msg, eax
	invoke printf, offset format, offset exit_msg 
	invoke ExitProcess, 0
main endp
END