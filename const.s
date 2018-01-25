	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str(%rip), %rdi
	movl	$5, %esi
	leaq	-4(%rbp), %rax
	movl	$5, -4(%rbp)
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	$10, (%rax)
	movb	$0, %al
	callq	_printf
	leaq	L_.str.1(%rip), %rdi
	movq	-16(%rbp), %rcx
	movl	(%rcx), %esi
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.2(%rip), %rdi
	leaq	-4(%rbp), %rsi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.3(%rip), %rdi
	movq	-16(%rbp), %rsi
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	xorl	%edx, %edx
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	movl	%edx, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"myConst value: %d\n"

L_.str.1:                               ## @.str.1
	.asciz	"nonConst value: %ud\n"

L_.str.2:                               ## @.str.2
	.asciz	"myConst address: %p\n"

L_.str.3:                               ## @.str.3
	.asciz	"nonConst address: %p\n"


.subsections_via_symbols
