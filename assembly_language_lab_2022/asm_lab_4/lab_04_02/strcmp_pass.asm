;--------------------------------------
;Assembly language Lab 4.2
;Create by Haodong Lu on 2022/04/22
;strcmp_pass.asm
;--------------------------------------
.386
.686P
.model flat, c
VirtualProtect proto stdcall: dword, :dword, :dword, :dword
extern flag : dword
.data
s	db 80H, 36H, 4CH
	db 80H, 76H, 01H, 55H
	db 80H, 76H, 02H, 48H
	db 80H, 76H, 03H, 41H
	db 80H, 76H, 04H, 4FH
	db 80H, 76H, 05H, 44H
	db 80H, 76H, 06H, 4FH
	db 80H, 76H, 07H, 4EH
	db 80H, 76H, 08H, 47H
	db 80H, 76H, 09H, 49H
len = $ - s
oldprotect dd ?
.code
strcmp_pass	proc str1 : dword, str2 : dword, time : dword
	mov eax, len
	mov ebx, 40h
	lea ecx, CopyHere
	invoke VirtualProtect, ecx, eax, ebx, offset oldprotect
	mov ecx, len
	mov edi, offset CopyHere
	mov esi, offset s
CopyCode:
	mov al, [esi]
	mov [edi], al
	inc esi
	inc edi
	loop CopyCode
	mov esi, str1
	mov edi, str2
	mov ecx, time
CopyHere:	
	db len dup(0)
	;XOR byte ptr[esi],'L'
	;XOR byte ptr[esi+1],'U'
	;XOR byte ptr[esi+2],'H'
	;XOR byte ptr[esi+3],'A'
	;XOR byte ptr[esi+4],'O'
	;XOR byte ptr[esi+5],'D'
	;XOR byte ptr[esi+6],'O'
	;XOR byte ptr[esi+7],'N'
	;XOR byte ptr[esi+8],'G'
	;XOR byte ptr[esi+9],'I'
strcmp_1:	
	repz cmpsb
	cmp ecx, 0
	je strcmp_equ
	jmp strcmp_end
strcmp_equ:
	mov ebx, 1
	mov flag, ebx
	jmp strcmp_exit
strcmp_end:
	mov ebx, 0
	mov flag, ebx
strcmp_exit:
	ret
strcmp_pass endp
end

