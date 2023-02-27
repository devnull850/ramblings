
	.section .text
	.globl _start

_start:

	xor	%eax,%eax
	mov	$0xc4,%al
	movzx	%al,%eax
	cdq
	mov	%edx,%edi
	mov	$0x3c,%eax
	syscall

