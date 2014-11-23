# t0 - wczytany ciag
#t1 - licznik krokow
#t2 - do wczytywania litery z t0

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
	li	$v0,	8
	syscall
	li	$t1,	0
	j	loop
	
loop:
	lb	$t2,	($t0)
	addiu	$t0,	$t0,	1
	beq	$t2,	'\n',	exit
	bge	$t2,	'a',	potencjalna_mala
	sb	$t2,	-1($t0)
	
	j	loop
	
potencjalna_mala:
	ble	$t2,	'z',	mala
	j	loop
	
mala:
	addiu	$t1,	$t1,	1
	beq	$t1,	2,	zamien
	j	loop
	
zamien:
	li	$t1,	0
	addiu	$t2,	$t2,	-32
	sb	$t2,	-1($t0)
	j	loop
	
exit:
	li	$v0,	4
	syscall
	li	$v0,	10
	syscall
	