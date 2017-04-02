	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$96, %rsp
	leaq	-24(%rbp), %rax
	leaq	-88(%rbp), %rcx
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, -92(%rbp)
	movq	%rax, %rdi
	movq	%rcx, %rsi
	callq	_init
	movq	-16(%rbp), %rdi
	callq	_get_option
	leaq	-88(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movl	-8(%rbp), %edx
	callq	_sort_argv
	leaq	-88(%rbp), %rdi
	callq	_print
	leaq	-88(%rbp), %rdi
	movl	-8(%rbp), %esi
	callq	_quit
	xorl	%eax, %eax
	addq	$96, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"a"

L_.str.1:                               ## @.str.1
	.asciz	"print hide file"

L_.str.2:                               ## @.str.2
	.asciz	"1"

L_.str.3:                               ## @.str.3
	.asciz	"One file per line"

L_.str.4:                               ## @.str.4
	.asciz	"R"

L_.str.5:                               ## @.str.5
	.asciz	"list subdirectory recursively"

L_.str.6:                               ## @.str.6
	.asciz	"r"

L_.str.7:                               ## @.str.7
	.asciz	"reverse sort"

L_.str.8:                               ## @.str.8
	.asciz	"t"

L_.str.9:                               ## @.str.9
	.asciz	"sort by time (new first)"

L_.str.10:                              ## @.str.10
	.asciz	"l"

L_.str.11:                              ## @.str.11
	.asciz	"print full info"

L_.str.12:                              ## @.str.12
	.asciz	"--"

L_.str.13:                              ## @.str.13
	.asciz	"end getting option"

	.section	__DATA,__data
	.globl	_g_argp                 ## @g_argp
	.align	4
_g_argp:
	.quad	L_.str
	.byte	0                       ## 0x0
	.space	7
	.quad	L_.str.1
	.quad	L_.str.2
	.byte	0                       ## 0x0
	.space	7
	.quad	L_.str.3
	.quad	L_.str.4
	.byte	0                       ## 0x0
	.space	7
	.quad	L_.str.5
	.quad	L_.str.6
	.byte	0                       ## 0x0
	.space	7
	.quad	L_.str.7
	.quad	L_.str.8
	.byte	0                       ## 0x0
	.space	7
	.quad	L_.str.9
	.quad	L_.str.10
	.byte	0                       ## 0x0
	.space	7
	.quad	L_.str.11
	.quad	L_.str.12
	.byte	0                       ## 0x0
	.space	7
	.quad	L_.str.13
	.space	24


.subsections_via_symbols
