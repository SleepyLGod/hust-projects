#############################################################
#����jal,jalrָ�
#############################################################
.text
 addi s1,zero, 1   #����jal,jalrrָ��
 j jmp_next1       #jal x0,8
 addi s1,zero, 1
 addi s2,zero, 2
 addi s3,zero, 3
jmp_next1:
 j jmp_next2
 addi s1,zero, 1
 addi s2,zero, 2
 addi s3,zero, 3
jmp_next2:
 j jmp_next3
 addi s1,zero, 1
 addi s2,zero, 2
 addi s3,zero, 3
jmp_next3:
 j jmp_next4
 addi s1,zero, 1
 addi s2,zero, 2
 addi s3,zero, 3
jmp_next4:jal jmp_count

#��λ����  ��Ҫ֧�ֳ�addi,sll,add,ecall,srl,sll,sra,beq,j,ecall    revise date:2015/12/16 tiger

.text
addi s0,zero,1     #����λ��ѭ�����ԣ�0��������ʾ���ǳ�ʼֵ1����1λ�ظ�15�ε�ֵ��1���������ۼ�ֵ
addi s1,zero,1  
slli s1, s1, 31   #�߼�����31λ s1=0x80000000
 

###################################################################
#                �߼����Ʋ��� 
# ��ʾ����������ʾ0x80000000 0x20000000 0x08000000 0x02000000 0x00800000 0x00200000 0x00080000 0x00020000 0x00008000 0x00002000 0x00000800 0x00000200 0x00000080 0x00000020 0x00000008 0x00000002 0x00000000  
###################################################################
LogicalRightShift:            #�߼����Ʋ��ԣ������λ1��λ��������ֱ�����Ϊ��

add    a0,zero,s1       #display s1
addi   a7,zero,34        # display hex
ecall                 # we are out of here.  
     
srli s1, s1, 2   
beq s1, zero, shift_next1
j LogicalRightShift

shift_next1:

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


###################################################################
#                �߼����Ʋ��� 
# ��ʾ����������ʾ0x00000004 0x00000010 0x00000040 0x00000100 0x00000400 0x00001000 0x00004000 0x00010000 0x00040000 0x00100000 0x00400000 0x01000000 0x04000000 0x10000000 0x40000000 0x00000000 
###################################################################

addi s1,zero, 1   
LogicalLeftShift:         #�߼����Ʋ��ԣ������λ1��λ������ֱ�����Ϊ��
slli s1, s1, 2  

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  
      
beq s1, zero, ArithRightShift
j LogicalLeftShift


###################################################################
#                �������Ʋ��� 
# ��ʾ����������ʾ0x80000000 0xf0000000 0xff000000 0xfff00000 0xffff0000 0xfffff000 0xffffff00 0xfffffff0 0xffffffff 
###################################################################
ArithRightShift:          #�������Ʋ��ԣ�#������λ���ԣ�80000000�������ƣ�������ʾΪF0000000,FF000000,FFF00000,FFFF0000ֱ��FFFFFFFF

addi s1,zero,1  
slli s1, s1, 31   #�߼�����31λ s1=0x80000000

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  

srai s1, s1, 3    #s1=0X80000000-->0XF0000000

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


srai s1, s1, 4    #0XF0000000-->0XFF000000

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


srai s1, s1, 4    #0XFF000000-->0XFFF00000

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  

srai s1, s1, 4    

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  

srai s1, s1, 4    

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


srai s1, s1, 4    

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


srai s1, s1, 4    

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


srai s1, s1, 4    


add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.    

#############################################################
#����Ʋ���,����addi,andi,sll,srl,sra,or,ori,nor,ecall  LED������Ʒ�ʽ������ʾ����
#############################################################

.text
addi s0,zero,1 
slli s3, s0, 31      # s3=0x80000000
srai s3, s3, 31      # s3=0xFFFFFFFF   
add s0,zero,zero   # s0=0         
addi s2,zero,12 

addi s6,zero,3  #����Ƽ���
zmd_loop:

addi s0, s0, 1    #������һ������Ƶ�����
andi s0, s0, 15  

#######################################
addi t0,zero,8    
addi t1,zero,1
left:

slli s3, s3, 4   #���������
or s3, s3, s0

add    a0,zero,s3       # display s3
addi   a7,zero,34         # system call for LED display 
ecall                 # display 

sub t0,t0,t1
bne t0,zero,left
#######################################

addi s0, s0, 1   #������һ������Ƶ�����
addi t6,zero,15
and s0, s0, t6
slli s0, s0, 28     

addi t0,zero,8
addi t1,zero,1

zmd_right:

srli s3, s3, 4  #���������
or s3, s3, s0

add    a0,zero,s3       # display s3
addi   a7,zero,34         # system call for LED display 
ecall                 # display 

sub t0,t0,t1
bne t0,zero,zmd_right
srli s0, s0, 28  
#######################################

sub s6,s6,t1
beq s6,zero, exit
j zmd_loop

exit:

add t0,zero,zero
xori t0,t0,-1      #test r  xori
slli t0,t0,8
ori t0,t0,255

add   a0,zero,t0       # display t0
addi   a7,zero,34         # system call for LED display 
ecall                 # display 

#################################################################################
#������ʵ��0-15���ֵ�Ԫ�Ľ�������,�˳������rars ������������
#����ʱ�뽫rars Setting�е�Memory Configuration����ΪCompact��data at address 0
#################################################################################
 .text
sort_init:
 addi s0,zero,-1
 addi s1,zero,0
 
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
    sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
   
 addi s0,s0,1
 
 add s0,zero,zero   
 addi s1,zero,60   #��������
sort_loop:
 lw s3,0(s0)     
 lw s4,0(s1)
 slt t0,s3,s4
 beq t0,zero,sort_next   #��������
 sw s3, 0(s1)
 sw s4, 0(s0)   
sort_next:
 addi s1, s1, -4   
 bne s0, s1, sort_loop  
 
 add    a0,zero,s0       #display s0
 addi   a7,zero,34         # display hex
 ecall                 # we are out of here.  DISP: disp r0, 0
 
 addi s0,s0,4
 addi s1,zero,60
 bne s0, s1, sort_loop


 #addi   a7,zero,50         # system call for pause
 #ecall                  # we are out of here.   
 
 
#############################################
# insert your ccmb benchmark program here!!!
#############################################

#j benchmark_start       #delete this instruction for ccmb bencmark
#C1 instruction benchmark



#C2 instruction benchmark



#Mem instruction benchmark




#Branch instruction benchmark


                 
 addi   a7,zero,10         # system call for exit
 ecall                  # we are out of here.   
 
 #������ʵ��������ͣ��ָ��ʵ��ecall

jmp_count: addi s0,zero, 0
       addi s0,s0, 1
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  
       
       addi s0,s0, 2
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  
       
       addi s0,s0, 3
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  
       
       addi s0,s0, 4       
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  
       
       addi s0,s0, 5              
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  

       addi s0,s0, 6              
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  

       addi s0,s0, 7              
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  

       addi s0,s0, 8              
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       addi   a7,zero,34         # display hex       
       ecall                 # we are out of here.  
       
       ret  #persudo instruction  jalr x0,x1,0
