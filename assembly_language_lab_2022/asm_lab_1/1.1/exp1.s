	.file	"exp1.c"
	.text
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%r8, -32(%rbp)
	movq	%r9, -24(%rbp)
	leaq	-40(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rbx
	movl	$1, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rbx, %r8
	movq	-48(%rbp), %rdx
	movq	%rax, %rcx
	call	__mingw_vfprintf
	movl	%eax, -84(%rbp)
	movl	-84(%rbp), %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.globl	password
	.data
	.align 8
password:
	.ascii "0123456789"
	.globl	user_name
	.align 16
user_name:
	.ascii "Hello, U202010755\12\0"
	.globl	input_msg
	.align 16
input_msg:
	.ascii "Iput Your Password: $ \0"
	.globl	password_ok
password_ok:
	.ascii "OK\0"
	.globl	password_err1
	.align 16
password_err1:
	.ascii "Incorrect Password!\0"
	.globl	password_err2
	.align 16
password_err2:
	.ascii "Password Too Long!\0"
	.globl	password_err3
	.align 16
password_err3:
	.ascii "Password Too Short!\0"
	.globl	my_password
	.bss
	.align 8
my_password:
	.space 10
	.globl	len
	.align 4
len:
	.space 4
	.globl	flag
	.align 4
flag:
	.space 4
	.globl	ch
ch:
	.space 1
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "  +  \0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	call	__main
	leaq	user_name(%rip), %rcx
	call	printf
	leaq	input_msg(%rip), %rcx
	call	printf
	jmp	.L4
.L5:
	movl	len(%rip), %edx
	movzbl	ch(%rip), %eax
	movslq	%edx, %rdx
	leaq	my_password(%rip), %rcx
	movb	%al, (%rdx,%rcx)
	movl	len(%rip), %eax
	addl	$1, %eax
	movl	%eax, len(%rip)
.L4:
	call	getchar
	movb	%al, ch(%rip)
	movzbl	ch(%rip), %eax
	cmpb	$10, %al
	jne	.L5
	movl	len(%rip), %eax
	cmpl	$10, %eax
	jne	.L6
	movl	$0, -4(%rbp)
	jmp	.L7
.L10:
	movl	-4(%rbp), %eax
	cltq
	leaq	my_password(%rip), %rdx
	movzbl	(%rax,%rdx), %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	password(%rip), %rcx
	movzbl	(%rax,%rcx), %eax
	cmpb	%al, %dl
	je	.L8
	movl	$1, flag(%rip)
	movl	-4(%rbp), %eax
	cltq
	leaq	my_password(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movsbq	%al, %rcx
	movl	-4(%rbp), %eax
	cltq
	leaq	password(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movsbq	%al, %rax
	leaq	(%rcx,%rax), %rdx
	leaq	.LC0(%rip), %rax
	addq	%rdx, %rax
	movq	%rax, %rcx
	call	printf
	jmp	.L9
.L8:
	addl	$1, -4(%rbp)
.L7:
	cmpl	$9, -4(%rbp)
	jle	.L10
.L9:
	movl	flag(%rip), %eax
	testl	%eax, %eax
	jne	.L11
	leaq	password_ok(%rip), %rcx
	call	printf
	jmp	.L12
.L11:
	leaq	password_err1(%rip), %rcx
	call	printf
	jmp	.L12
.L6:
	movl	len(%rip), %eax
	cmpl	$9, %eax
	jg	.L13
	leaq	password_err3(%rip), %rcx
	call	printf
	jmp	.L12
.L13:
	movl	len(%rip), %eax
	cmpl	$10, %eax
	jle	.L12
	leaq	password_err2(%rip), %rcx
	call	printf
.L12:
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-seh, Built by Guyutongxue) 10.2.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	getchar;	.scl	2;	.type	32;	.endef
