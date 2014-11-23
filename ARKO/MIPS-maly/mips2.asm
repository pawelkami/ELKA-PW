.data
str1:	.asciiz	"Podaj ciag: "
input:	.space 80
output:	.space 80
	.text
	
main:
	li	$v0,	4
	la	$a0,	str1
	syscall
	
	la	$a1,	80
	la	$a0,	input
	la	$t0,	input
	la	$t1,	output
	li	$v0,	8
	syscall
	
	j	loop
	
loop:
	lb	$t2,	($t0)
	#addiu	$t0,	$t0,	1
	blt	$t2,	' ',	exit
	beq	$t2,	'(',	nawias
	addiu	$t0,	$t0,	1
	sb	$t2,	($t1)
	addi	$t1,	$t1,	1
	j	loop

nawias:

	lb	$t2,	($t0)
		addiu	$t0,	$t0,	1
	beq	$t2,	')',	nawias2
	bge	$t2,	'0',	potencjalna_cyfra
	sb	$t2,	($t1)
	addiu	$t1,	$t1,	1
	
	j	nawias
	
nawias2:
	sb	$t2,	($t1)
	addiu	$t1,	$t1,	1
	j	loop

potencjalna_cyfra:
	ble	$t2,	'9',	cyfra
	sb	$t2,	($t1)
	addiu	$t1,	$t1,	1
	j	nawias
	
cyfra:
	li	$t2,	'*'
	sb	$t2,	($t1)
	addiu	$t1,	$t1,	1
	j	nawias		
	
	
	
exit:
	la	$a0,	output
	li	$v0,	4
	syscall
	li	$v0,	10
	syscall