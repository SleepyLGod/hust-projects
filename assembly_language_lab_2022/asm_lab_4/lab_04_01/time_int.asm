

;  �����ܣ�ÿ��Լ1���� ��ʾһ�ε�ǰ��ʱ�䣨ʱ���֣��룩
;            ����������������������
;        Ϊ�˸��õ�չʾ�������еĳ��򱻴�ϣ�ʱ�����ʾ���ַ�������ʾ������һ��


;  �漰��֪ʶ�㣺
;  (1) 8���ж�
;  (2) ����8���жϵ��жϴ������
;  (3) �жϴ������פ�����ڴ�
;  (4) ��ȡϵͳ��ǰʱ��
;  (5) ����Ļָ��λ����ʾ��
;  �ο����ϣ��̲��и�¼�й��жϵ����� 
;            CMOS���ݵĶ�д��

.386
STACK  SEGMENT  USE16  STACK
       DB  200  DUP (0)
STACK  ENDS

CODE   SEGMENT USE16
       ASSUME CS:CODE, SS:STACK
  COUNT  DB  18
  HOUR   DB  ?, ?, ':'
  MIN    DB  ?, ?, ':'
  SEC    DB  ?, ?
  BUF_LEN = $ - HOUR
  CURSOR   DW  ?
  OLD_INT  DW  ?, ?
  MESSAGE  DB  0dh,0ah,'press any key to return',0dh,0ah,0dh,0ah,'$'
  PROMPT   DB  0DH, 0AH, ' Please select:   ' 
                 DB  0DH, 0AH, '      1:  simple display chars'
                 DB  0DH, 0AH, '      2:  new 8  interrupt,  and restore when return'
                 DB  0DH, 0AH, '      3:  new 8  interrupt,  and resudile when return'
                 DB  0DH, 0AH, '$'
 SELECT_ITEM   DB  0


; -------------------------------------NEW08H----------------------------------------------------
; ����� 8���жϴ������  
NEW08H  PROC  FAR
        PUSHF
        CALL  DWORD  PTR  OLD_INT
        DEC   COUNT
        JZ    DISP
        IRET
  DISP: MOV  COUNT,18
        STI
        PUSHA
        PUSH  DS
        PUSH  ES
        MOV   AX, CS
        MOV   DS, AX
        MOV   ES, AX

        CALL  GET_TIME

        MOV   BH, 0
        MOV   AH, 3
        INT   10H             ; ��ȡ���λ�� (DH,DL)=(�У���)


;      MOV   CURSOR,  DX
;      MOV   DH, 0
;      MOV   DL, 80 - BUF_LEN
 

    MOV   BP,  OFFSET  HOUR
    MOV   BH, 0
    MOV   BL, 07H
    MOV   CX, BUF_LEN
    MOV   AL, 1
    MOV   AH, 13H
    INT   10H

;     MOV   DX, CURSOR
;     ADD    DL, BUF_LEN   ;  �� DL�Ƶ�ʱ����ʾ�Ľ�β��
;     CMP    DL, 80
;     JBE     NEW08_L1
;     INC     DH
;     SUB    DL, 81

        MOV   BH, 0
        MOV   AH, 3
        INT   10H             ; ��ȡ���λ�� (DH,DL)=(�У���)
         
NEW08_L1:    
        MOV    BH, 0
        MOV   AH, 2
        INT    10H

        POP   ES
        POP   DS
        POPA
        IRET
NEW08H  ENDP

; -------------------------------GET_TIME ------------------------------------------------
; ȡʱ��
; �ο����ϣ�CMOS���ݵĶ�д
GET_TIME  PROC
        MOV AL, 4
        OUT 70H, AL
        JMP $+2
        IN  AL, 71H
        MOV AH,AL
        AND AL,0FH
        SHR AH, 4
        ADD AX, 3030H
        XCHG  AH,  AL
        MOV WORD PTR HOUR, AX
        MOV   AL, 2
        OUT   70H, AL
        JMP   $+2
        IN    AL, 71H
        MOV   AH, AL
        AND   AL, 0FH
        SHR   AH, 4
        ADD   AX, 3030H
        XCHG  AH, AL
        MOV   WORD PTR MIN, AX
        MOV   AL, 0
        OUT   70H, AL
        JMP   $+2
        IN    AL,  71H
        MOV   AH,  AL
        AND   AL,  0FH
        SHR   AH,  4
        ADD   AX,  3030H
        XCHG  AH,  AL
        MOV   WORD PTR SEC, AX
        RET
GET_TIME ENDP

; _____________DELAY __________________
; ��ʱ�����
DELAY   PROC
        PUSH  ECX
        MOV   ECX,0
L1:     INC   ECX
        CMP   ECX, 020000H
        JB    L1
        POP   ECX
        RET
DELAY   ENDP


; __________________________________________________________
; ��ȡ������8���жϵĴ��������ڵ�ַ

GET_SET_INTR8_ADDRESS  PROC
         ; ��ȡԭ 8 ���жϵ��жϴ���������ڵ�ַ
        MOV   AX, 3508H
        INT   21H
        MOV   OLD_INT,  BX
        MOV   OLD_INT+2, ES

           ; �����µ� 8���жϵ��жϴ���������ڵ�ַ
        MOV   DX, OFFSET NEW08H
        MOV   AX, 2508H
        INT   21H
        RET
GET_SET_INTR8_ADDRESS  ENDP



RESTORE_INTR8_RETURN    PROC
;        ԭ���ĳ����ǽ��жϴ���������ڵ�ַ��ԭ
         LDS    DX, DWORD PTR OLD_INT
         MOV   AX, 2508H
         INT    21H
         MOV   AH, 4CH
         INT    21H

RESTORE_INTR8_RETURN  ENDP 


RESIDULE_INTR8      PROC
    ;       ���µ��жϴ������פ���ڴ�
        MOV   DX, OFFSET DELAY+14
        MOV   CL, 4
        SHR   DX, CL
        ADD   DX, 10H
        ADD   DX, 70H
        MOV   AL, 0
        MOV   AH, 31H
        INT   21H

RESIDULE_INTR8   ENDP


; -------------------------------------------------------------------------------------------------------
; ������ʼ

BEGIN:   
          ; ��ʾ�����ڴ�����е� MESSAGE���е����ݣ�

        PUSH  CS
        POP   DS

        LEA   DX, PROMPT   ; ��ʾ��ʾ�� PROMPT
        MOV   AH, 9
        INT   21H  
        
        MOV  AH, 1             ; ����ѡ��
        INT   21H

        MOV  SELECT_ITEM, AL


        LEA   DX, MESSAGE    ; ��ʾ��ʾ�� MESSAGE
        MOV   AH, 9
        INT   21H  
 
         
         CMP    SELECT_ITEM,  '1'
         JZ       DISP_CHARS
                                                               ; --------------------------------
         CALL   GET_SET_INTR8_ADDRESS      ;   �����µ��ж�����
                                                               ; --------------------------------       

DISP_CHARS:
        MOV   DL,30H
LOOP_DISP:    
        MOV   AH, 2           ;   ��ʾ�ַ�
        INT    21H
    
        CALL  DELAY           ;  ϣ���ó��������й����У��ܿ��� 8���жϲ����������Ч��
                                     ;   �������������������ʱ���ܣ�����ʾһЩ�ַ���          

         MOV   AH, 0BH       ;   �ж����޻���������������а�����ֹ         
         INT   21H
         CMP   AL, 0   
         JNZ    EXIT

        INC    DL                ;  ׼����һ��Ҫ��ʾ���ַ�
        CMP   DL, 200
        JNZ   CONTINUE
        MOV   DL, 30H

CONTINUE:
        JMP    LOOP_DISP


EXIT:
       CMP  SELECT_ITEM, '1'
       JZ    EXIT1
       CMP  SELECT_ITEM, '3'
       JZ     EXIT3
      
       JMP  EXIT2

EXIT1: 
       MOV  AH,4CH
       INT   21H

EXIT2:
                         ;    ԭ���ĳ����ǽ��жϴ���������ڵ�ַ��ԭ
                         ;    ������ DOS
       CALL    RESTORE_INTR8_RETURN       

EXIT3:
                         ;       ���µ��жϴ������פ���ڴ�, ������ DOS
       CALL    RESIDULE_INTR8 

CODE    ENDS
        END  BEGIN

 