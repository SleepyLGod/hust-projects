;--------------------------------------
;Assembly language Lab 3.1
;Create by Haodong Lu on 2022/04/08
;s_copy
;--------------------------------------
.686     
.model flat, stdcall
includelib  ucrt.lib
includelib  libcmt.lib
includelib  legacy_stdio_definitions.lib
.data
.stack 200
.code
; copy the struct from address2 to address1
; another function: 25 bytes equals to 4 * 6 bytes + 1 byte
s_copy proc c  addr_1: dword, addr_2: dword
	push esi
	push edi
	push eax
	push ebx
	mov ebx, 0
	mov esi, addr_2
	mov edi, addr_1
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
END