.data
str1:	.asciiz	"Podaj ciag: "
input:	.space 80
	.text
	
main:
	li	$v0,	4
	la	$a0,	str1
	syscall
	
	la	$a1,	80
	la	$a0,	input
	la	$t0,	input
	la	$t1,	input
	li	$v0,	8
	syscall

	
	j	do_kropki
	
	
do_kropki:
	lb	$t2,	($t1)
	addiu	$t1,	$t1,	1
	beq	$t2,	'.',	one_step_back
	j	do_kropki
	
one_step_back:
	move	$t6,	$t1
	addiu	$t6,	$t6,	1
	move	$t7,	$t6
	subu	$t1,	$t1,	2
	
	j	zamien1

zamien1:
	lb	$t2,	($t0)
	lb	$t3,	($t1)
	blt	$t1,	$t0,	od_kropki			##
	sb	$t2,	($t1)
	sb	$t3,	($t0)
								##
	addiu	$t0,	$t0,	1
	subu	$t1,	$t1,	1
	j	zamien1
	
od_kropki:
	addiu	$t7,	$t7,	1
	lb	$t2,	($t7)
	beq	$t2,	'\n',	one_step_back1
	j	od_kropki
	
one_step_back1:
	subu	$t6,	$t6,	1
	subu	$t7,	$t7,	1
	#move	$t7,	$t6
	#subu	$t6,	$t6,	1
	
	j	zamien2

zamien2:	
	lb	$t2,	($t6)
	lb	$t3,	($t7)
	blt	$t7,	$t6,	exit			##
	sb	$t2,	($t7)
	sb	$t3,	($t6)
								##
	addiu	$t6,	$t6,	1
	subu	$t7,	$t7,	1
	j	zamien2
	
			
	
exit:
	li	$v0,	4
	syscall
	li	$v0,	10
	syscall