	.file	"c8_1_4-2.cpp"
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
	leaq	x(%rip), %rax
	movq	%rax, p1(%rip)
	leaq	y(%rip), %rax
	movq	%rax, p2(%rip)
.L3:
	movq	p1(%rip), %rax
	movq	%rax, %rdx
	leaq	x(%rip), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cmpq	$199, %rax
	jg	.L4
	movq	p1(%rip), %rax
	leaq	4(%rax), %rdx
	movq	%rdx, p1(%rip)
	movq	p2(%rip), %rdx
	leaq	4(%rdx), %rcx
	movq	%rcx, p2(%rip)
	movl	(%rdx), %edx
	movl	%edx, (%rax)
	jmp	.L3
.L4:
	nop
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (tdm64-1) 5.1.0"
