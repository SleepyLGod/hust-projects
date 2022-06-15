
.686P 
.model flat,c
 ExitProcess proto  stdcall :dword
 includelib  kernel32.lib
 includelib  ucrt.lib
 clock    proto
 ;printf      proto c :vararg
 printf      proto c :ptr byte, :vararg
 includelib  libcmt.lib   
 includelib  legacy_stdio_definitions.lib

SAMPLES  STRUCT
  SAMID DB 9 DUP(0)  ;ÿ�����ݵ���ˮ��
  SDA   DD  256809   ;״̬��Ϣa
  SDB   DD  -1023    ;״̬��Ϣb
  SDC   DD   1265    ;״̬��Ϣc
  SF    DD   0       ;������f
SAMPLES  ENDS

N  = 200
.data
  buf  SAMPLES <'202203001',10,20,30,0>
       SAMPLES <'202203002',100,200,300,0>
       SAMPLES <'202203003',1234,456,789,0>
       SAMPLES <'202203004',123,4567,89,0>
       SAMPLES N-4 DUP(<>)
  start_time dd  0    ; ��ʼʱ��
  end_time   dd  0    ; ����ʱ��
  used_time  dd  0    ; ʹ��ʱ��
  prtFmt    db  "%d",0dh,0ah,0
  prompt    db  "hello",0dh, 0ah, 0

.stack 200
.code
main proc  
   invoke  clock
   mov    start_time, eax
   invoke printf,offset prompt
   invoke clock
   mov    end_time, eax
   sub    eax,  start_time
   invoke printf, offset prtFmt, eax
   invoke ExitProcess, 0
main endp
end 