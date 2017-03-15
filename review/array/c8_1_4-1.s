	.file	"c8_1_4.cpp"
	.globl	x
	.bss
	.align 32
x:
	.space 200
	.globl	y
	.align 32
y:
	.space 200
	.globl	i
	.align 4
i:
	.space 4
	.globl	p1
	.align 8
p1:
	.space 8
	.globl	p2
	.align 8
p2:
	.space 8
	.text
	.globl	_Z4try1v
	.def	_Z4try1v;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z4try1v
_Z4try1v:
.LFB0:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	$0, i(%rip)
.L3:
	movl	i(%rip), %eax
	cmpl	$49, %eax
	jg	.L4
	movl	i(%rip), %ecx
	movl	i(%rip), %eax
	cltq                            ;cltq指令，该指令的作用是对eax的值进行符号扩展(sign-extend)，结果存在rax里
	leaq	0(,%rax,4), %rdx
	leaq	y(%rip), %rax
	movl	(%rdx,%rax), %edx
	movslq	%ecx, %rax
	leaq	0(,%rax,4), %rcx
	leaq	x(%rip), %rax
	movl	%edx, (%rcx,%rax)
	movl	i(%rip), %eax
	addl	$1, %eax
	movl	%eax, i(%rip)
	jmp	.L3
.L4:
	nop
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (tdm64-1) 5.1.0"
