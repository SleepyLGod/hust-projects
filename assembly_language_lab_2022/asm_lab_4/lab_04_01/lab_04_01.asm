;----------------------------------------------------
;Assembly language Lab 4.1
;Create by Haodong Lu on 2022/04/22
;----------------------------------------------------
.386
STACK	SEGMENT USE16 STACK	;主程序的堆栈
		DB 200 DUP(0)
STACK	ENDS
;
CODE	SEGMENT USE16
		ASSUME CS: CODE,DS:CODE,SS:STACK
	hello DB    'How are you! ',0ah, 0dh, 0
		DB  '7.Check ',0ah, 0dh, 0
		DB  '8.Install ',0ah, 0dh, 0
		DB  '9.Exit ',0ah, 0dh, 0, '$'
	FLAG  DB  0			;用来标检查中断处理程序是否已经安装
	NOT1  DB 'Can not repeat the installation! ',0ah, 0dh, 0, '$'
	NOT2  DB  'Input error! ',0ah, 0dh, 0, '$'
	NOT3  DB  'Ready to install ',0ah, 0dh, 0, '$'
;新的INT 08H使用的变量
	COUNT DB 18			;“滴答”计数
	HOUR  DB ?,?,':'	;时的ASCII码
	MIN   DB ?,?,':'	;分的ASCII码
	SEC   DB ?,?		;秒的ASCII码
	BUF_LEN = $ - HOUR	;计算显示信息的长度
	CURSOR  DW ?		;原光标位置
	OLD_INT DW ?,?		;原INT 08H的中断矢量
;新的INT 08H的代码
NEW08H PROC FAR
	PUSHF						;将标志寄存器的内容压栈
	CALL DWORD PTR CS:OLD_INT	;完成原功能(变量在汇编后使用的默认寄存器
								;为DS，故必须加前缀CS:)
	DEC CS:COUNT				;(倒)计时
	JZ DISP						;计满18次，转时钟显示
	IRET						;未计满，中断返回
DISP:
	MOV CS:COUNT,18
	STI							;开中断
	PUSHA						;保护现场
	PUSH DS
	PUSH ES
	MOV AX,CS					;将DS,ES指向CS
	MOV DS,AX
	MOV ES,AX
	CALL GET_TIME				;获取当前时间，并转换成ASCII码
	MOV BH,0					;获取0号显示页面当前的光标位置
	MOV AH,3
	INT 10H
	MOV CURSOR,DX				;保存原光标的位置
	MOV BP,OFFSET HOUR			;ES:[BP]指向显示信息的起始地址
	MOV BH,0					;显示到0号页面
	MOV DH,0					;显示在0行
	MOV DL,80 - BUF_LEN			;显示在最后几列(光标位置设置到右上角)
	MOV BL,07H					;显示字符的属性(白色)
	MOV CX,BUF_LEN				;显示字符串的长度
	MOV AL,0					;BL包含显示属性，写后光标不动
	MOV AH,13H					;调用显示字符串的功能
	INT 10H						;在右上角显示出当前时间
	MOV BH,0					;对0号页面操作
	MOV DX,CURSOR				;恢复原来的光标位置
	MOV AH,2					;设置光标位置的功能号
	INT 10H						;还原光标位置(保证主程序的光标位置不受影响)
	POP ES
	POP DS
	POPA						;恢复现场
	IRET						;中断返回
NEW08H ENDP
;取时间子程序。从RT/CMOS RAM中取得时分秒并转化成ASCII码存放到对应变量中
GET_TIME PROC
	MOV AL,4					;4是“时”信息的偏移地址
	OUT 70H,AL					;设定将要访问的单元是偏移值为4的“时”信息
	JMP $ + 2					;延时，保证端口操作的可靠性
	IN AL,71H					;读取“时”信息
	MOV AH,AL					;将2位压缩的BCD码转换成未压缩的BCD码
	AND AL,0FH
	SHR AH,4
	ADD AX,3030H				;转换成对应的ASCII码
	XCHG AH,AL					;高位放在前面显示
	MOV WORD PTR HOUR,AX		;保存到HOUR变量指示的前2个字节中
	MOV AL,2					;2是“分”信息的偏移地址
	OUT 70H,AL
	JMP $ + 2
	IN AL,71H					;读取“分”信息
	MOV AH,AL					;转换成对应的ACSII码
	AND AL,0FH
	SHR AH,4
	ADD AX,3030H
	XCHG AH,AL
	MOV WORD PTR MIN,AX			;保存到MIN变量指示的前2个字节中
	MOV AL,0					;0是“秒”信息的偏移地址
	OUT 70H,AL
	JMP $ + 2
	IN AL,71H					;读取“秒”信息
	MOV AH,AL					;转换成对应的ASCII码
	AND AL,0FH
	SHR AH,4
	ADD AX,3030H
	XCHG AH,AL
	MOV WORD PTR SEC,AX			;保存到SEC变量指示的2个字节中
	RET
GET_TIME ENDP
;
;初始化(中断处理程序的安装)及主程序
BEGIN:           
	PUSH CS
	POP DS
	MOV AX,3508H				;获取原08H的中断矢量
	INT 21H						;系统功能调用35H的入口/出口参数的规定见附录IV
	;AH=35H						;取中断向量，调用AL=中断类型，返回BX=中断向量
	MOV OLD_INT,BX				;保存中断矢量
	MOV OLD_INT + 2,ES		
	JMP MENU
CHECK:
	MOV AL,FLAG
	CMP AL,1
	JE QUIT_CHECK
	LEA DX,NOT3
	MOV AH,9     ;display
    INT 21H  
INSTALL:
	MOV BYTE PTR FLAG,1
	MOV AX,3508H				;获取原08H的中断矢量
	INT 21H						;系统功能调用35H的入口/出口参数的规定见附录IV
	;AH=35H						;取中断向量，调用AL=中断类型，返回BX=中断向量
	MOV OLD_INT,BX				;保存中断矢量
	MOV OLD_INT + 2,ES	
	MOV DX,OFFSET NEW08H
	MOV AX,2508H				;设置新的08H中断矢量
	INT 21H						;系统功能调用25H的入口/出口参数的规定见附录IV
	;AH=25H						;设置中断向量，DX=中断向量号，AL=中断类型号
MENU:
	LEA DX,hello
	MOV AH,9					;display
    INT 21H   
	MOV AH,0					;等待按键
	INT 16H						;该软中断的入口和出口参数的规定见附录V
	;从键盘读入字符，入口参数AH（00H：读键盘），出口参数AH=键盘的扫描码，AL=字符的ASCII码
	CMP AL,'7'					
	JE CHECK
	CMP AL,'8'					
	JE CHECK
	CMP AL,'9'					;若输入9则退出
	JE QUIT
	LEA DX,NOT2
	MOV AH,9     ;display
    INT 21H
	JMP MENU
QUIT_CHECK:
	LEA DX,NOT1
	MOV AH,9     ;display
    INT 21H   
QUIT:
	LDS DX,DWORD PTR OLD_INT	;取出保存的原08H中断矢量
	MOV AX,2508H
	INT 21H						;恢复原08H中断矢量
	;驻留退出
	MOV DX,OFFSET BEGIN + 15	;计算中断处理程序占用的字节数，+15是为了在计算节数时能向上取整
	MOV CL,4
	SHR DX,CL					;把字节数换成节数(每节代表16个字节)
	ADD DX,10H					;驻留的长度还需包括程序段前缀的内容(100H个字节)
	MOV AL,0					;退出码为0
	MOV AH,31H					;退出时，将(DX)节的主存单元驻留(不释放)
	INT 21H						;退出
CODE ENDS
	END BEGIN