;--------------------------------------
;Assembly language Lab 3.1
;Create by Haodong Lu on 2022/04/08
;f_calculate
;--------------------------------------
.686     
.model flat, stdcall
includelib  ucrt.lib
includelib  libcmt.lib
includelib  legacy_stdio_definitions.lib
;--------------------------- extern variable definition -------------------------------
extern sf_: dword
.data
.stack 200
.code
f_calculate proc c s_addr: dword
	push esi
	push ebx
	mov esi, s_addr
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
END