.data
  MessageBoxA proto :DWORD ,:DWORD
  extrn ExitProcess : proc  ;���������ټ������Ƿ�Ϲ棬��ˣ����Բ���PROTO��˵���ⲿ����
  lpContent db  '��ã� 3+6='
  sum       db  0,0
  lpTitle   db  'My first x86-64 Application',0
.code
;mainCRTStartup proc     ;���ǿ���̨�����Ĭ�ϵ�ִ����ڵ�
start proc ;��Ҫ����Ŀ������-����-�߼�����ָ��startΪ��ڵ�,����ᱨmainCRTStartup���ܽ���
   mov  ax,3
   push ax
   mov  ax,6
   push ax
   call  addtwo          ;�Լ���д���ӳ��򣬶�ջ���ݲ���ʱ���������ж���Э��
   add  al,30h
   mov  sum,al
   ;
   sub  rsp, 28h         
   xor  r9d, r9d
   lea  r8,  lpTitle
   lea  rdx, lpContent
   xor  rcx,rcx
   call MessageBoxA     ;����ϵͳ����ʱ���򴫵ݲ���ʱ��Ҫ��ѭ�涨�Ķ�ջ����
   add  rsp,28h
   ;
   sub  rsp, 18h
   mov  rcx,0
   call ExitProcess
start endp
;mainCRTStartup endp
;
;������16λ���ĺ͵��ӳ���
addtwo   proc
    push bx
    mov  ax,[rsp+10]    ; ȡ��ջ���ݹ����Ĳ���
    mov  bx,[rsp+12]
    add  ax,bx
    pop  bx
    ret 4     ;
addtwo  endp
;
end