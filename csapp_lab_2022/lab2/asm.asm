
./bomb:     file format elf32-i386


Disassembly of section .init:

080486f4 <_init>:
 80486f4:	53                   	push   %ebx
 80486f5:	83 ec 08             	sub    $0x8,%esp
 80486f8:	e8 13 02 00 00       	call   8048910 <__x86.get_pc_thunk.bx>
 80486fd:	81 c3 03 39 00 00    	add    $0x3903,%ebx
 8048703:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 8048709:	85 c0                	test   %eax,%eax
 804870b:	74 05                	je     8048712 <_init+0x1e>
 804870d:	e8 be 01 00 00       	call   80488d0 <__gmon_start__@plt>
 8048712:	83 c4 08             	add    $0x8,%esp
 8048715:	5b                   	pop    %ebx
 8048716:	c3                   	ret    

Disassembly of section .plt:

08048720 <.plt>:
 8048720:	ff 35 04 c0 04 08    	pushl  0x804c004
 8048726:	ff 25 08 c0 04 08    	jmp    *0x804c008
 804872c:	00 00                	add    %al,(%eax)
	...

08048730 <read@plt>:
 8048730:	ff 25 0c c0 04 08    	jmp    *0x804c00c
 8048736:	68 00 00 00 00       	push   $0x0
 804873b:	e9 e0 ff ff ff       	jmp    8048720 <.plt>

08048740 <fflush@plt>:
 8048740:	ff 25 10 c0 04 08    	jmp    *0x804c010
 8048746:	68 08 00 00 00       	push   $0x8
 804874b:	e9 d0 ff ff ff       	jmp    8048720 <.plt>

08048750 <fgets@plt>:
 8048750:	ff 25 14 c0 04 08    	jmp    *0x804c014
 8048756:	68 10 00 00 00       	push   $0x10
 804875b:	e9 c0 ff ff ff       	jmp    8048720 <.plt>

08048760 <signal@plt>:
 8048760:	ff 25 18 c0 04 08    	jmp    *0x804c018
 8048766:	68 18 00 00 00       	push   $0x18
 804876b:	e9 b0 ff ff ff       	jmp    8048720 <.plt>

08048770 <sleep@plt>:
 8048770:	ff 25 1c c0 04 08    	jmp    *0x804c01c
 8048776:	68 20 00 00 00       	push   $0x20
 804877b:	e9 a0 ff ff ff       	jmp    8048720 <.plt>

08048780 <alarm@plt>:
 8048780:	ff 25 20 c0 04 08    	jmp    *0x804c020
 8048786:	68 28 00 00 00       	push   $0x28
 804878b:	e9 90 ff ff ff       	jmp    8048720 <.plt>

08048790 <__stack_chk_fail@plt>:
 8048790:	ff 25 24 c0 04 08    	jmp    *0x804c024
 8048796:	68 30 00 00 00       	push   $0x30
 804879b:	e9 80 ff ff ff       	jmp    8048720 <.plt>

080487a0 <strcpy@plt>:
 80487a0:	ff 25 28 c0 04 08    	jmp    *0x804c028
 80487a6:	68 38 00 00 00       	push   $0x38
 80487ab:	e9 70 ff ff ff       	jmp    8048720 <.plt>

080487b0 <getenv@plt>:
 80487b0:	ff 25 2c c0 04 08    	jmp    *0x804c02c
 80487b6:	68 40 00 00 00       	push   $0x40
 80487bb:	e9 60 ff ff ff       	jmp    8048720 <.plt>

080487c0 <puts@plt>:
 80487c0:	ff 25 30 c0 04 08    	jmp    *0x804c030
 80487c6:	68 48 00 00 00       	push   $0x48
 80487cb:	e9 50 ff ff ff       	jmp    8048720 <.plt>

080487d0 <__memmove_chk@plt>:
 80487d0:	ff 25 34 c0 04 08    	jmp    *0x804c034
 80487d6:	68 50 00 00 00       	push   $0x50
 80487db:	e9 40 ff ff ff       	jmp    8048720 <.plt>

080487e0 <exit@plt>:
 80487e0:	ff 25 38 c0 04 08    	jmp    *0x804c038
 80487e6:	68 58 00 00 00       	push   $0x58
 80487eb:	e9 30 ff ff ff       	jmp    8048720 <.plt>

080487f0 <__libc_start_main@plt>:
 80487f0:	ff 25 3c c0 04 08    	jmp    *0x804c03c
 80487f6:	68 60 00 00 00       	push   $0x60
 80487fb:	e9 20 ff ff ff       	jmp    8048720 <.plt>

08048800 <write@plt>:
 8048800:	ff 25 40 c0 04 08    	jmp    *0x804c040
 8048806:	68 68 00 00 00       	push   $0x68
 804880b:	e9 10 ff ff ff       	jmp    8048720 <.plt>

08048810 <__isoc99_sscanf@plt>:
 8048810:	ff 25 44 c0 04 08    	jmp    *0x804c044
 8048816:	68 70 00 00 00       	push   $0x70
 804881b:	e9 00 ff ff ff       	jmp    8048720 <.plt>

08048820 <fopen@plt>:
 8048820:	ff 25 48 c0 04 08    	jmp    *0x804c048
 8048826:	68 78 00 00 00       	push   $0x78
 804882b:	e9 f0 fe ff ff       	jmp    8048720 <.plt>

08048830 <__errno_location@plt>:
 8048830:	ff 25 4c c0 04 08    	jmp    *0x804c04c
 8048836:	68 80 00 00 00       	push   $0x80
 804883b:	e9 e0 fe ff ff       	jmp    8048720 <.plt>

08048840 <__printf_chk@plt>:
 8048840:	ff 25 50 c0 04 08    	jmp    *0x804c050
 8048846:	68 88 00 00 00       	push   $0x88
 804884b:	e9 d0 fe ff ff       	jmp    8048720 <.plt>

08048850 <socket@plt>:
 8048850:	ff 25 54 c0 04 08    	jmp    *0x804c054
 8048856:	68 90 00 00 00       	push   $0x90
 804885b:	e9 c0 fe ff ff       	jmp    8048720 <.plt>

08048860 <__fprintf_chk@plt>:
 8048860:	ff 25 58 c0 04 08    	jmp    *0x804c058
 8048866:	68 98 00 00 00       	push   $0x98
 804886b:	e9 b0 fe ff ff       	jmp    8048720 <.plt>

08048870 <gethostbyname@plt>:
 8048870:	ff 25 5c c0 04 08    	jmp    *0x804c05c
 8048876:	68 a0 00 00 00       	push   $0xa0
 804887b:	e9 a0 fe ff ff       	jmp    8048720 <.plt>

08048880 <strtol@plt>:
 8048880:	ff 25 60 c0 04 08    	jmp    *0x804c060
 8048886:	68 a8 00 00 00       	push   $0xa8
 804888b:	e9 90 fe ff ff       	jmp    8048720 <.plt>

08048890 <connect@plt>:
 8048890:	ff 25 64 c0 04 08    	jmp    *0x804c064
 8048896:	68 b0 00 00 00       	push   $0xb0
 804889b:	e9 80 fe ff ff       	jmp    8048720 <.plt>

080488a0 <close@plt>:
 80488a0:	ff 25 68 c0 04 08    	jmp    *0x804c068
 80488a6:	68 b8 00 00 00       	push   $0xb8
 80488ab:	e9 70 fe ff ff       	jmp    8048720 <.plt>

080488b0 <__ctype_b_loc@plt>:
 80488b0:	ff 25 6c c0 04 08    	jmp    *0x804c06c
 80488b6:	68 c0 00 00 00       	push   $0xc0
 80488bb:	e9 60 fe ff ff       	jmp    8048720 <.plt>

080488c0 <__sprintf_chk@plt>:
 80488c0:	ff 25 70 c0 04 08    	jmp    *0x804c070
 80488c6:	68 c8 00 00 00       	push   $0xc8
 80488cb:	e9 50 fe ff ff       	jmp    8048720 <.plt>

Disassembly of section .plt.got:

080488d0 <__gmon_start__@plt>:
 80488d0:	ff 25 fc bf 04 08    	jmp    *0x804bffc
 80488d6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

080488e0 <_start>:
 80488e0:	31 ed                	xor    %ebp,%ebp
 80488e2:	5e                   	pop    %esi
 80488e3:	89 e1                	mov    %esp,%ecx
 80488e5:	83 e4 f0             	and    $0xfffffff0,%esp
 80488e8:	50                   	push   %eax
 80488e9:	54                   	push   %esp
 80488ea:	52                   	push   %edx
 80488eb:	68 90 9e 04 08       	push   $0x8049e90
 80488f0:	68 30 9e 04 08       	push   $0x8049e30
 80488f5:	51                   	push   %ecx
 80488f6:	56                   	push   %esi
 80488f7:	68 db 89 04 08       	push   $0x80489db
 80488fc:	e8 ef fe ff ff       	call   80487f0 <__libc_start_main@plt>
 8048901:	f4                   	hlt    
 8048902:	66 90                	xchg   %ax,%ax
 8048904:	66 90                	xchg   %ax,%ax
 8048906:	66 90                	xchg   %ax,%ax
 8048908:	66 90                	xchg   %ax,%ax
 804890a:	66 90                	xchg   %ax,%ax
 804890c:	66 90                	xchg   %ax,%ax
 804890e:	66 90                	xchg   %ax,%ax

08048910 <__x86.get_pc_thunk.bx>:
 8048910:	8b 1c 24             	mov    (%esp),%ebx
 8048913:	c3                   	ret    
 8048914:	66 90                	xchg   %ax,%ax
 8048916:	66 90                	xchg   %ax,%ax
 8048918:	66 90                	xchg   %ax,%ax
 804891a:	66 90                	xchg   %ax,%ax
 804891c:	66 90                	xchg   %ax,%ax
 804891e:	66 90                	xchg   %ax,%ax

08048920 <deregister_tm_clones>:
 8048920:	b8 a3 c3 04 08       	mov    $0x804c3a3,%eax
 8048925:	2d a0 c3 04 08       	sub    $0x804c3a0,%eax
 804892a:	83 f8 06             	cmp    $0x6,%eax
 804892d:	76 1a                	jbe    8048949 <deregister_tm_clones+0x29>
 804892f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048934:	85 c0                	test   %eax,%eax
 8048936:	74 11                	je     8048949 <deregister_tm_clones+0x29>
 8048938:	55                   	push   %ebp
 8048939:	89 e5                	mov    %esp,%ebp
 804893b:	83 ec 14             	sub    $0x14,%esp
 804893e:	68 a0 c3 04 08       	push   $0x804c3a0
 8048943:	ff d0                	call   *%eax
 8048945:	83 c4 10             	add    $0x10,%esp
 8048948:	c9                   	leave  
 8048949:	f3 c3                	repz ret 
 804894b:	90                   	nop
 804894c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

08048950 <register_tm_clones>:
 8048950:	b8 a0 c3 04 08       	mov    $0x804c3a0,%eax
 8048955:	2d a0 c3 04 08       	sub    $0x804c3a0,%eax
 804895a:	c1 f8 02             	sar    $0x2,%eax
 804895d:	89 c2                	mov    %eax,%edx
 804895f:	c1 ea 1f             	shr    $0x1f,%edx
 8048962:	01 d0                	add    %edx,%eax
 8048964:	d1 f8                	sar    %eax
 8048966:	74 1b                	je     8048983 <register_tm_clones+0x33>
 8048968:	ba 00 00 00 00       	mov    $0x0,%edx
 804896d:	85 d2                	test   %edx,%edx
 804896f:	74 12                	je     8048983 <register_tm_clones+0x33>
 8048971:	55                   	push   %ebp
 8048972:	89 e5                	mov    %esp,%ebp
 8048974:	83 ec 10             	sub    $0x10,%esp
 8048977:	50                   	push   %eax
 8048978:	68 a0 c3 04 08       	push   $0x804c3a0
 804897d:	ff d2                	call   *%edx
 804897f:	83 c4 10             	add    $0x10,%esp
 8048982:	c9                   	leave  
 8048983:	f3 c3                	repz ret 
 8048985:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048989:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048990 <__do_global_dtors_aux>:
 8048990:	80 3d c8 c3 04 08 00 	cmpb   $0x0,0x804c3c8
 8048997:	75 13                	jne    80489ac <__do_global_dtors_aux+0x1c>
 8048999:	55                   	push   %ebp
 804899a:	89 e5                	mov    %esp,%ebp
 804899c:	83 ec 08             	sub    $0x8,%esp
 804899f:	e8 7c ff ff ff       	call   8048920 <deregister_tm_clones>
 80489a4:	c6 05 c8 c3 04 08 01 	movb   $0x1,0x804c3c8
 80489ab:	c9                   	leave  
 80489ac:	f3 c3                	repz ret 
 80489ae:	66 90                	xchg   %ax,%ax

080489b0 <frame_dummy>:
 80489b0:	b8 10 bf 04 08       	mov    $0x804bf10,%eax
 80489b5:	8b 10                	mov    (%eax),%edx
 80489b7:	85 d2                	test   %edx,%edx
 80489b9:	75 05                	jne    80489c0 <frame_dummy+0x10>
 80489bb:	eb 93                	jmp    8048950 <register_tm_clones>
 80489bd:	8d 76 00             	lea    0x0(%esi),%esi
 80489c0:	ba 00 00 00 00       	mov    $0x0,%edx
 80489c5:	85 d2                	test   %edx,%edx
 80489c7:	74 f2                	je     80489bb <frame_dummy+0xb>
 80489c9:	55                   	push   %ebp
 80489ca:	89 e5                	mov    %esp,%ebp
 80489cc:	83 ec 14             	sub    $0x14,%esp
 80489cf:	50                   	push   %eax
 80489d0:	ff d2                	call   *%edx
 80489d2:	83 c4 10             	add    $0x10,%esp
 80489d5:	c9                   	leave  
 80489d6:	e9 75 ff ff ff       	jmp    8048950 <register_tm_clones>

080489db <main>:
 80489db:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 80489df:	83 e4 f0             	and    $0xfffffff0,%esp
 80489e2:	ff 71 fc             	pushl  -0x4(%ecx)
 80489e5:	55                   	push   %ebp
 80489e6:	89 e5                	mov    %esp,%ebp
 80489e8:	53                   	push   %ebx
 80489e9:	51                   	push   %ecx
 80489ea:	8b 01                	mov    (%ecx),%eax
 80489ec:	8b 59 04             	mov    0x4(%ecx),%ebx
 80489ef:	83 f8 01             	cmp    $0x1,%eax
 80489f2:	75 0c                	jne    8048a00 <main+0x25>
 80489f4:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 80489f9:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 80489fe:	eb 5b                	jmp    8048a5b <main+0x80>
 8048a00:	83 f8 02             	cmp    $0x2,%eax
 8048a03:	75 39                	jne    8048a3e <main+0x63>
 8048a05:	83 ec 08             	sub    $0x8,%esp
 8048a08:	68 c8 9e 04 08       	push   $0x8049ec8
 8048a0d:	ff 73 04             	pushl  0x4(%ebx)
 8048a10:	e8 0b fe ff ff       	call   8048820 <fopen@plt>
 8048a15:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 8048a1a:	83 c4 10             	add    $0x10,%esp
 8048a1d:	85 c0                	test   %eax,%eax
 8048a1f:	75 3a                	jne    8048a5b <main+0x80>
 8048a21:	ff 73 04             	pushl  0x4(%ebx)
 8048a24:	ff 33                	pushl  (%ebx)
 8048a26:	68 ca 9e 04 08       	push   $0x8049eca
 8048a2b:	6a 01                	push   $0x1
 8048a2d:	e8 0e fe ff ff       	call   8048840 <__printf_chk@plt>
 8048a32:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048a39:	e8 a2 fd ff ff       	call   80487e0 <exit@plt>
 8048a3e:	83 ec 04             	sub    $0x4,%esp
 8048a41:	ff 33                	pushl  (%ebx)
 8048a43:	68 e7 9e 04 08       	push   $0x8049ee7
 8048a48:	6a 01                	push   $0x1
 8048a4a:	e8 f1 fd ff ff       	call   8048840 <__printf_chk@plt>
 8048a4f:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048a56:	e8 85 fd ff ff       	call   80487e0 <exit@plt>
 8048a5b:	e8 f7 05 00 00       	call   8049057 <initialize_bomb>
 8048a60:	83 ec 0c             	sub    $0xc,%esp
 8048a63:	68 4c 9f 04 08       	push   $0x8049f4c
 8048a68:	e8 53 fd ff ff       	call   80487c0 <puts@plt>
 8048a6d:	c7 04 24 88 9f 04 08 	movl   $0x8049f88,(%esp)
 8048a74:	e8 47 fd ff ff       	call   80487c0 <puts@plt>
 8048a79:	e8 cb 06 00 00       	call   8049149 <read_line>
 8048a7e:	89 04 24             	mov    %eax,(%esp)
 8048a81:	e8 ad 00 00 00       	call   8048b33 <phase_1>
 8048a86:	e8 b7 07 00 00       	call   8049242 <phase_defused>
 8048a8b:	c7 04 24 b4 9f 04 08 	movl   $0x8049fb4,(%esp)
 8048a92:	e8 29 fd ff ff       	call   80487c0 <puts@plt>
 8048a97:	e8 ad 06 00 00       	call   8049149 <read_line>
 8048a9c:	89 04 24             	mov    %eax,(%esp)
 8048a9f:	e8 b0 00 00 00       	call   8048b54 <phase_2>
 8048aa4:	e8 99 07 00 00       	call   8049242 <phase_defused>
 8048aa9:	c7 04 24 01 9f 04 08 	movl   $0x8049f01,(%esp)
 8048ab0:	e8 0b fd ff ff       	call   80487c0 <puts@plt>
 8048ab5:	e8 8f 06 00 00       	call   8049149 <read_line>
 8048aba:	89 04 24             	mov    %eax,(%esp)
 8048abd:	e8 fd 00 00 00       	call   8048bbf <phase_3>
 8048ac2:	e8 7b 07 00 00       	call   8049242 <phase_defused>
 8048ac7:	c7 04 24 1f 9f 04 08 	movl   $0x8049f1f,(%esp)
 8048ace:	e8 ed fc ff ff       	call   80487c0 <puts@plt>
 8048ad3:	e8 71 06 00 00       	call   8049149 <read_line>
 8048ad8:	89 04 24             	mov    %eax,(%esp)
 8048adb:	e8 10 02 00 00       	call   8048cf0 <phase_4>
 8048ae0:	e8 5d 07 00 00       	call   8049242 <phase_defused>
 8048ae5:	c7 04 24 e0 9f 04 08 	movl   $0x8049fe0,(%esp)
 8048aec:	e8 cf fc ff ff       	call   80487c0 <puts@plt>
 8048af1:	e8 53 06 00 00       	call   8049149 <read_line>
 8048af6:	89 04 24             	mov    %eax,(%esp)
 8048af9:	e8 67 02 00 00       	call   8048d65 <phase_5>
 8048afe:	e8 3f 07 00 00       	call   8049242 <phase_defused>
 8048b03:	c7 04 24 2e 9f 04 08 	movl   $0x8049f2e,(%esp)
 8048b0a:	e8 b1 fc ff ff       	call   80487c0 <puts@plt>
 8048b0f:	e8 35 06 00 00       	call   8049149 <read_line>
 8048b14:	89 04 24             	mov    %eax,(%esp)
 8048b17:	e8 91 02 00 00       	call   8048dad <phase_6>
 8048b1c:	e8 21 07 00 00       	call   8049242 <phase_defused>
 8048b21:	83 c4 10             	add    $0x10,%esp
 8048b24:	b8 00 00 00 00       	mov    $0x0,%eax
 8048b29:	8d 65 f8             	lea    -0x8(%ebp),%esp
 8048b2c:	59                   	pop    %ecx
 8048b2d:	5b                   	pop    %ebx
 8048b2e:	5d                   	pop    %ebp
 8048b2f:	8d 61 fc             	lea    -0x4(%ecx),%esp
 8048b32:	c3                   	ret    

08048b33 <phase_1>:
 8048b33:	83 ec 14             	sub    $0x14,%esp 
 8048b36:	68 04 a0 04 08       	push   $0x804a004
 8048b3b:	ff 74 24 1c          	pushl  0x1c(%esp)
 8048b3f:	e8 ae 04 00 00       	call   8048ff2 <strings_not_equal>
 8048b44:	83 c4 10             	add    $0x10,%esp
 8048b47:	85 c0                	test   %eax,%eax
 8048b49:	74 05                	je     8048b50 <phase_1+0x1d>
 8048b4b:	e8 99 05 00 00       	call   80490e9 <explode_bomb>
 8048b50:	83 c4 0c             	add    $0xc,%esp
 8048b53:	c3                   	ret    

08048b54 <phase_2>:
 8048b54:	56                   	push   %esi
 8048b55:	53                   	push   %ebx
 8048b56:	83 ec 2c             	sub    $0x2c,%esp
 # parameters:
 8048b59:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048b5f:	89 44 24 24          	mov    %eax,0x24(%esp)
 8048b63:	31 c0                	xor    %eax,%eax
 8048b65:	8d 44 24 0c          	lea    0xc(%esp),%eax
 8048b69:	50                   	push   %eax
 8048b6a:	ff 74 24 3c          	pushl  0x3c(%esp)
 # input:
 8048b6e:	e8 9b 05 00 00       	call   804910e <read_six_numbers>
 8048b73:	83 c4 10             	add    $0x10,%esp
 # cmp:
 8048b76:	83 7c 24 04 00       	cmpl   $0x0,0x4(%esp) # 1:0
 8048b7b:	75 07                	jne    8048b84 <phase_2+0x30> # explode_bomb
 8048b7d:	83 7c 24 08 01       	cmpl   $0x1,0x8(%esp) # 2:1
 8048b82:	74 05                	je     8048b89 <phase_2+0x35>  # 8048b96:
 8048b84:	e8 60 05 00 00       	call   80490e9 <explode_bomb>
 8048b89:	8d 5c 24 04          	lea    0x4(%esp),%ebx # the 1st
 8048b8d:	8d 74 24 14          	lea    0x14(%esp),%esi # the 5th
 # loop:
 8048b91:	8b 43 04             	mov    0x4(%ebx),%eax # eax:value(ebx->next)
 8048b94:	03 03                	add    (%ebx),%eax # %eax += prev value
 8048b96:	39 43 08             	cmp    %eax,0x8(%ebx) # ebx->next->next
 8048b99:	74 05                	je     8048ba0 <phase_2+0x4c> # 8048ba0: %ebx + 4
 8048b9b:	e8 49 05 00 00       	call   80490e9 <explode_bomb>
 8048ba0:	83 c3 04             	add    $0x4,%ebx # the 2nd
 8048ba3:	39 f3                	cmp    %esi,%ebx # 5th & 2nd
 8048ba5:	75 ea                	jne    8048b91 <phase_2+0x3d> # 8048b91: loop
 # loop end
 8048ba7:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 8048bab:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048bb2:	74 05                	je     8048bb9 <phase_2+0x65> # 8048bb9:exit
 8048bb4:	e8 d7 fb ff ff       	call   8048790 <__stack_chk_fail@plt>
 8048bb9:	83 c4 24             	add    $0x24,%esp
 8048bbc:	5b                   	pop    %ebx
 8048bbd:	5e                   	pop    %esi
 8048bbe:	c3                   	ret    

08048bbf <phase_3>:
 8048bbf:	83 ec 1c             	sub    $0x1c,%esp
 # parqmeters:
 8048bc2:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048bc8:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048bcc:	31 c0                	xor    %eax,%eax
 8048bce:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048bd2:	50                   	push   %eax
 8048bd3:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048bd7:	50                   	push   %eax
 8048bd8:	68 cf a1 04 08       	push   $0x804a1cf # the 2nd para
 8048bdd:	ff 74 24 2c          	pushl  0x2c(%esp)
 # __isoc99_sscanf
 8048be1:	e8 2a fc ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8048be6:	83 c4 10             	add    $0x10,%esp
 8048be9:	83 f8 01             	cmp    $0x1,%eax
 8048bec:	7f 05                	jg     8048bf3 <phase_3+0x34>
 8048bee:	e8 f6 04 00 00       	call   80490e9 <explode_bomb>
 # cmp with 7 (<=)
 8048bf3:	83 7c 24 04 07       	cmpl   $0x7,0x4(%esp)
 8048bf8:	77 66                	ja     8048c60 <phase_3+0xa1> # explode_bomb
 # break point:
 8048bfa:	8b 44 24 04          	mov    0x4(%esp),%eax
 8048bfe:	ff 24 85 60 a0 04 08 	jmp    *0x804a060(,%eax,4)
 8048c05:	b8 c6 02 00 00       	mov    $0x2c6,%eax
 8048c0a:	eb 05                	jmp    8048c11 <phase_3+0x52>
 8048c0c:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c11:	2d d4 01 00 00       	sub    $0x1d4,%eax
 8048c16:	eb 05                	jmp    8048c1d <phase_3+0x5e>
 8048c18:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c1d:	05 4b 01 00 00       	add    $0x14b,%eax
 8048c22:	eb 05                	jmp    8048c29 <phase_3+0x6a>
 8048c24:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c29:	2d e5 01 00 00       	sub    $0x1e5,%eax
 8048c2e:	eb 05                	jmp    8048c35 <phase_3+0x76>
 8048c30:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c35:	05 e5 01 00 00       	add    $0x1e5,%eax
 8048c3a:	eb 05                	jmp    8048c41 <phase_3+0x82>
 8048c3c:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c41:	2d e5 01 00 00       	sub    $0x1e5,%eax
 8048c46:	eb 05                	jmp    8048c4d <phase_3+0x8e>
 8048c48:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c4d:	05 e5 01 00 00       	add    $0x1e5,%eax
 8048c52:	eb 05                	jmp    8048c59 <phase_3+0x9a>
 8048c54:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c59:	2d e5 01 00 00       	sub    $0x1e5,%eax
 8048c5e:	eb 0a                	jmp    8048c6a <phase_3+0xab>
 8048c60:	e8 84 04 00 00       	call   80490e9 <explode_bomb>
 8048c65:	b8 00 00 00 00       	mov    $0x0,%eax
 # attention:
 8048c6a:	83 7c 24 04 05       	cmpl   $0x5,0x4(%esp)
 8048c6f:	7f 06                	jg     8048c77 <phase_3+0xb8>
 8048c71:	3b 44 24 08          	cmp    0x8(%esp),%eax
 8048c75:	74 05                	je     8048c7c <phase_3+0xbd>
 8048c77:	e8 6d 04 00 00       	call   80490e9 <explode_bomb>
 8048c7c:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048c80:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048c87:	74 05                	je     8048c8e <phase_3+0xcf>
 8048c89:	e8 02 fb ff ff       	call   8048790 <__stack_chk_fail@plt>
 8048c8e:	83 c4 1c             	add    $0x1c,%esp
 8048c91:	c3                   	ret    

08048c92 <func4>:
 8048c92:	56                   	push   %esi
 8048c93:	53                   	push   %ebx
 8048c94:	83 ec 04             	sub    $0x4,%esp
 8048c97:	8b 4c 24 10          	mov    0x10(%esp),%ecx
 8048c9b:	8b 5c 24 14          	mov    0x14(%esp),%ebx
 8048c9f:	8b 74 24 18          	mov    0x18(%esp),%esi
 8048ca3:	89 f0                	mov    %esi,%eax
 8048ca5:	29 d8                	sub    %ebx,%eax
 8048ca7:	89 c2                	mov    %eax,%edx
 8048ca9:	c1 ea 1f             	shr    $0x1f,%edx
 8048cac:	01 d0                	add    %edx,%eax
 8048cae:	d1 f8                	sar    %eax
 8048cb0:	8d 14 18             	lea    (%eax,%ebx,1),%edx
 8048cb3:	39 ca                	cmp    %ecx,%edx
 8048cb5:	7e 15                	jle    8048ccc <func4+0x3a>
 8048cb7:	83 ec 04             	sub    $0x4,%esp
 8048cba:	83 ea 01             	sub    $0x1,%edx
 8048cbd:	52                   	push   %edx
 8048cbe:	53                   	push   %ebx
 8048cbf:	51                   	push   %ecx
 8048cc0:	e8 cd ff ff ff       	call   8048c92 <func4>
 8048cc5:	83 c4 10             	add    $0x10,%esp
 8048cc8:	01 c0                	add    %eax,%eax
 8048cca:	eb 1e                	jmp    8048cea <func4+0x58>
 8048ccc:	b8 00 00 00 00       	mov    $0x0,%eax
 8048cd1:	39 ca                	cmp    %ecx,%edx
 8048cd3:	7d 15                	jge    8048cea <func4+0x58>
 8048cd5:	83 ec 04             	sub    $0x4,%esp
 8048cd8:	56                   	push   %esi
 8048cd9:	83 c2 01             	add    $0x1,%edx
 8048cdc:	52                   	push   %edx
 8048cdd:	51                   	push   %ecx
 8048cde:	e8 af ff ff ff       	call   8048c92 <func4>
 8048ce3:	83 c4 10             	add    $0x10,%esp
 8048ce6:	8d 44 00 01          	lea    0x1(%eax,%eax,1),%eax
 8048cea:	83 c4 04             	add    $0x4,%esp
 8048ced:	5b                   	pop    %ebx
 8048cee:	5e                   	pop    %esi
 8048cef:	c3                   	ret    

08048cf0 <phase_4>:
 8048cf0:	83 ec 1c             	sub    $0x1c,%esp
 # parameter:
 8048cf3:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048cf9:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048cfd:	31 c0                	xor    %eax,%eax
 8048cff:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048d03:	50                   	push   %eax
 8048d04:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048d08:	50                   	push   %eax
 8048d09:	68 cf a1 04 08       	push   $0x804a1cf
 8048d0e:	ff 74 24 2c          	pushl  0x2c(%esp)
 # read in:
 8048d12:	e8 f9 fa ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8048d17:	83 c4 10             	add    $0x10,%esp
 8048d1a:	83 f8 02             	cmp    $0x2,%eax # 2 parameters
 8048d1d:	75 07                	jne    8048d26 <phase_4+0x36> # explode_bomb
 8048d1f:	83 7c 24 04 0e       	cmpl   $0xe,0x4(%esp)
 8048d24:	76 05                	jbe    8048d2b <phase_4+0x3b>
 8048d26:	e8 be 03 00 00       	call   80490e9 <explode_bomb>
 # parameters:
 8048d2b:	83 ec 04             	sub    $0x4,%esp
 8048d2e:	6a 0e                	push   $0xe
 8048d30:	6a 00                	push   $0x0
 8048d32:	ff 74 24 10          	pushl  0x10(%esp)
 # func4:
 8048d36:	e8 57 ff ff ff       	call   8048c92 <func4>
 8048d3b:	83 c4 10             	add    $0x10,%esp
 8048d3e:	83 f8 04             	cmp    $0x4,%eax
 8048d41:	75 07                	jne    8048d4a <phase_4+0x5a>
 8048d43:	83 7c 24 08 04       	cmpl   $0x4,0x8(%esp)
 8048d48:	74 05                	je     8048d4f <phase_4+0x5f>
 8048d4a:	e8 9a 03 00 00       	call   80490e9 <explode_bomb>
 8048d4f:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048d53:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048d5a:	74 05                	je     8048d61 <phase_4+0x71>
 8048d5c:	e8 2f fa ff ff       	call   8048790 <__stack_chk_fail@plt>
 8048d61:	83 c4 1c             	add    $0x1c,%esp
 8048d64:	c3                   	ret    

08048d65 <phase_5>:
 8048d65:	53                   	push   %ebx
 8048d66:	83 ec 14             	sub    $0x14,%esp
 8048d69:	8b 5c 24 1c          	mov    0x1c(%esp),%ebx
 8048d6d:	53                   	push   %ebx
 8048d6e:	e8 60 02 00 00       	call   8048fd3 <string_length>
 8048d73:	83 c4 10             	add    $0x10,%esp
 8048d76:	83 f8 06             	cmp    $0x6,%eax # length == 6
 8048d79:	74 05                	je     8048d80 <phase_5+0x1b>
 8048d7b:	e8 69 03 00 00       	call   80490e9 <explode_bomb>
 8048d80:	89 d8                	mov    %ebx,%eax 
 8048d82:	83 c3 06             	add    $0x6,%ebx # length = 6
 8048d85:	b9 00 00 00 00       	mov    $0x0,%ecx # (%ecx) = 0
 # loop:
 8048d8a:	0f b6 10             	movzbl (%eax),%edx 
 8048d8d:	83 e2 0f             	and    $0xf,%edx # (%edx): 0~15
 8048d90:	03 0c 95 80 a0 04 08 	add    0x804a080(,%edx,4),%ecx
 8048d97:	83 c0 01             	add    $0x1,%eax
 8048d9a:	39 d8                	cmp    %ebx,%eax
 8048d9c:	75 ec                	jne    8048d8a <phase_5+0x25>
 # loop end
 8048d9e:	83 f9 3a             	cmp    $0x3a,%ecx # ecx = 58 √
 8048da1:	74 05                	je     8048da8 <phase_5+0x43>
 8048da3:	e8 41 03 00 00       	call   80490e9 <explode_bomb>
 8048da8:	83 c4 08             	add    $0x8,%esp
 8048dab:	5b                   	pop    %ebx
 8048dac:	c3                   	ret    

08048dad <phase_6>:
 # ----------------------------- part1 ---------------------------------
 8048dad:	56                   	push   %esi
 8048dae:	53                   	push   %ebx
 8048daf:	83 ec 4c             	sub    $0x4c,%esp
 8048db2:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048db8:	89 44 24 44          	mov    %eax,0x44(%esp)
 8048dbc:	31 c0                	xor    %eax,%eax
 8048dbe:	8d 44 24 14          	lea    0x14(%esp),%eax
 8048dc2:	50                   	push   %eax
 8048dc3:	ff 74 24 5c          	pushl  0x5c(%esp)
 # read in:
 8048dc7:	e8 42 03 00 00       	call   804910e <read_six_numbers>
 8048dcc:	83 c4 10             	add    $0x10,%esp
 # ----------------------------- part2 ---------------------------------
 8048dcf:	be 00 00 00 00       	mov    $0x0,%esi
 # outer loop:
 8048dd4:	8b 44 b4 0c          	mov    0xc(%esp,%esi,4),%eax
 8048dd8:	83 e8 01             	sub    $0x1,%eax # -1
 8048ddb:	83 f8 05             	cmp    $0x5,%eax # (x-1)<=5 √
 8048dde:	76 05                	jbe    8048de5 <phase_6+0x38>
 8048de0:	e8 04 03 00 00       	call   80490e9 <explode_bomb>
 8048de5:	83 c6 01             	add    $0x1,%esi
 8048de8:	83 fe 06             	cmp    $0x6,%esi # outer loop(6)
 8048deb:	74 1b                	je     8048e08 <phase_6+0x5b>
 8048ded:	89 f3                	mov    %esi,%ebx # %ebx: temp value
 # inner loop:
 8048def:	8b 44 9c 0c          	mov    0xc(%esp,%ebx,4),%eax
 8048df3:	39 44 b4 08          	cmp    %eax,0x8(%esp,%esi,4)
 8048df7:	75 05                	jne    8048dfe <phase_6+0x51> # all is different
 8048df9:	e8 eb 02 00 00       	call   80490e9 <explode_bomb>
 8048dfe:	83 c3 01             	add    $0x1,%ebx
 8048e01:	83 fb 05             	cmp    $0x5,%ebx # inner loop(5)
 8048e04:	7e e9                	jle    8048def <phase_6+0x42>
 # inner loop end
 8048e06:	eb cc                	jmp    8048dd4 <phase_6+0x27>
 # outer loop end
 # ----------------------------- part3 ---------------------------------
 8048e08:	8d 44 24 0c          	lea    0xc(%esp),%eax
 8048e0c:	8d 5c 24 24          	lea    0x24(%esp),%ebx # len: 6 bytes
 8048e10:	b9 07 00 00 00       	mov    $0x7,%ecx # init:
 # loop3: ▲ between each number and 7
 8048e15:	89 ca                	mov    %ecx,%edx
 8048e17:	2b 10                	sub    (%eax),%edx 
 8048e19:	89 10                	mov    %edx,(%eax) # (%eax) = %edx - (%eax)
 8048e1b:	83 c0 04             	add    $0x4,%eax # next byte
 8048e1e:	39 c3                	cmp    %eax,%ebx 
 8048e20:	75 f3                	jne    8048e15 <phase_6+0x68>
 # loop3 end
 # ----------------------------- part4 ---------------------------------
 8048e22:	bb 00 00 00 00       	mov    $0x0,%ebx # init:
 8048e27:	eb 16                	jmp    8048e3f <phase_6+0x92>
 # go through the old and build a new linked list:
 8048e29:	8b 52 08             	mov    0x8(%edx),%edx # next ptr
 8048e2c:	83 c0 01             	add    $0x1,%eax
 8048e2f:	39 c8                	cmp    %ecx,%eax
 8048e31:	75 f6                	jne    8048e29 <phase_6+0x7c>
 8048e33:	89 54 b4 24          	mov    %edx,0x24(%esp,%esi,4) # %esi == 6
 8048e37:	83 c3 01             	add    $0x1,%ebx
 8048e3a:	83 fb 06             	cmp    $0x6,%ebx
 8048e3d:	74 17                	je     8048e56 <phase_6+0xa9>
 8048e3f:	89 de                	mov    %ebx,%esi
 8048e41:	8b 4c 9c 0c          	mov    0xc(%esp,%ebx,4),%ecx
 8048e45:	b8 01 00 00 00       	mov    $0x1,%eax
 8048e4a:	ba 3c c1 04 08       	mov    $0x804c13c,%edx # the first node!
 8048e4f:	83 f9 01             	cmp    $0x1,%ecx
 8048e52:	7f d5                	jg     8048e29 <phase_6+0x7c>
 8048e54:	eb dd                	jmp    8048e33 <phase_6+0x86>
 8048e56:	8b 5c 24 24          	mov    0x24(%esp),%ebx
 8048e5a:	8d 44 24 24          	lea    0x24(%esp),%eax
 8048e5e:	8d 74 24 38          	lea    0x38(%esp),%esi
 8048e62:	89 d9                	mov    %ebx,%ecx
 8048e64:	8b 50 04             	mov    0x4(%eax),%edx
 8048e67:	89 51 08             	mov    %edx,0x8(%ecx) # ptr -> next node
 8048e6a:	83 c0 04             	add    $0x4,%eax
 8048e6d:	89 d1                	mov    %edx,%ecx
 8048e6f:	39 c6                	cmp    %eax,%esi
 8048e71:	75 f1                	jne    8048e64 <phase_6+0xb7>
 8048e73:	c7 42 08 00 00 00 00 	movl   $0x0,0x8(%edx) # the last node -> 0
 # new linked list built
 # ----------------------------- part5 ---------------------------------
 # judge:
 8048e7a:	be 05 00 00 00       	mov    $0x5,%esi
 8048e7f:	8b 43 08             	mov    0x8(%ebx),%eax
 8048e82:	8b 00                	mov    (%eax),%eax
 8048e84:	39 03                	cmp    %eax,(%ebx)
 8048e86:	7d 05                	jge    8048e8d <phase_6+0xe0> # the former is bigger
 8048e88:	e8 5c 02 00 00       	call   80490e9 <explode_bomb> 
 8048e8d:	8b 5b 08             	mov    0x8(%ebx),%ebx
 8048e90:	83 ee 01             	sub    $0x1,%esi
 8048e93:	75 ea                	jne    8048e7f <phase_6+0xd2>
 8048e95:	8b 44 24 3c          	mov    0x3c(%esp),%eax
 8048e99:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048ea0:	74 05                	je     8048ea7 <phase_6+0xfa>
 8048ea2:	e8 e9 f8 ff ff       	call   8048790 <__stack_chk_fail@plt>
 8048ea7:	83 c4 44             	add    $0x44,%esp
 8048eaa:	5b                   	pop    %ebx
 8048eab:	5e                   	pop    %esi
 8048eac:	c3                   	ret    

08048ead <fun7>:
 8048ead:	53                   	push   %ebx
 8048eae:	83 ec 08             	sub    $0x8,%esp
 8048eb1:	8b 54 24 10          	mov    0x10(%esp),%edx
 8048eb5:	8b 4c 24 14          	mov    0x14(%esp),%ecx
 8048eb9:	85 d2                	test   %edx,%edx
 8048ebb:	74 37                	je     8048ef4 <fun7+0x47> # boom

 8048ebd:	8b 1a                	mov    (%edx),%ebx
 8048ebf:	39 cb                	cmp    %ecx,%ebx
 8048ec1:	7e 13                	jle    8048ed6 <fun7+0x29>

 8048ec3:	83 ec 08             	sub    $0x8,%esp
 8048ec6:	51                   	push   %ecx
 8048ec7:	ff 72 04             	pushl  0x4(%edx)
 8048eca:	e8 de ff ff ff       	call   8048ead <fun7>

 8048ecf:	83 c4 10             	add    $0x10,%esp
 8048ed2:	01 c0                	add    %eax,%eax
 8048ed4:	eb 23                	jmp    8048ef9 <fun7+0x4c>

 8048ed6:	b8 00 00 00 00       	mov    $0x0,%eax
 8048edb:	39 cb                	cmp    %ecx,%ebx
 8048edd:	74 1a                	je     8048ef9 <fun7+0x4c>

 8048edf:	83 ec 08             	sub    $0x8,%esp
 8048ee2:	51                   	push   %ecx
 8048ee3:	ff 72 08             	pushl  0x8(%edx)
 8048ee6:	e8 c2 ff ff ff       	call   8048ead <fun7>
 8048eeb:	83 c4 10             	add    $0x10,%esp
 8048eee:	8d 44 00 01          	lea    0x1(%eax,%eax,1),%eax
 8048ef2:	eb 05                	jmp    8048ef9 <fun7+0x4c>
 8048ef4:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 
 8048ef9:	83 c4 08             	add    $0x8,%esp
 8048efc:	5b                   	pop    %ebx
 8048efd:	c3                   	ret    

08048efe <secret_phase>:
 8048efe:	53                   	push   %ebx
 8048eff:	83 ec 08             	sub    $0x8,%esp
 8048f02:	e8 42 02 00 00       	call   8049149 <read_line>
 # parameters:
 8048f07:	83 ec 04             	sub    $0x4,%esp
 8048f0a:	6a 0a                	push   $0xa
 8048f0c:	6a 00                	push   $0x0
 8048f0e:	50                   	push   %eax
 # strtol
 8048f0f:	e8 6c f9 ff ff       	call   8048880 <strtol@plt>

 8048f14:	89 c3                	mov    %eax,%ebx
 8048f16:	8d 40 ff             	lea    -0x1(%eax),%eax # eax -= 1
 8048f19:	83 c4 10             	add    $0x10,%esp
 8048f1c:	3d e8 03 00 00       	cmp    $0x3e8,%eax # eax ? 0x3e8
 8048f21:	76 05                	jbe    8048f28 <secret_phase+0x2a> # para1 <= 0x3e9
 8048f23:	e8 c1 01 00 00       	call   80490e9 <explode_bomb>
 # parameter:
 8048f28:	83 ec 08             	sub    $0x8,%esp
 8048f2b:	53                   	push   %ebx
 8048f2c:	68 88 c0 04 08       	push   $0x804c088
 # fun7:
 8048f31:	e8 77 ff ff ff       	call   8048ead <fun7>

 8048f36:	83 c4 10             	add    $0x10,%esp
 8048f39:	83 f8 01             	cmp    $0x1,%eax
 8048f3c:	74 05                	je     8048f43 <secret_phase+0x45>
 8048f3e:	e8 a6 01 00 00       	call   80490e9 <explode_bomb>

 8048f43:	83 ec 0c             	sub    $0xc,%esp
 8048f46:	68 38 a0 04 08       	push   $0x804a038
 8048f4b:	e8 70 f8 ff ff       	call   80487c0 <puts@plt>
 8048f50:	e8 ed 02 00 00       	call   8049242 <phase_defused>
 8048f55:	83 c4 18             	add    $0x18,%esp
 8048f58:	5b                   	pop    %ebx
 8048f59:	c3                   	ret    

08048f5a <sig_handler>:
 8048f5a:	83 ec 18             	sub    $0x18,%esp
 8048f5d:	68 c0 a0 04 08       	push   $0x804a0c0
 8048f62:	e8 59 f8 ff ff       	call   80487c0 <puts@plt>
 8048f67:	c7 04 24 03 00 00 00 	movl   $0x3,(%esp)
 8048f6e:	e8 fd f7 ff ff       	call   8048770 <sleep@plt>
 8048f73:	83 c4 08             	add    $0x8,%esp
 8048f76:	68 82 a1 04 08       	push   $0x804a182
 8048f7b:	6a 01                	push   $0x1
 8048f7d:	e8 be f8 ff ff       	call   8048840 <__printf_chk@plt>
 8048f82:	83 c4 04             	add    $0x4,%esp
 8048f85:	ff 35 c4 c3 04 08    	pushl  0x804c3c4
 8048f8b:	e8 b0 f7 ff ff       	call   8048740 <fflush@plt>
 8048f90:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8048f97:	e8 d4 f7 ff ff       	call   8048770 <sleep@plt>
 8048f9c:	c7 04 24 8a a1 04 08 	movl   $0x804a18a,(%esp)
 8048fa3:	e8 18 f8 ff ff       	call   80487c0 <puts@plt>
 8048fa8:	c7 04 24 10 00 00 00 	movl   $0x10,(%esp)
 8048faf:	e8 2c f8 ff ff       	call   80487e0 <exit@plt>

08048fb4 <invalid_phase>:
 8048fb4:	83 ec 10             	sub    $0x10,%esp
 8048fb7:	ff 74 24 14          	pushl  0x14(%esp)
 8048fbb:	68 92 a1 04 08       	push   $0x804a192
 8048fc0:	6a 01                	push   $0x1
 8048fc2:	e8 79 f8 ff ff       	call   8048840 <__printf_chk@plt>
 8048fc7:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048fce:	e8 0d f8 ff ff       	call   80487e0 <exit@plt>

08048fd3 <string_length>:
 8048fd3:	8b 54 24 04          	mov    0x4(%esp),%edx
 8048fd7:	80 3a 00             	cmpb   $0x0,(%edx)
 8048fda:	74 10                	je     8048fec <string_length+0x19>
 8048fdc:	b8 00 00 00 00       	mov    $0x0,%eax
 8048fe1:	83 c0 01             	add    $0x1,%eax
 8048fe4:	80 3c 02 00          	cmpb   $0x0,(%edx,%eax,1)
 8048fe8:	75 f7                	jne    8048fe1 <string_length+0xe>
 8048fea:	f3 c3                	repz ret 
 8048fec:	b8 00 00 00 00       	mov    $0x0,%eax
 8048ff1:	c3                   	ret    

08048ff2 <strings_not_equal>:
 8048ff2:	57                   	push   %edi
 8048ff3:	56                   	push   %esi
 8048ff4:	53                   	push   %ebx
 8048ff5:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 8048ff9:	8b 74 24 14          	mov    0x14(%esp),%esi
 8048ffd:	53                   	push   %ebx
 8048ffe:	e8 d0 ff ff ff       	call   8048fd3 <string_length>
 8049003:	89 c7                	mov    %eax,%edi
 8049005:	89 34 24             	mov    %esi,(%esp)
 8049008:	e8 c6 ff ff ff       	call   8048fd3 <string_length>
 804900d:	83 c4 04             	add    $0x4,%esp
 8049010:	ba 01 00 00 00       	mov    $0x1,%edx
 8049015:	39 c7                	cmp    %eax,%edi
 8049017:	75 38                	jne    8049051 <strings_not_equal+0x5f>
 8049019:	0f b6 03             	movzbl (%ebx),%eax
 804901c:	84 c0                	test   %al,%al
 804901e:	74 1e                	je     804903e <strings_not_equal+0x4c>
 8049020:	3a 06                	cmp    (%esi),%al
 8049022:	74 06                	je     804902a <strings_not_equal+0x38>
 8049024:	eb 1f                	jmp    8049045 <strings_not_equal+0x53>
 8049026:	3a 06                	cmp    (%esi),%al
 8049028:	75 22                	jne    804904c <strings_not_equal+0x5a>
 804902a:	83 c3 01             	add    $0x1,%ebx
 804902d:	83 c6 01             	add    $0x1,%esi
 8049030:	0f b6 03             	movzbl (%ebx),%eax
 8049033:	84 c0                	test   %al,%al
 8049035:	75 ef                	jne    8049026 <strings_not_equal+0x34>
 8049037:	ba 00 00 00 00       	mov    $0x0,%edx
 804903c:	eb 13                	jmp    8049051 <strings_not_equal+0x5f>
 804903e:	ba 00 00 00 00       	mov    $0x0,%edx
 8049043:	eb 0c                	jmp    8049051 <strings_not_equal+0x5f>
 8049045:	ba 01 00 00 00       	mov    $0x1,%edx
 804904a:	eb 05                	jmp    8049051 <strings_not_equal+0x5f>
 804904c:	ba 01 00 00 00       	mov    $0x1,%edx
 8049051:	89 d0                	mov    %edx,%eax
 8049053:	5b                   	pop    %ebx
 8049054:	5e                   	pop    %esi
 8049055:	5f                   	pop    %edi
 8049056:	c3                   	ret    

08049057 <initialize_bomb>:
 8049057:	83 ec 14             	sub    $0x14,%esp
 804905a:	68 5a 8f 04 08       	push   $0x8048f5a
 804905f:	6a 02                	push   $0x2
 8049061:	e8 fa f6 ff ff       	call   8048760 <signal@plt>
 8049066:	83 c4 1c             	add    $0x1c,%esp
 8049069:	c3                   	ret    

0804906a <initialize_bomb_solve>:
 804906a:	f3 c3                	repz ret 

0804906c <blank_line>:
 804906c:	56                   	push   %esi
 804906d:	53                   	push   %ebx
 804906e:	83 ec 04             	sub    $0x4,%esp
 8049071:	8b 74 24 10          	mov    0x10(%esp),%esi
 8049075:	eb 14                	jmp    804908b <blank_line+0x1f>
 8049077:	e8 34 f8 ff ff       	call   80488b0 <__ctype_b_loc@plt>
 804907c:	83 c6 01             	add    $0x1,%esi
 804907f:	0f be db             	movsbl %bl,%ebx
 8049082:	8b 00                	mov    (%eax),%eax
 8049084:	f6 44 58 01 20       	testb  $0x20,0x1(%eax,%ebx,2)
 8049089:	74 0e                	je     8049099 <blank_line+0x2d>
 804908b:	0f b6 1e             	movzbl (%esi),%ebx
 804908e:	84 db                	test   %bl,%bl
 8049090:	75 e5                	jne    8049077 <blank_line+0xb>
 8049092:	b8 01 00 00 00       	mov    $0x1,%eax
 8049097:	eb 05                	jmp    804909e <blank_line+0x32>
 8049099:	b8 00 00 00 00       	mov    $0x0,%eax
 804909e:	83 c4 04             	add    $0x4,%esp
 80490a1:	5b                   	pop    %ebx
 80490a2:	5e                   	pop    %esi
 80490a3:	c3                   	ret    

080490a4 <skip>:
 80490a4:	53                   	push   %ebx
 80490a5:	83 ec 08             	sub    $0x8,%esp
 80490a8:	83 ec 04             	sub    $0x4,%esp
 80490ab:	ff 35 d0 c3 04 08    	pushl  0x804c3d0
 80490b1:	6a 50                	push   $0x50
 80490b3:	a1 cc c3 04 08       	mov    0x804c3cc,%eax
 80490b8:	8d 04 80             	lea    (%eax,%eax,4),%eax
 80490bb:	c1 e0 04             	shl    $0x4,%eax
 80490be:	05 e0 c3 04 08       	add    $0x804c3e0,%eax
 80490c3:	50                   	push   %eax
 80490c4:	e8 87 f6 ff ff       	call   8048750 <fgets@plt>
 80490c9:	89 c3                	mov    %eax,%ebx
 80490cb:	83 c4 10             	add    $0x10,%esp
 80490ce:	85 c0                	test   %eax,%eax
 80490d0:	74 10                	je     80490e2 <skip+0x3e>
 80490d2:	83 ec 0c             	sub    $0xc,%esp
 80490d5:	50                   	push   %eax
 80490d6:	e8 91 ff ff ff       	call   804906c <blank_line>
 80490db:	83 c4 10             	add    $0x10,%esp
 80490de:	85 c0                	test   %eax,%eax
 80490e0:	75 c6                	jne    80490a8 <skip+0x4>
 80490e2:	89 d8                	mov    %ebx,%eax
 80490e4:	83 c4 08             	add    $0x8,%esp
 80490e7:	5b                   	pop    %ebx
 80490e8:	c3                   	ret    

080490e9 <explode_bomb>:
 80490e9:	83 ec 18             	sub    $0x18,%esp
 80490ec:	68 a3 a1 04 08       	push   $0x804a1a3
 80490f1:	e8 ca f6 ff ff       	call   80487c0 <puts@plt>
 80490f6:	c7 04 24 ac a1 04 08 	movl   $0x804a1ac,(%esp)
 80490fd:	e8 be f6 ff ff       	call   80487c0 <puts@plt>
 8049102:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049109:	e8 d2 f6 ff ff       	call   80487e0 <exit@plt>

0804910e <read_six_numbers>:
 804910e:	83 ec 0c             	sub    $0xc,%esp
 8049111:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049115:	8d 50 14             	lea    0x14(%eax),%edx
 8049118:	52                   	push   %edx
 8049119:	8d 50 10             	lea    0x10(%eax),%edx
 804911c:	52                   	push   %edx
 804911d:	8d 50 0c             	lea    0xc(%eax),%edx
 8049120:	52                   	push   %edx
 8049121:	8d 50 08             	lea    0x8(%eax),%edx
 8049124:	52                   	push   %edx
 8049125:	8d 50 04             	lea    0x4(%eax),%edx
 8049128:	52                   	push   %edx
 8049129:	50                   	push   %eax
 804912a:	68 c3 a1 04 08       	push   $0x804a1c3
 804912f:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049133:	e8 d8 f6 ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8049138:	83 c4 20             	add    $0x20,%esp
 804913b:	83 f8 05             	cmp    $0x5,%eax
 804913e:	7f 05                	jg     8049145 <read_six_numbers+0x37>
 8049140:	e8 a4 ff ff ff       	call   80490e9 <explode_bomb>
 8049145:	83 c4 0c             	add    $0xc,%esp
 8049148:	c3                   	ret    

08049149 <read_line>:
 8049149:	57                   	push   %edi
 804914a:	56                   	push   %esi
 804914b:	53                   	push   %ebx
 804914c:	e8 53 ff ff ff       	call   80490a4 <skip>
 8049151:	85 c0                	test   %eax,%eax
 8049153:	75 70                	jne    80491c5 <read_line+0x7c>
 8049155:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 804915a:	39 05 d0 c3 04 08    	cmp    %eax,0x804c3d0
 8049160:	75 19                	jne    804917b <read_line+0x32>
 8049162:	83 ec 0c             	sub    $0xc,%esp
 8049165:	68 d5 a1 04 08       	push   $0x804a1d5
 804916a:	e8 51 f6 ff ff       	call   80487c0 <puts@plt>
 804916f:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049176:	e8 65 f6 ff ff       	call   80487e0 <exit@plt>
 804917b:	83 ec 0c             	sub    $0xc,%esp
 804917e:	68 f3 a1 04 08       	push   $0x804a1f3
 8049183:	e8 28 f6 ff ff       	call   80487b0 <getenv@plt>
 8049188:	83 c4 10             	add    $0x10,%esp
 804918b:	85 c0                	test   %eax,%eax
 804918d:	74 0a                	je     8049199 <read_line+0x50>
 804918f:	83 ec 0c             	sub    $0xc,%esp
 8049192:	6a 00                	push   $0x0
 8049194:	e8 47 f6 ff ff       	call   80487e0 <exit@plt>
 8049199:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 804919e:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 80491a3:	e8 fc fe ff ff       	call   80490a4 <skip>
 80491a8:	85 c0                	test   %eax,%eax
 80491aa:	75 19                	jne    80491c5 <read_line+0x7c>
 80491ac:	83 ec 0c             	sub    $0xc,%esp
 80491af:	68 d5 a1 04 08       	push   $0x804a1d5
 80491b4:	e8 07 f6 ff ff       	call   80487c0 <puts@plt>
 80491b9:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 80491c0:	e8 1b f6 ff ff       	call   80487e0 <exit@plt>
 80491c5:	8b 15 cc c3 04 08    	mov    0x804c3cc,%edx
 80491cb:	8d 1c 92             	lea    (%edx,%edx,4),%ebx
 80491ce:	c1 e3 04             	shl    $0x4,%ebx
 80491d1:	81 c3 e0 c3 04 08    	add    $0x804c3e0,%ebx
 80491d7:	b8 00 00 00 00       	mov    $0x0,%eax
 80491dc:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 80491e1:	89 df                	mov    %ebx,%edi
 80491e3:	f2 ae                	repnz scas %es:(%edi),%al
 80491e5:	f7 d1                	not    %ecx
 80491e7:	83 e9 01             	sub    $0x1,%ecx
 80491ea:	83 f9 4e             	cmp    $0x4e,%ecx
 80491ed:	7e 36                	jle    8049225 <read_line+0xdc>
 80491ef:	83 ec 0c             	sub    $0xc,%esp
 80491f2:	68 fe a1 04 08       	push   $0x804a1fe
 80491f7:	e8 c4 f5 ff ff       	call   80487c0 <puts@plt>
 80491fc:	a1 cc c3 04 08       	mov    0x804c3cc,%eax
 8049201:	8d 50 01             	lea    0x1(%eax),%edx
 8049204:	89 15 cc c3 04 08    	mov    %edx,0x804c3cc
 804920a:	6b c0 50             	imul   $0x50,%eax,%eax
 804920d:	05 e0 c3 04 08       	add    $0x804c3e0,%eax
 8049212:	be 19 a2 04 08       	mov    $0x804a219,%esi
 8049217:	b9 04 00 00 00       	mov    $0x4,%ecx
 804921c:	89 c7                	mov    %eax,%edi
 804921e:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049220:	e8 c4 fe ff ff       	call   80490e9 <explode_bomb>
 8049225:	8d 04 92             	lea    (%edx,%edx,4),%eax
 8049228:	c1 e0 04             	shl    $0x4,%eax
 804922b:	c6 84 01 df c3 04 08 	movb   $0x0,0x804c3df(%ecx,%eax,1)
 8049232:	00 
 8049233:	83 c2 01             	add    $0x1,%edx
 8049236:	89 15 cc c3 04 08    	mov    %edx,0x804c3cc
 804923c:	89 d8                	mov    %ebx,%eax
 804923e:	5b                   	pop    %ebx
 804923f:	5e                   	pop    %esi
 8049240:	5f                   	pop    %edi
 8049241:	c3                   	ret    

08049242 <phase_defused>:
 8049242:	83 ec 6c             	sub    $0x6c,%esp
 8049245:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 804924b:	89 44 24 5c          	mov    %eax,0x5c(%esp)
 804924f:	31 c0                	xor    %eax,%eax
 8049251:	83 3d cc c3 04 08 06 	cmpl   $0x6,0x804c3cc
 8049258:	75 73                	jne    80492cd <phase_defused+0x8b>
 # parameters:
 804925a:	83 ec 0c             	sub    $0xc,%esp
 804925d:	8d 44 24 18          	lea    0x18(%esp),%eax
 8049261:	50                   	push   %eax
 8049262:	8d 44 24 18          	lea    0x18(%esp),%eax
 8049266:	50                   	push   %eax
 8049267:	8d 44 24 18          	lea    0x18(%esp),%eax
 804926b:	50                   	push   %eax
 804926c:	68 29 a2 04 08       	push   $0x804a229
 8049271:	68 d0 c4 04 08       	push   $0x804c4d0
 # read in:
 8049276:	e8 95 f5 ff ff       	call   8048810 <__isoc99_sscanf@plt>
 804927b:	83 c4 20             	add    $0x20,%esp
 804927e:	83 f8 03             	cmp    $0x3,%eax
 8049281:	75 3a                	jne    80492bd <phase_defused+0x7b>
 # parameters:
 8049283:	83 ec 08             	sub    $0x8,%esp
 8049286:	68 32 a2 04 08       	push   $0x804a232
 804928b:	8d 44 24 18          	lea    0x18(%esp),%eax
 804928f:	50                   	push   %eax
 # strings_not_equal:
 8049290:	e8 5d fd ff ff       	call   8048ff2 <strings_not_equal>
 8049295:	83 c4 10             	add    $0x10,%esp
 8049298:	85 c0                	test   %eax,%eax
 804929a:	75 21                	jne    80492bd <phase_defused+0x7b>

 804929c:	83 ec 0c             	sub    $0xc,%esp
 804929f:	68 f8 a0 04 08       	push   $0x804a0f8
 80492a4:	e8 17 f5 ff ff       	call   80487c0 <puts@plt>
 80492a9:	c7 04 24 20 a1 04 08 	movl   $0x804a120,(%esp)
 80492b0:	e8 0b f5 ff ff       	call   80487c0 <puts@plt>
 80492b5:	e8 44 fc ff ff       	call   8048efe <secret_phase>
 80492ba:	83 c4 10             	add    $0x10,%esp

 80492bd:	83 ec 0c             	sub    $0xc,%esp
 80492c0:	68 58 a1 04 08       	push   $0x804a158
 80492c5:	e8 f6 f4 ff ff       	call   80487c0 <puts@plt>
 80492ca:	83 c4 10             	add    $0x10,%esp
 80492cd:	8b 44 24 5c          	mov    0x5c(%esp),%eax
 80492d1:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 80492d8:	74 05                	je     80492df <phase_defused+0x9d>
 80492da:	e8 b1 f4 ff ff       	call   8048790 <__stack_chk_fail@plt>
 80492df:	83 c4 6c             	add    $0x6c,%esp
 80492e2:	c3                   	ret    

080492e3 <sigalrm_handler>:
 80492e3:	83 ec 0c             	sub    $0xc,%esp
 80492e6:	6a 00                	push   $0x0
 80492e8:	68 88 a2 04 08       	push   $0x804a288
 80492ed:	6a 01                	push   $0x1
 80492ef:	ff 35 a0 c3 04 08    	pushl  0x804c3a0
 80492f5:	e8 66 f5 ff ff       	call   8048860 <__fprintf_chk@plt>
 80492fa:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8049301:	e8 da f4 ff ff       	call   80487e0 <exit@plt>

08049306 <rio_readlineb>:
 8049306:	55                   	push   %ebp
 8049307:	57                   	push   %edi
 8049308:	56                   	push   %esi
 8049309:	53                   	push   %ebx
 804930a:	83 ec 2c             	sub    $0x2c,%esp
 804930d:	89 d7                	mov    %edx,%edi
 804930f:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
 8049313:	65 8b 15 14 00 00 00 	mov    %gs:0x14,%edx
 804931a:	89 54 24 1c          	mov    %edx,0x1c(%esp)
 804931e:	31 d2                	xor    %edx,%edx
 8049320:	83 f9 01             	cmp    $0x1,%ecx
 8049323:	76 79                	jbe    804939e <rio_readlineb+0x98>
 8049325:	89 c3                	mov    %eax,%ebx
 8049327:	89 4c 24 08          	mov    %ecx,0x8(%esp)
 804932b:	bd 01 00 00 00       	mov    $0x1,%ebp
 8049330:	8d 73 0c             	lea    0xc(%ebx),%esi
 8049333:	eb 2d                	jmp    8049362 <rio_readlineb+0x5c>
 8049335:	83 ec 04             	sub    $0x4,%esp
 8049338:	68 00 20 00 00       	push   $0x2000
 804933d:	56                   	push   %esi
 804933e:	ff 33                	pushl  (%ebx)
 8049340:	e8 eb f3 ff ff       	call   8048730 <read@plt>
 8049345:	89 43 04             	mov    %eax,0x4(%ebx)
 8049348:	83 c4 10             	add    $0x10,%esp
 804934b:	85 c0                	test   %eax,%eax
 804934d:	79 0c                	jns    804935b <rio_readlineb+0x55>
 804934f:	e8 dc f4 ff ff       	call   8048830 <__errno_location@plt>
 8049354:	83 38 04             	cmpl   $0x4,(%eax)
 8049357:	74 09                	je     8049362 <rio_readlineb+0x5c>
 8049359:	eb 62                	jmp    80493bd <rio_readlineb+0xb7>
 804935b:	85 c0                	test   %eax,%eax
 804935d:	74 63                	je     80493c2 <rio_readlineb+0xbc>
 804935f:	89 73 08             	mov    %esi,0x8(%ebx)
 8049362:	8b 43 04             	mov    0x4(%ebx),%eax
 8049365:	85 c0                	test   %eax,%eax
 8049367:	7e cc                	jle    8049335 <rio_readlineb+0x2f>
 8049369:	8b 4b 08             	mov    0x8(%ebx),%ecx
 804936c:	0f b6 11             	movzbl (%ecx),%edx
 804936f:	88 54 24 1b          	mov    %dl,0x1b(%esp)
 8049373:	83 c1 01             	add    $0x1,%ecx
 8049376:	89 4b 08             	mov    %ecx,0x8(%ebx)
 8049379:	83 e8 01             	sub    $0x1,%eax
 804937c:	89 43 04             	mov    %eax,0x4(%ebx)
 804937f:	83 c7 01             	add    $0x1,%edi
 8049382:	88 57 ff             	mov    %dl,-0x1(%edi)
 8049385:	80 fa 0a             	cmp    $0xa,%dl
 8049388:	75 09                	jne    8049393 <rio_readlineb+0x8d>
 804938a:	eb 1d                	jmp    80493a9 <rio_readlineb+0xa3>
 804938c:	83 fd 01             	cmp    $0x1,%ebp
 804938f:	75 18                	jne    80493a9 <rio_readlineb+0xa3>
 8049391:	eb 1b                	jmp    80493ae <rio_readlineb+0xa8>
 8049393:	83 c5 01             	add    $0x1,%ebp
 8049396:	3b 6c 24 08          	cmp    0x8(%esp),%ebp
 804939a:	74 09                	je     80493a5 <rio_readlineb+0x9f>
 804939c:	eb c4                	jmp    8049362 <rio_readlineb+0x5c>
 804939e:	bd 01 00 00 00       	mov    $0x1,%ebp
 80493a3:	eb 04                	jmp    80493a9 <rio_readlineb+0xa3>
 80493a5:	8b 6c 24 0c          	mov    0xc(%esp),%ebp
 80493a9:	c6 07 00             	movb   $0x0,(%edi)
 80493ac:	89 e8                	mov    %ebp,%eax
 80493ae:	8b 54 24 1c          	mov    0x1c(%esp),%edx
 80493b2:	65 33 15 14 00 00 00 	xor    %gs:0x14,%edx
 80493b9:	74 17                	je     80493d2 <rio_readlineb+0xcc>
 80493bb:	eb 10                	jmp    80493cd <rio_readlineb+0xc7>
 80493bd:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80493c2:	85 c0                	test   %eax,%eax
 80493c4:	74 c6                	je     804938c <rio_readlineb+0x86>
 80493c6:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80493cb:	eb e1                	jmp    80493ae <rio_readlineb+0xa8>
 80493cd:	e8 be f3 ff ff       	call   8048790 <__stack_chk_fail@plt>
 80493d2:	83 c4 2c             	add    $0x2c,%esp
 80493d5:	5b                   	pop    %ebx
 80493d6:	5e                   	pop    %esi
 80493d7:	5f                   	pop    %edi
 80493d8:	5d                   	pop    %ebp
 80493d9:	c3                   	ret    

080493da <submitr>:
 80493da:	55                   	push   %ebp
 80493db:	57                   	push   %edi
 80493dc:	56                   	push   %esi
 80493dd:	53                   	push   %ebx
 80493de:	81 ec 60 a0 00 00    	sub    $0xa060,%esp
 80493e4:	8b b4 24 74 a0 00 00 	mov    0xa074(%esp),%esi
 80493eb:	8b 84 24 7c a0 00 00 	mov    0xa07c(%esp),%eax
 80493f2:	89 44 24 10          	mov    %eax,0x10(%esp)
 80493f6:	8b 84 24 80 a0 00 00 	mov    0xa080(%esp),%eax
 80493fd:	89 44 24 14          	mov    %eax,0x14(%esp)
 8049401:	8b 84 24 84 a0 00 00 	mov    0xa084(%esp),%eax
 8049408:	89 44 24 18          	mov    %eax,0x18(%esp)
 804940c:	8b 9c 24 88 a0 00 00 	mov    0xa088(%esp),%ebx
 8049413:	8b 84 24 8c a0 00 00 	mov    0xa08c(%esp),%eax
 804941a:	89 44 24 1c          	mov    %eax,0x1c(%esp)
 804941e:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8049424:	89 84 24 50 a0 00 00 	mov    %eax,0xa050(%esp)
 804942b:	31 c0                	xor    %eax,%eax
 804942d:	c7 44 24 30 00 00 00 	movl   $0x0,0x30(%esp)
 8049434:	00 
 8049435:	6a 00                	push   $0x0
 8049437:	6a 01                	push   $0x1
 8049439:	6a 02                	push   $0x2
 804943b:	e8 10 f4 ff ff       	call   8048850 <socket@plt>
 8049440:	89 44 24 18          	mov    %eax,0x18(%esp)
 8049444:	83 c4 10             	add    $0x10,%esp
 8049447:	85 c0                	test   %eax,%eax
 8049449:	79 52                	jns    804949d <submitr+0xc3>
 804944b:	8b 44 24 18          	mov    0x18(%esp),%eax
 804944f:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049455:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 804945c:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049463:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 804946a:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049471:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049478:	c7 40 18 63 72 65 61 	movl   $0x61657263,0x18(%eax)
 804947f:	c7 40 1c 74 65 20 73 	movl   $0x73206574,0x1c(%eax)
 8049486:	c7 40 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%eax)
 804948d:	66 c7 40 24 74 00    	movw   $0x74,0x24(%eax)
 8049493:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049498:	e9 3f 06 00 00       	jmp    8049adc <submitr+0x702>
 804949d:	83 ec 0c             	sub    $0xc,%esp
 80494a0:	56                   	push   %esi
 80494a1:	e8 ca f3 ff ff       	call   8048870 <gethostbyname@plt>
 80494a6:	83 c4 10             	add    $0x10,%esp
 80494a9:	85 c0                	test   %eax,%eax
 80494ab:	75 73                	jne    8049520 <submitr+0x146>
 80494ad:	8b 44 24 18          	mov    0x18(%esp),%eax
 80494b1:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80494b7:	c7 40 04 72 3a 20 44 	movl   $0x44203a72,0x4(%eax)
 80494be:	c7 40 08 4e 53 20 69 	movl   $0x6920534e,0x8(%eax)
 80494c5:	c7 40 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%eax)
 80494cc:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 80494d3:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 80494da:	c7 40 18 72 65 73 6f 	movl   $0x6f736572,0x18(%eax)
 80494e1:	c7 40 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%eax)
 80494e8:	c7 40 20 73 65 72 76 	movl   $0x76726573,0x20(%eax)
 80494ef:	c7 40 24 65 72 20 61 	movl   $0x61207265,0x24(%eax)
 80494f6:	c7 40 28 64 64 72 65 	movl   $0x65726464,0x28(%eax)
 80494fd:	66 c7 40 2c 73 73    	movw   $0x7373,0x2c(%eax)
 8049503:	c6 40 2e 00          	movb   $0x0,0x2e(%eax)
 8049507:	83 ec 0c             	sub    $0xc,%esp
 804950a:	ff 74 24 14          	pushl  0x14(%esp)
 804950e:	e8 8d f3 ff ff       	call   80488a0 <close@plt>
 8049513:	83 c4 10             	add    $0x10,%esp
 8049516:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804951b:	e9 bc 05 00 00       	jmp    8049adc <submitr+0x702>
 8049520:	8d 74 24 30          	lea    0x30(%esp),%esi
 8049524:	c7 44 24 30 00 00 00 	movl   $0x0,0x30(%esp)
 804952b:	00 
 804952c:	c7 44 24 34 00 00 00 	movl   $0x0,0x34(%esp)
 8049533:	00 
 8049534:	c7 44 24 38 00 00 00 	movl   $0x0,0x38(%esp)
 804953b:	00 
 804953c:	c7 44 24 3c 00 00 00 	movl   $0x0,0x3c(%esp)
 8049543:	00 
 8049544:	66 c7 44 24 30 02 00 	movw   $0x2,0x30(%esp)
 804954b:	6a 0c                	push   $0xc
 804954d:	ff 70 0c             	pushl  0xc(%eax)
 8049550:	8b 40 10             	mov    0x10(%eax),%eax
 8049553:	ff 30                	pushl  (%eax)
 8049555:	8d 44 24 40          	lea    0x40(%esp),%eax
 8049559:	50                   	push   %eax
 804955a:	e8 71 f2 ff ff       	call   80487d0 <__memmove_chk@plt>
 804955f:	0f b7 84 24 84 a0 00 	movzwl 0xa084(%esp),%eax
 8049566:	00 
 8049567:	66 c1 c8 08          	ror    $0x8,%ax
 804956b:	66 89 44 24 42       	mov    %ax,0x42(%esp)
 8049570:	83 c4 0c             	add    $0xc,%esp
 8049573:	6a 10                	push   $0x10
 8049575:	56                   	push   %esi
 8049576:	ff 74 24 14          	pushl  0x14(%esp)
 804957a:	e8 11 f3 ff ff       	call   8048890 <connect@plt>
 804957f:	83 c4 10             	add    $0x10,%esp
 8049582:	85 c0                	test   %eax,%eax
 8049584:	79 65                	jns    80495eb <submitr+0x211>
 8049586:	8b 44 24 18          	mov    0x18(%esp),%eax
 804958a:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049590:	c7 40 04 72 3a 20 55 	movl   $0x55203a72,0x4(%eax)
 8049597:	c7 40 08 6e 61 62 6c 	movl   $0x6c62616e,0x8(%eax)
 804959e:	c7 40 0c 65 20 74 6f 	movl   $0x6f742065,0xc(%eax)
 80495a5:	c7 40 10 20 63 6f 6e 	movl   $0x6e6f6320,0x10(%eax)
 80495ac:	c7 40 14 6e 65 63 74 	movl   $0x7463656e,0x14(%eax)
 80495b3:	c7 40 18 20 74 6f 20 	movl   $0x206f7420,0x18(%eax)
 80495ba:	c7 40 1c 74 68 65 20 	movl   $0x20656874,0x1c(%eax)
 80495c1:	c7 40 20 73 65 72 76 	movl   $0x76726573,0x20(%eax)
 80495c8:	66 c7 40 24 65 72    	movw   $0x7265,0x24(%eax)
 80495ce:	c6 40 26 00          	movb   $0x0,0x26(%eax)
 80495d2:	83 ec 0c             	sub    $0xc,%esp
 80495d5:	ff 74 24 14          	pushl  0x14(%esp)
 80495d9:	e8 c2 f2 ff ff       	call   80488a0 <close@plt>
 80495de:	83 c4 10             	add    $0x10,%esp
 80495e1:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80495e6:	e9 f1 04 00 00       	jmp    8049adc <submitr+0x702>
 80495eb:	be ff ff ff ff       	mov    $0xffffffff,%esi
 80495f0:	b8 00 00 00 00       	mov    $0x0,%eax
 80495f5:	89 f1                	mov    %esi,%ecx
 80495f7:	89 df                	mov    %ebx,%edi
 80495f9:	f2 ae                	repnz scas %es:(%edi),%al
 80495fb:	f7 d1                	not    %ecx
 80495fd:	89 cd                	mov    %ecx,%ebp
 80495ff:	89 f1                	mov    %esi,%ecx
 8049601:	8b 7c 24 0c          	mov    0xc(%esp),%edi
 8049605:	f2 ae                	repnz scas %es:(%edi),%al
 8049607:	89 4c 24 1c          	mov    %ecx,0x1c(%esp)
 804960b:	89 f1                	mov    %esi,%ecx
 804960d:	8b 7c 24 10          	mov    0x10(%esp),%edi
 8049611:	f2 ae                	repnz scas %es:(%edi),%al
 8049613:	89 ca                	mov    %ecx,%edx
 8049615:	f7 d2                	not    %edx
 8049617:	89 f1                	mov    %esi,%ecx
 8049619:	8b 7c 24 14          	mov    0x14(%esp),%edi
 804961d:	f2 ae                	repnz scas %es:(%edi),%al
 804961f:	2b 54 24 1c          	sub    0x1c(%esp),%edx
 8049623:	29 ca                	sub    %ecx,%edx
 8049625:	8d 44 6d fd          	lea    -0x3(%ebp,%ebp,2),%eax
 8049629:	8d 44 02 7b          	lea    0x7b(%edx,%eax,1),%eax
 804962d:	3d 00 20 00 00       	cmp    $0x2000,%eax
 8049632:	76 7e                	jbe    80496b2 <submitr+0x2d8>
 8049634:	8b 44 24 18          	mov    0x18(%esp),%eax
 8049638:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 804963e:	c7 40 04 72 3a 20 52 	movl   $0x52203a72,0x4(%eax)
 8049645:	c7 40 08 65 73 75 6c 	movl   $0x6c757365,0x8(%eax)
 804964c:	c7 40 0c 74 20 73 74 	movl   $0x74732074,0xc(%eax)
 8049653:	c7 40 10 72 69 6e 67 	movl   $0x676e6972,0x10(%eax)
 804965a:	c7 40 14 20 74 6f 6f 	movl   $0x6f6f7420,0x14(%eax)
 8049661:	c7 40 18 20 6c 61 72 	movl   $0x72616c20,0x18(%eax)
 8049668:	c7 40 1c 67 65 2e 20 	movl   $0x202e6567,0x1c(%eax)
 804966f:	c7 40 20 49 6e 63 72 	movl   $0x72636e49,0x20(%eax)
 8049676:	c7 40 24 65 61 73 65 	movl   $0x65736165,0x24(%eax)
 804967d:	c7 40 28 20 53 55 42 	movl   $0x42555320,0x28(%eax)
 8049684:	c7 40 2c 4d 49 54 52 	movl   $0x5254494d,0x2c(%eax)
 804968b:	c7 40 30 5f 4d 41 58 	movl   $0x58414d5f,0x30(%eax)
 8049692:	c7 40 34 42 55 46 00 	movl   $0x465542,0x34(%eax)
 8049699:	83 ec 0c             	sub    $0xc,%esp
 804969c:	ff 74 24 14          	pushl  0x14(%esp)
 80496a0:	e8 fb f1 ff ff       	call   80488a0 <close@plt>
 80496a5:	83 c4 10             	add    $0x10,%esp
 80496a8:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80496ad:	e9 2a 04 00 00       	jmp    8049adc <submitr+0x702>
 80496b2:	8d 94 24 4c 40 00 00 	lea    0x404c(%esp),%edx
 80496b9:	b9 00 08 00 00       	mov    $0x800,%ecx
 80496be:	b8 00 00 00 00       	mov    $0x0,%eax
 80496c3:	89 d7                	mov    %edx,%edi
 80496c5:	f3 ab                	rep stos %eax,%es:(%edi)
 80496c7:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 80496cc:	89 df                	mov    %ebx,%edi
 80496ce:	f2 ae                	repnz scas %es:(%edi),%al
 80496d0:	f7 d1                	not    %ecx
 80496d2:	89 ce                	mov    %ecx,%esi
 80496d4:	83 ee 01             	sub    $0x1,%esi
 80496d7:	0f 84 5c 04 00 00    	je     8049b39 <submitr+0x75f>
 80496dd:	89 d5                	mov    %edx,%ebp
 80496df:	bf d9 ff 00 00       	mov    $0xffd9,%edi
 80496e4:	0f b6 13             	movzbl (%ebx),%edx
 80496e7:	8d 4a d6             	lea    -0x2a(%edx),%ecx
 80496ea:	b8 01 00 00 00       	mov    $0x1,%eax
 80496ef:	80 f9 0f             	cmp    $0xf,%cl
 80496f2:	77 0a                	ja     80496fe <submitr+0x324>
 80496f4:	89 f8                	mov    %edi,%eax
 80496f6:	d3 e8                	shr    %cl,%eax
 80496f8:	83 f0 01             	xor    $0x1,%eax
 80496fb:	83 e0 01             	and    $0x1,%eax
 80496fe:	80 fa 5f             	cmp    $0x5f,%dl
 8049701:	0f 94 c1             	sete   %cl
 8049704:	38 c1                	cmp    %al,%cl
 8049706:	73 0c                	jae    8049714 <submitr+0x33a>
 8049708:	89 d0                	mov    %edx,%eax
 804970a:	83 e0 df             	and    $0xffffffdf,%eax
 804970d:	83 e8 41             	sub    $0x41,%eax
 8049710:	3c 19                	cmp    $0x19,%al
 8049712:	77 08                	ja     804971c <submitr+0x342>
 8049714:	88 55 00             	mov    %dl,0x0(%ebp)
 8049717:	8d 6d 01             	lea    0x1(%ebp),%ebp
 804971a:	eb 62                	jmp    804977e <submitr+0x3a4>
 804971c:	80 fa 20             	cmp    $0x20,%dl
 804971f:	75 09                	jne    804972a <submitr+0x350>
 8049721:	c6 45 00 2b          	movb   $0x2b,0x0(%ebp)
 8049725:	8d 6d 01             	lea    0x1(%ebp),%ebp
 8049728:	eb 54                	jmp    804977e <submitr+0x3a4>
 804972a:	8d 42 e0             	lea    -0x20(%edx),%eax
 804972d:	3c 5f                	cmp    $0x5f,%al
 804972f:	76 09                	jbe    804973a <submitr+0x360>
 8049731:	80 fa 09             	cmp    $0x9,%dl
 8049734:	0f 85 bb 03 00 00    	jne    8049af5 <submitr+0x71b>
 804973a:	83 ec 0c             	sub    $0xc,%esp
 804973d:	0f b6 d2             	movzbl %dl,%edx
 8049740:	52                   	push   %edx
 8049741:	68 94 a3 04 08       	push   $0x804a394
 8049746:	6a 08                	push   $0x8
 8049748:	6a 01                	push   $0x1
 804974a:	8d 84 24 68 80 00 00 	lea    0x8068(%esp),%eax
 8049751:	50                   	push   %eax
 8049752:	e8 69 f1 ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049757:	0f b6 84 24 6c 80 00 	movzbl 0x806c(%esp),%eax
 804975e:	00 
 804975f:	88 45 00             	mov    %al,0x0(%ebp)
 8049762:	0f b6 84 24 6d 80 00 	movzbl 0x806d(%esp),%eax
 8049769:	00 
 804976a:	88 45 01             	mov    %al,0x1(%ebp)
 804976d:	0f b6 84 24 6e 80 00 	movzbl 0x806e(%esp),%eax
 8049774:	00 
 8049775:	88 45 02             	mov    %al,0x2(%ebp)
 8049778:	83 c4 20             	add    $0x20,%esp
 804977b:	8d 6d 03             	lea    0x3(%ebp),%ebp
 804977e:	83 c3 01             	add    $0x1,%ebx
 8049781:	83 ee 01             	sub    $0x1,%esi
 8049784:	0f 85 5a ff ff ff    	jne    80496e4 <submitr+0x30a>
 804978a:	e9 aa 03 00 00       	jmp    8049b39 <submitr+0x75f>
 804978f:	83 ec 04             	sub    $0x4,%esp
 8049792:	53                   	push   %ebx
 8049793:	56                   	push   %esi
 8049794:	55                   	push   %ebp
 8049795:	e8 66 f0 ff ff       	call   8048800 <write@plt>
 804979a:	83 c4 10             	add    $0x10,%esp
 804979d:	85 c0                	test   %eax,%eax
 804979f:	7f 0f                	jg     80497b0 <submitr+0x3d6>
 80497a1:	e8 8a f0 ff ff       	call   8048830 <__errno_location@plt>
 80497a6:	83 38 04             	cmpl   $0x4,(%eax)
 80497a9:	75 0f                	jne    80497ba <submitr+0x3e0>
 80497ab:	b8 00 00 00 00       	mov    $0x0,%eax
 80497b0:	01 c6                	add    %eax,%esi
 80497b2:	29 c3                	sub    %eax,%ebx
 80497b4:	75 d9                	jne    804978f <submitr+0x3b5>
 80497b6:	85 ff                	test   %edi,%edi
 80497b8:	79 69                	jns    8049823 <submitr+0x449>
 80497ba:	8b 44 24 18          	mov    0x18(%esp),%eax
 80497be:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80497c4:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 80497cb:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 80497d2:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 80497d9:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 80497e0:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 80497e7:	c7 40 18 77 72 69 74 	movl   $0x74697277,0x18(%eax)
 80497ee:	c7 40 1c 65 20 74 6f 	movl   $0x6f742065,0x1c(%eax)
 80497f5:	c7 40 20 20 74 68 65 	movl   $0x65687420,0x20(%eax)
 80497fc:	c7 40 24 20 73 65 72 	movl   $0x72657320,0x24(%eax)
 8049803:	c7 40 28 76 65 72 00 	movl   $0x726576,0x28(%eax)
 804980a:	83 ec 0c             	sub    $0xc,%esp
 804980d:	ff 74 24 14          	pushl  0x14(%esp)
 8049811:	e8 8a f0 ff ff       	call   80488a0 <close@plt>
 8049816:	83 c4 10             	add    $0x10,%esp
 8049819:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804981e:	e9 b9 02 00 00       	jmp    8049adc <submitr+0x702>
 8049823:	8b 44 24 08          	mov    0x8(%esp),%eax
 8049827:	89 44 24 40          	mov    %eax,0x40(%esp)
 804982b:	c7 44 24 44 00 00 00 	movl   $0x0,0x44(%esp)
 8049832:	00 
 8049833:	8d 44 24 4c          	lea    0x4c(%esp),%eax
 8049837:	89 44 24 48          	mov    %eax,0x48(%esp)
 804983b:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049840:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 8049847:	8d 44 24 40          	lea    0x40(%esp),%eax
 804984b:	e8 b6 fa ff ff       	call   8049306 <rio_readlineb>
 8049850:	85 c0                	test   %eax,%eax
 8049852:	7f 7d                	jg     80498d1 <submitr+0x4f7>
 8049854:	8b 44 24 18          	mov    0x18(%esp),%eax
 8049858:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 804985e:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049865:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 804986c:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049873:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 804987a:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049881:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049888:	c7 40 1c 20 66 69 72 	movl   $0x72696620,0x1c(%eax)
 804988f:	c7 40 20 73 74 20 68 	movl   $0x68207473,0x20(%eax)
 8049896:	c7 40 24 65 61 64 65 	movl   $0x65646165,0x24(%eax)
 804989d:	c7 40 28 72 20 66 72 	movl   $0x72662072,0x28(%eax)
 80498a4:	c7 40 2c 6f 6d 20 73 	movl   $0x73206d6f,0x2c(%eax)
 80498ab:	c7 40 30 65 72 76 65 	movl   $0x65767265,0x30(%eax)
 80498b2:	66 c7 40 34 72 00    	movw   $0x72,0x34(%eax)
 80498b8:	83 ec 0c             	sub    $0xc,%esp
 80498bb:	ff 74 24 14          	pushl  0x14(%esp)
 80498bf:	e8 dc ef ff ff       	call   80488a0 <close@plt>
 80498c4:	83 c4 10             	add    $0x10,%esp
 80498c7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80498cc:	e9 0b 02 00 00       	jmp    8049adc <submitr+0x702>
 80498d1:	83 ec 0c             	sub    $0xc,%esp
 80498d4:	8d 84 24 58 80 00 00 	lea    0x8058(%esp),%eax
 80498db:	50                   	push   %eax
 80498dc:	8d 44 24 3c          	lea    0x3c(%esp),%eax
 80498e0:	50                   	push   %eax
 80498e1:	8d 84 24 60 60 00 00 	lea    0x6060(%esp),%eax
 80498e8:	50                   	push   %eax
 80498e9:	68 9b a3 04 08       	push   $0x804a39b
 80498ee:	8d 84 24 68 20 00 00 	lea    0x2068(%esp),%eax
 80498f5:	50                   	push   %eax
 80498f6:	e8 15 ef ff ff       	call   8048810 <__isoc99_sscanf@plt>
 80498fb:	8b 44 24 4c          	mov    0x4c(%esp),%eax
 80498ff:	83 c4 20             	add    $0x20,%esp
 8049902:	3d c8 00 00 00       	cmp    $0xc8,%eax
 8049907:	0f 84 c4 00 00 00    	je     80499d1 <submitr+0x5f7>
 804990d:	83 ec 08             	sub    $0x8,%esp
 8049910:	8d 94 24 54 80 00 00 	lea    0x8054(%esp),%edx
 8049917:	52                   	push   %edx
 8049918:	50                   	push   %eax
 8049919:	68 ac a2 04 08       	push   $0x804a2ac
 804991e:	6a ff                	push   $0xffffffff
 8049920:	6a 01                	push   $0x1
 8049922:	ff 74 24 34          	pushl  0x34(%esp)
 8049926:	e8 95 ef ff ff       	call   80488c0 <__sprintf_chk@plt>
 804992b:	83 c4 14             	add    $0x14,%esp
 804992e:	ff 74 24 14          	pushl  0x14(%esp)
 8049932:	e8 69 ef ff ff       	call   80488a0 <close@plt>
 8049937:	83 c4 10             	add    $0x10,%esp
 804993a:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804993f:	e9 98 01 00 00       	jmp    8049adc <submitr+0x702>
 8049944:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049949:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 8049950:	8d 44 24 40          	lea    0x40(%esp),%eax
 8049954:	e8 ad f9 ff ff       	call   8049306 <rio_readlineb>
 8049959:	85 c0                	test   %eax,%eax
 804995b:	7f 74                	jg     80499d1 <submitr+0x5f7>
 804995d:	8b 44 24 18          	mov    0x18(%esp),%eax
 8049961:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049967:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 804996e:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049975:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 804997c:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049983:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 804998a:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049991:	c7 40 1c 20 68 65 61 	movl   $0x61656820,0x1c(%eax)
 8049998:	c7 40 20 64 65 72 73 	movl   $0x73726564,0x20(%eax)
 804999f:	c7 40 24 20 66 72 6f 	movl   $0x6f726620,0x24(%eax)
 80499a6:	c7 40 28 6d 20 73 65 	movl   $0x6573206d,0x28(%eax)
 80499ad:	c7 40 2c 72 76 65 72 	movl   $0x72657672,0x2c(%eax)
 80499b4:	c6 40 30 00          	movb   $0x0,0x30(%eax)
 80499b8:	83 ec 0c             	sub    $0xc,%esp
 80499bb:	ff 74 24 14          	pushl  0x14(%esp)
 80499bf:	e8 dc ee ff ff       	call   80488a0 <close@plt>
 80499c4:	83 c4 10             	add    $0x10,%esp
 80499c7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80499cc:	e9 0b 01 00 00       	jmp    8049adc <submitr+0x702>
 80499d1:	80 bc 24 4c 20 00 00 	cmpb   $0xd,0x204c(%esp)
 80499d8:	0d 
 80499d9:	0f 85 65 ff ff ff    	jne    8049944 <submitr+0x56a>
 80499df:	80 bc 24 4d 20 00 00 	cmpb   $0xa,0x204d(%esp)
 80499e6:	0a 
 80499e7:	0f 85 57 ff ff ff    	jne    8049944 <submitr+0x56a>
 80499ed:	80 bc 24 4e 20 00 00 	cmpb   $0x0,0x204e(%esp)
 80499f4:	00 
 80499f5:	0f 85 49 ff ff ff    	jne    8049944 <submitr+0x56a>
 80499fb:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049a00:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 8049a07:	8d 44 24 40          	lea    0x40(%esp),%eax
 8049a0b:	e8 f6 f8 ff ff       	call   8049306 <rio_readlineb>
 8049a10:	85 c0                	test   %eax,%eax
 8049a12:	7f 7b                	jg     8049a8f <submitr+0x6b5>
 8049a14:	8b 44 24 18          	mov    0x18(%esp),%eax
 8049a18:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049a1e:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049a25:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049a2c:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049a33:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049a3a:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049a41:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049a48:	c7 40 1c 20 73 74 61 	movl   $0x61747320,0x1c(%eax)
 8049a4f:	c7 40 20 74 75 73 20 	movl   $0x20737574,0x20(%eax)
 8049a56:	c7 40 24 6d 65 73 73 	movl   $0x7373656d,0x24(%eax)
 8049a5d:	c7 40 28 61 67 65 20 	movl   $0x20656761,0x28(%eax)
 8049a64:	c7 40 2c 66 72 6f 6d 	movl   $0x6d6f7266,0x2c(%eax)
 8049a6b:	c7 40 30 20 73 65 72 	movl   $0x72657320,0x30(%eax)
 8049a72:	c7 40 34 76 65 72 00 	movl   $0x726576,0x34(%eax)
 8049a79:	83 ec 0c             	sub    $0xc,%esp
 8049a7c:	ff 74 24 14          	pushl  0x14(%esp)
 8049a80:	e8 1b ee ff ff       	call   80488a0 <close@plt>
 8049a85:	83 c4 10             	add    $0x10,%esp
 8049a88:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049a8d:	eb 4d                	jmp    8049adc <submitr+0x702>
 8049a8f:	83 ec 08             	sub    $0x8,%esp
 8049a92:	8d 84 24 54 20 00 00 	lea    0x2054(%esp),%eax
 8049a99:	50                   	push   %eax
 8049a9a:	8b 7c 24 24          	mov    0x24(%esp),%edi
 8049a9e:	57                   	push   %edi
 8049a9f:	e8 fc ec ff ff       	call   80487a0 <strcpy@plt>
 8049aa4:	83 c4 04             	add    $0x4,%esp
 8049aa7:	ff 74 24 14          	pushl  0x14(%esp)
 8049aab:	e8 f0 ed ff ff       	call   80488a0 <close@plt>
 8049ab0:	0f b6 17             	movzbl (%edi),%edx
 8049ab3:	b8 4f 00 00 00       	mov    $0x4f,%eax
 8049ab8:	83 c4 10             	add    $0x10,%esp
 8049abb:	29 d0                	sub    %edx,%eax
 8049abd:	75 13                	jne    8049ad2 <submitr+0x6f8>
 8049abf:	0f b6 57 01          	movzbl 0x1(%edi),%edx
 8049ac3:	b8 4b 00 00 00       	mov    $0x4b,%eax
 8049ac8:	29 d0                	sub    %edx,%eax
 8049aca:	75 06                	jne    8049ad2 <submitr+0x6f8>
 8049acc:	0f b6 47 02          	movzbl 0x2(%edi),%eax
 8049ad0:	f7 d8                	neg    %eax
 8049ad2:	85 c0                	test   %eax,%eax
 8049ad4:	0f 95 c0             	setne  %al
 8049ad7:	0f b6 c0             	movzbl %al,%eax
 8049ada:	f7 d8                	neg    %eax
 8049adc:	8b bc 24 4c a0 00 00 	mov    0xa04c(%esp),%edi
 8049ae3:	65 33 3d 14 00 00 00 	xor    %gs:0x14,%edi
 8049aea:	0f 84 a9 00 00 00    	je     8049b99 <submitr+0x7bf>
 8049af0:	e9 9f 00 00 00       	jmp    8049b94 <submitr+0x7ba>
 8049af5:	a1 dc a2 04 08       	mov    0x804a2dc,%eax
 8049afa:	8b 7c 24 18          	mov    0x18(%esp),%edi
 8049afe:	89 07                	mov    %eax,(%edi)
 8049b00:	a1 1b a3 04 08       	mov    0x804a31b,%eax
 8049b05:	89 47 3f             	mov    %eax,0x3f(%edi)
 8049b08:	89 f8                	mov    %edi,%eax
 8049b0a:	83 c7 04             	add    $0x4,%edi
 8049b0d:	83 e7 fc             	and    $0xfffffffc,%edi
 8049b10:	29 f8                	sub    %edi,%eax
 8049b12:	be dc a2 04 08       	mov    $0x804a2dc,%esi
 8049b17:	29 c6                	sub    %eax,%esi
 8049b19:	83 c0 43             	add    $0x43,%eax
 8049b1c:	c1 e8 02             	shr    $0x2,%eax
 8049b1f:	89 c1                	mov    %eax,%ecx
 8049b21:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049b23:	83 ec 0c             	sub    $0xc,%esp
 8049b26:	ff 74 24 14          	pushl  0x14(%esp)
 8049b2a:	e8 71 ed ff ff       	call   80488a0 <close@plt>
 8049b2f:	83 c4 10             	add    $0x10,%esp
 8049b32:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049b37:	eb a3                	jmp    8049adc <submitr+0x702>
 8049b39:	8d 84 24 4c 40 00 00 	lea    0x404c(%esp),%eax
 8049b40:	50                   	push   %eax
 8049b41:	ff 74 24 18          	pushl  0x18(%esp)
 8049b45:	ff 74 24 18          	pushl  0x18(%esp)
 8049b49:	ff 74 24 18          	pushl  0x18(%esp)
 8049b4d:	68 20 a3 04 08       	push   $0x804a320
 8049b52:	68 00 20 00 00       	push   $0x2000
 8049b57:	6a 01                	push   $0x1
 8049b59:	8d bc 24 68 20 00 00 	lea    0x2068(%esp),%edi
 8049b60:	57                   	push   %edi
 8049b61:	e8 5a ed ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049b66:	b8 00 00 00 00       	mov    $0x0,%eax
 8049b6b:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049b70:	f2 ae                	repnz scas %es:(%edi),%al
 8049b72:	f7 d1                	not    %ecx
 8049b74:	8d 79 ff             	lea    -0x1(%ecx),%edi
 8049b77:	83 c4 20             	add    $0x20,%esp
 8049b7a:	89 fb                	mov    %edi,%ebx
 8049b7c:	8d b4 24 4c 20 00 00 	lea    0x204c(%esp),%esi
 8049b83:	8b 6c 24 08          	mov    0x8(%esp),%ebp
 8049b87:	85 ff                	test   %edi,%edi
 8049b89:	0f 85 00 fc ff ff    	jne    804978f <submitr+0x3b5>
 8049b8f:	e9 8f fc ff ff       	jmp    8049823 <submitr+0x449>
 8049b94:	e8 f7 eb ff ff       	call   8048790 <__stack_chk_fail@plt>
 8049b99:	81 c4 5c a0 00 00    	add    $0xa05c,%esp
 8049b9f:	5b                   	pop    %ebx
 8049ba0:	5e                   	pop    %esi
 8049ba1:	5f                   	pop    %edi
 8049ba2:	5d                   	pop    %ebp
 8049ba3:	c3                   	ret    

08049ba4 <init_timeout>:
 8049ba4:	53                   	push   %ebx
 8049ba5:	83 ec 08             	sub    $0x8,%esp
 8049ba8:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 8049bac:	85 db                	test   %ebx,%ebx
 8049bae:	74 24                	je     8049bd4 <init_timeout+0x30>
 8049bb0:	83 ec 08             	sub    $0x8,%esp
 8049bb3:	68 e3 92 04 08       	push   $0x80492e3
 8049bb8:	6a 0e                	push   $0xe
 8049bba:	e8 a1 eb ff ff       	call   8048760 <signal@plt>
 8049bbf:	85 db                	test   %ebx,%ebx
 8049bc1:	b8 00 00 00 00       	mov    $0x0,%eax
 8049bc6:	0f 48 d8             	cmovs  %eax,%ebx
 8049bc9:	89 1c 24             	mov    %ebx,(%esp)
 8049bcc:	e8 af eb ff ff       	call   8048780 <alarm@plt>
 8049bd1:	83 c4 10             	add    $0x10,%esp
 8049bd4:	83 c4 08             	add    $0x8,%esp
 8049bd7:	5b                   	pop    %ebx
 8049bd8:	c3                   	ret    

08049bd9 <init_driver>:
 8049bd9:	57                   	push   %edi
 8049bda:	56                   	push   %esi
 8049bdb:	53                   	push   %ebx
 8049bdc:	83 ec 28             	sub    $0x28,%esp
 8049bdf:	8b 74 24 38          	mov    0x38(%esp),%esi
 8049be3:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8049be9:	89 44 24 24          	mov    %eax,0x24(%esp)
 8049bed:	31 c0                	xor    %eax,%eax
 8049bef:	6a 01                	push   $0x1
 8049bf1:	6a 0d                	push   $0xd
 8049bf3:	e8 68 eb ff ff       	call   8048760 <signal@plt>
 8049bf8:	83 c4 08             	add    $0x8,%esp
 8049bfb:	6a 01                	push   $0x1
 8049bfd:	6a 1d                	push   $0x1d
 8049bff:	e8 5c eb ff ff       	call   8048760 <signal@plt>
 8049c04:	83 c4 08             	add    $0x8,%esp
 8049c07:	6a 01                	push   $0x1
 8049c09:	6a 1d                	push   $0x1d
 8049c0b:	e8 50 eb ff ff       	call   8048760 <signal@plt>
 8049c10:	83 c4 0c             	add    $0xc,%esp
 8049c13:	6a 00                	push   $0x0
 8049c15:	6a 01                	push   $0x1
 8049c17:	6a 02                	push   $0x2
 8049c19:	e8 32 ec ff ff       	call   8048850 <socket@plt>
 8049c1e:	83 c4 10             	add    $0x10,%esp
 8049c21:	85 c0                	test   %eax,%eax
 8049c23:	79 4e                	jns    8049c73 <init_driver+0x9a>
 8049c25:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049c2b:	c7 46 04 72 3a 20 43 	movl   $0x43203a72,0x4(%esi)
 8049c32:	c7 46 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%esi)
 8049c39:	c7 46 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%esi)
 8049c40:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049c47:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049c4e:	c7 46 18 63 72 65 61 	movl   $0x61657263,0x18(%esi)
 8049c55:	c7 46 1c 74 65 20 73 	movl   $0x73206574,0x1c(%esi)
 8049c5c:	c7 46 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%esi)
 8049c63:	66 c7 46 24 74 00    	movw   $0x74,0x24(%esi)
 8049c69:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049c6e:	e9 1f 01 00 00       	jmp    8049d92 <init_driver+0x1b9>
 8049c73:	89 c3                	mov    %eax,%ebx
 8049c75:	83 ec 0c             	sub    $0xc,%esp
 8049c78:	68 ac a3 04 08       	push   $0x804a3ac
 8049c7d:	e8 ee eb ff ff       	call   8048870 <gethostbyname@plt>
 8049c82:	83 c4 10             	add    $0x10,%esp
 8049c85:	85 c0                	test   %eax,%eax
 8049c87:	75 6c                	jne    8049cf5 <init_driver+0x11c>
 8049c89:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049c8f:	c7 46 04 72 3a 20 44 	movl   $0x44203a72,0x4(%esi)
 8049c96:	c7 46 08 4e 53 20 69 	movl   $0x6920534e,0x8(%esi)
 8049c9d:	c7 46 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%esi)
 8049ca4:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049cab:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049cb2:	c7 46 18 72 65 73 6f 	movl   $0x6f736572,0x18(%esi)
 8049cb9:	c7 46 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%esi)
 8049cc0:	c7 46 20 73 65 72 76 	movl   $0x76726573,0x20(%esi)
 8049cc7:	c7 46 24 65 72 20 61 	movl   $0x61207265,0x24(%esi)
 8049cce:	c7 46 28 64 64 72 65 	movl   $0x65726464,0x28(%esi)
 8049cd5:	66 c7 46 2c 73 73    	movw   $0x7373,0x2c(%esi)
 8049cdb:	c6 46 2e 00          	movb   $0x0,0x2e(%esi)
 8049cdf:	83 ec 0c             	sub    $0xc,%esp
 8049ce2:	53                   	push   %ebx
 8049ce3:	e8 b8 eb ff ff       	call   80488a0 <close@plt>
 8049ce8:	83 c4 10             	add    $0x10,%esp
 8049ceb:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049cf0:	e9 9d 00 00 00       	jmp    8049d92 <init_driver+0x1b9>
 8049cf5:	8d 7c 24 0c          	lea    0xc(%esp),%edi
 8049cf9:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
 8049d00:	00 
 8049d01:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 8049d08:	00 
 8049d09:	c7 44 24 14 00 00 00 	movl   $0x0,0x14(%esp)
 8049d10:	00 
 8049d11:	c7 44 24 18 00 00 00 	movl   $0x0,0x18(%esp)
 8049d18:	00 
 8049d19:	66 c7 44 24 0c 02 00 	movw   $0x2,0xc(%esp)
 8049d20:	6a 0c                	push   $0xc
 8049d22:	ff 70 0c             	pushl  0xc(%eax)
 8049d25:	8b 40 10             	mov    0x10(%eax),%eax
 8049d28:	ff 30                	pushl  (%eax)
 8049d2a:	8d 44 24 1c          	lea    0x1c(%esp),%eax
 8049d2e:	50                   	push   %eax
 8049d2f:	e8 9c ea ff ff       	call   80487d0 <__memmove_chk@plt>
 8049d34:	66 c7 44 24 1e 3b 6e 	movw   $0x6e3b,0x1e(%esp)
 8049d3b:	83 c4 0c             	add    $0xc,%esp
 8049d3e:	6a 10                	push   $0x10
 8049d40:	57                   	push   %edi
 8049d41:	53                   	push   %ebx
 8049d42:	e8 49 eb ff ff       	call   8048890 <connect@plt>
 8049d47:	83 c4 10             	add    $0x10,%esp
 8049d4a:	85 c0                	test   %eax,%eax
 8049d4c:	79 2a                	jns    8049d78 <init_driver+0x19f>
 8049d4e:	83 ec 0c             	sub    $0xc,%esp
 8049d51:	68 ac a3 04 08       	push   $0x804a3ac
 8049d56:	68 6c a3 04 08       	push   $0x804a36c
 8049d5b:	6a ff                	push   $0xffffffff
 8049d5d:	6a 01                	push   $0x1
 8049d5f:	56                   	push   %esi
 8049d60:	e8 5b eb ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049d65:	83 c4 14             	add    $0x14,%esp
 8049d68:	53                   	push   %ebx
 8049d69:	e8 32 eb ff ff       	call   80488a0 <close@plt>
 8049d6e:	83 c4 10             	add    $0x10,%esp
 8049d71:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049d76:	eb 1a                	jmp    8049d92 <init_driver+0x1b9>
 8049d78:	83 ec 0c             	sub    $0xc,%esp
 8049d7b:	53                   	push   %ebx
 8049d7c:	e8 1f eb ff ff       	call   80488a0 <close@plt>
 8049d81:	66 c7 06 4f 4b       	movw   $0x4b4f,(%esi)
 8049d86:	c6 46 02 00          	movb   $0x0,0x2(%esi)
 8049d8a:	83 c4 10             	add    $0x10,%esp
 8049d8d:	b8 00 00 00 00       	mov    $0x0,%eax
 8049d92:	8b 54 24 1c          	mov    0x1c(%esp),%edx
 8049d96:	65 33 15 14 00 00 00 	xor    %gs:0x14,%edx
 8049d9d:	74 05                	je     8049da4 <init_driver+0x1cb>
 8049d9f:	e8 ec e9 ff ff       	call   8048790 <__stack_chk_fail@plt>
 8049da4:	83 c4 20             	add    $0x20,%esp
 8049da7:	5b                   	pop    %ebx
 8049da8:	5e                   	pop    %esi
 8049da9:	5f                   	pop    %edi
 8049daa:	c3                   	ret    

08049dab <driver_post>:
 8049dab:	53                   	push   %ebx
 8049dac:	83 ec 08             	sub    $0x8,%esp
 8049daf:	8b 44 24 10          	mov    0x10(%esp),%eax
 8049db3:	8b 5c 24 1c          	mov    0x1c(%esp),%ebx
 8049db7:	83 7c 24 18 00       	cmpl   $0x0,0x18(%esp)
 8049dbc:	74 26                	je     8049de4 <driver_post+0x39>
 8049dbe:	83 ec 04             	sub    $0x4,%esp
 8049dc1:	ff 74 24 18          	pushl  0x18(%esp)
 8049dc5:	68 ba a3 04 08       	push   $0x804a3ba
 8049dca:	6a 01                	push   $0x1
 8049dcc:	e8 6f ea ff ff       	call   8048840 <__printf_chk@plt>
 8049dd1:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049dd6:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049dda:	83 c4 10             	add    $0x10,%esp
 8049ddd:	b8 00 00 00 00       	mov    $0x0,%eax
 8049de2:	eb 3e                	jmp    8049e22 <driver_post+0x77>
 8049de4:	85 c0                	test   %eax,%eax
 8049de6:	74 2c                	je     8049e14 <driver_post+0x69>
 8049de8:	80 38 00             	cmpb   $0x0,(%eax)
 8049deb:	74 27                	je     8049e14 <driver_post+0x69>
 8049ded:	83 ec 04             	sub    $0x4,%esp
 8049df0:	53                   	push   %ebx
 8049df1:	ff 74 24 1c          	pushl  0x1c(%esp)
 8049df5:	68 d1 a3 04 08       	push   $0x804a3d1
 8049dfa:	50                   	push   %eax
 8049dfb:	68 d9 a3 04 08       	push   $0x804a3d9
 8049e00:	68 6e 3b 00 00       	push   $0x3b6e
 8049e05:	68 ac a3 04 08       	push   $0x804a3ac
 8049e0a:	e8 cb f5 ff ff       	call   80493da <submitr>
 8049e0f:	83 c4 20             	add    $0x20,%esp
 8049e12:	eb 0e                	jmp    8049e22 <driver_post+0x77>
 8049e14:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049e19:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049e1d:	b8 00 00 00 00       	mov    $0x0,%eax
 8049e22:	83 c4 08             	add    $0x8,%esp
 8049e25:	5b                   	pop    %ebx
 8049e26:	c3                   	ret    
 8049e27:	66 90                	xchg   %ax,%ax
 8049e29:	66 90                	xchg   %ax,%ax
 8049e2b:	66 90                	xchg   %ax,%ax
 8049e2d:	66 90                	xchg   %ax,%ax
 8049e2f:	90                   	nop

08049e30 <__libc_csu_init>:
 8049e30:	55                   	push   %ebp
 8049e31:	57                   	push   %edi
 8049e32:	56                   	push   %esi
 8049e33:	53                   	push   %ebx
 8049e34:	e8 d7 ea ff ff       	call   8048910 <__x86.get_pc_thunk.bx>
 8049e39:	81 c3 c7 21 00 00    	add    $0x21c7,%ebx
 8049e3f:	83 ec 0c             	sub    $0xc,%esp
 8049e42:	8b 6c 24 20          	mov    0x20(%esp),%ebp
 8049e46:	8d b3 0c ff ff ff    	lea    -0xf4(%ebx),%esi
 8049e4c:	e8 a3 e8 ff ff       	call   80486f4 <_init>
 8049e51:	8d 83 08 ff ff ff    	lea    -0xf8(%ebx),%eax
 8049e57:	29 c6                	sub    %eax,%esi
 8049e59:	c1 fe 02             	sar    $0x2,%esi
 8049e5c:	85 f6                	test   %esi,%esi
 8049e5e:	74 25                	je     8049e85 <__libc_csu_init+0x55>
 8049e60:	31 ff                	xor    %edi,%edi
 8049e62:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8049e68:	83 ec 04             	sub    $0x4,%esp
 8049e6b:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049e6f:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049e73:	55                   	push   %ebp
 8049e74:	ff 94 bb 08 ff ff ff 	call   *-0xf8(%ebx,%edi,4)
 8049e7b:	83 c7 01             	add    $0x1,%edi
 8049e7e:	83 c4 10             	add    $0x10,%esp
 8049e81:	39 f7                	cmp    %esi,%edi
 8049e83:	75 e3                	jne    8049e68 <__libc_csu_init+0x38>
 8049e85:	83 c4 0c             	add    $0xc,%esp
 8049e88:	5b                   	pop    %ebx
 8049e89:	5e                   	pop    %esi
 8049e8a:	5f                   	pop    %edi
 8049e8b:	5d                   	pop    %ebp
 8049e8c:	c3                   	ret    
 8049e8d:	8d 76 00             	lea    0x0(%esi),%esi

08049e90 <__libc_csu_fini>:
 8049e90:	f3 c3                	repz ret 

Disassembly of section .fini:

08049e94 <_fini>:
 8049e94:	53                   	push   %ebx
 8049e95:	83 ec 08             	sub    $0x8,%esp
 8049e98:	e8 73 ea ff ff       	call   8048910 <__x86.get_pc_thunk.bx>
 8049e9d:	81 c3 63 21 00 00    	add    $0x2163,%ebx
 8049ea3:	83 c4 08             	add    $0x8,%esp
 8049ea6:	5b                   	pop    %ebx
 8049ea7:	c3                   	ret    
