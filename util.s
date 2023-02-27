
	.section .text
	.globl checksum

checksum:

	push	%rbp
	mov	%rsp,%rbp
	sub	$0x20,%rsp
	mov	%rsi,-0x10(%rbp)
	mov	%rdx,-0x8(%rbp)
	mov	%edi,-0x1c(%rbp)
	mov	-0x10(%rbp),%rdi
	mov	(%rdi),%edi
	mov	-0x8(%rbp),%rsi
	mov	(%rsi),%esi
	mov	-0x1c(%rbp),%al
	movzx	%al,%eax
	cdq
	add	%edi,%eax
	adc	%esi,%edx
	mov	-0x10(%rbp),%rdi
	mov	-0x8(%rbp),%rsi
	mov	%eax,(%rdi)
	mov	%edx,(%rsi)
	add	$0x20,%rsp
	pop	%rbp
	ret

