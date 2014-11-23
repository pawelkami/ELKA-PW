# Pawe³ Kamiñski - listopad 2014
# Architektura Komputerow (ARKO)
# Semestr 3, grupa dziekanska 3I3
# Program rysuje tor lotu pocisku na 24-bitowej bitmapie
#****************************************************************************************************

# Uzywane rejestry:
# t0 - deskryptor pliku
# t1 - zaalokowany bufor
# t2 - szerokosc bitmapy
# t3 - wysokosc bmp
# t4 - Vx
# t5 - Vy
# t6- (g*t^2)/2
# t7 - szerokosc z uwzglednionym paddingiem
# s0 - czas probkowania
# s1 - rozmiar tablicy
# s2 - kolorek
# s3 - wspolrzedna x
# s4 - wspolrzedna y
# s5 - pomocniczy
# s6 - pomocniczy
# s7 - pomocniczy
# t8 - Vx nie zmieniony warunkami lotu - potrzebny przy odbijaniu
# t9 - Vy z ostatniego odbicia - potrzebny przy wyliczaniu kolejnego odbicia
###########################################################	
			.data
input:			.asciiz		"input.bmp"
header:			.space 		54
strErr:			.asciiz		"Blad przy wczytywaniu pliku\n"
coordinate_x:		.asciiz		"Podaj wspolrzedna x [0-1024]:\n"
coordinate_y:		.asciiz		"Podaj wspolrzedna y [0-1024]:\n"
input_Vx:		.asciiz		"Podaj predkosc wzdluz osi x:\n"
input_Vy:		.asciiz		"Podaj predkosc wzdluz osi y:\n"
	.text
	
	.globl main
main:
	# wczytywane pliku
	li	$v0,	13		# 13 - otworz plik
	la	$a0,	input		# sciazka do pliku
	li	$a1,	0		# flaga read
	li	$a2,	0
	syscall
	move	$t0,	$v0		# t0 - deskryptor
	
	beq	$t0,	0xffffffff,	found_error
	
	# czytanie naglowka
	li	$v0,	14		# 14 - czytanie z pliku
	la	$a0,	($t0)		# deskryptor pliku
	la	$a1,	header		# naglowek
	li	$a2,	54		# 54 - rozmiar naglowka
	syscall
	
	# odczytujemy rozmiar tablicy pikseli z naglowka i alokujemy pamiec
	la 	$s1, 	header
	li 	$v0, 	9		# wywolujemy SBRK podajac dlugosc bufora w a0
	ulw 	$a0, 	34($s1)		# pod 34 bajtem naglowka mamy rozmiar tablicy
	move 	$s1, 	$a0 		# s1 = rozmiar tablicy
	syscall
	move	$t1,	$v0		# adres zaalokowanej pamieci
	
	# zamykanie pliku
	li 	$v0, 	16		# 16 - close file
	move 	$a0, 	$t0
	syscall
	
	# odczyt szerokosci i dlugosci obrazu i zapis w rejestrach
	la	$s2,	header
	ulw	$t2,	18($s2)		# 18 bajt to szerokosc bmp
	ulw	$t3,	22($s2)		# 22 bajt to wysokosc bmp
	
	move	$s3,	$t1		# ladujemy bufor
	li	$s4,	0xff		# w s4 ustawiamy kolor bialy
	addu	$s5,	$s3,	$s1	# w s5 zapisujemy ostatni piksel


	# wypelnianie planszy bialym kolorem
white_it_up:
	usw	$s4,	($s3)		# kolorujemy na bialo
	addi	$s3,	$s3,	1	# kolejny pixel
	blt	$s3,	$s5, 	white_it_up
	
	# padding
padding:	

	mulu	$t7,	$t2,	3	# mnozymy szerokosc przez 3 poniewaz na jeden pixel przypadaja 3 bajty
	andi	$t6,	$t7,	3	# szybsze mod 4
	beqz	$t6,	padding_done	# jesli nie trzeba robic paddingu to przeskocz dalej
	li	$s5,	4		# ladujemy 4 do rejestru zeby potem od czworki odjac reszte z dzielenia
					# dzieki czemu bedziemy wiedzieli ile dodac do szerokosci
	subu	$t6,	$s5,	$t6	# ile musimy dodac
	addu	$t7,	$t7,	$t6	# dodajemy i otrzymujemy szerokosc po paddingu
	
	# pobieramy wspolrzedne od uzytkownika
padding_done:
	li	$v0,	4		# print string
	la	$a0,	coordinate_x	# pobranie wspolrzednej x od uzytkownika
	syscall
	li	$v0,	5		# read_int
	syscall
	move 	$s3,	$v0		# zapisanie x do s3
	li	$v0,	4		# print string
	la	$a0,	coordinate_y	# pobieramy y
	syscall
	li	$v0,	5		# read_int
	syscall
	move	$s4,	$v0		# zapisanie y do s4
	
	li	$v0,	4		# print string
	la	$a0,	input_Vx	# pobieramy predkosc Vx
	syscall
	li	$v0,	5		# read_int
	syscall
	move 	$t4,	$v0		# t4 = Vx
	move	$t8, 	$t4		# t8 = Vx - bedzie potrzebny przy odbijaniu
	
	li	$v0,	4		# print string
	la	$a0,	input_Vy
	syscall
	li	$v0,	5		# pobranie predkosci Vy
	syscall
	move	$t5,	$v0		# t5 = Vy
	move	$t9, 	$t5		# t9 = Vy - potrzebne przy odbijaniu
	
	# czas probkowania oraz stala (g*t^2)/2

					# przyspieszenie ziemskie = 1024
	li	$s0,	10		# czas probkowania
	mulu	$s5,	$s0,	$s0 	# t^2   ->   (g*t^2) bo przyspieszenie ziemskie znosi przecinki 10 w prawo i 10 w lewo
	sra	$t6,	$s5,	1	# czyli dzielimy przez 2 wiec otrzymujemy (g*t^2)/2
	
	# wyliczamy x i y
	
	mulu	$s3,	$s3,	$t2	# x razy szerokosc obrazka
	srl	$s3, 	$s3,	10	# przesuwamy przecinek
	
	mulu	$s4,	$s4,	$t3	# y razy wysokosc obrazka
	srl	$s4, 	$s4,	10	# przesuwamy przecinek
	
	li	$s2,	0xFF00		# do koloru
	
	
set_Pixel:
	li	$s7, 	3		# bo pixel = 3 bajty
	move	$s5,	$t1		# wczytujemy adres bufora
	move	$s6,	$s3		# kopiujemy x na ktorym bedziemy mogli teraz pracowac
	mulu	$s6,	$s6,	$s7	# x *= 3
	addu	$s5,	$s5,	$s6	# dodajemy x do bufora
	mulu	$s6,	$s4,	$t7	# pomnoz y przez szerokosc
	addu	$s5,	$s5,	$s6	# doloz y do pozycji bufora
	
	# Kolorowanie
	sb	$zero,	($s5)		
	sb	$zero,	1($s5)
	sb	$s2,	2($s5)
	
	# wyliczamy nowe wspolrzedne
	mulu	$s5,	$t5,	$s0	# Vy * t
	sra	$s5, 	$s5,	10	# przesuwamy przecinek
	subu	$s5,	$s5,	$t6	# Vy * t - (g*t^2)/2
	addu	$s4,	$s4,	$s5	# wyliczamy wspolrzedna Y
	ble	$s4,	0,	impact_bottom
	bge	$s4,	$t3,	impact_top		
	
	mulu	$s5,	$t4,	$s0	# Vx * t    
	sra	$s5, 	$s5,	10	# przesuwamy przecinek
	addu	$s3,	$s3,	$s5	# wyliczamy wspolrzedna X
	bge	$s3,	$t2,	impact_right	
	ble	$s3,	0,	impact_left               
                           
	subu	$t5,	$t5,	$s0	# Vy = Vy - g*t
	
	j	set_Pixel
	
	# uderzamy w podloge
impact_bottom:

	li	$s2,	0x00FF
	move	$t4,	$t8
	mulu	$t4,	$t4,	120
	sra	$t4,	$t4,	7	# Vx = 120/128 wczesniejszej wartosci
	beqz	$t4,	exit
	
	move	$t5,	$t9
	mulu	$t5,	$t5,	120	# Vy = 120/128 wczesniejszej wartosci
	sra	$t5,	$t5,	7	# dziele przez 128
	beqz	$t5,	exit
	
	li	$s4,	0
	mulu	$s5,	$t4,	$s0	# s5 = Vx * t    
	sra	$s5, 	$s5,	10	# usytuowanie przecinka w dobrym miejscu
	addu	$s3,	$s3,	$s5	# wyliczamy X
	
	move	$t8,	$t4		# zapamietuje nowe wartosci Vx i Vy
	move	$t9,	$t5
		
	bge	$s3,	$t2,	impact_right
	blt	$s3,	0,	impact_left

	j	set_Pixel
	
	# uderzamy w sufit
impact_top:	
	bge	$s3,	$t2,	exit	# jak wpadnie w prawy gorny kat - blokada programu
	
	li	$s2,	0x00FF		# kolorek dla odbicia
	move	$t4,	$t8
	mulu	$t4,	$t4,	120
	sra	$t4,	$t4,	7	# zmniejszamy Vx z powodu utraty energii
	beqz	$t4,	exit	
	
	mul	$t5,	$t5,	-120	# zmniejszam Vy i zmieniam kierunek ruchu
	sra	$t5,	$t5,	7
	beqz	$t5,	exit

	mul	$s5,	$t4,	$s0	#  Vx * t    
	sra	$s5, 	$s5,	10	# przesuniecie przecinka
	addu	$s3,	$s3,	$s5	# X = X0 + dX(s5)
	
	bge	$s3,	$t2,	impact_right
	ble	$s3,	0,	impact_left
	
	j	set_Pixel
	
	# uderzamy w prawa sciane
impact_right:					
	li	$s2,	0x8888			# kolorek dla odbicia
	move	$t4,	$t8
	mulu	$t4,	$t4,	-120
	sra	$t4,	$t4,	7	# zmniejszam wartosc skladowej Vx 
	beqz	$t4,	exit	

	mulu	$t5,	$t5,	120	# zmniejszam Vy
	sra	$t5,	$t5,	7
	beqz	$t5,	exit
	
	move	$s3,	$t2
	mulu	$s5,	$t5,	$s0	# Vy * t
	sra	$s5, 	$s5,	10	# usytuowanie przecinka w dobrym miejscu
	subu	$s5,	$s5,	$t6	# Vy * t - (g*t^2)/2
	addu	$s4,	$s4,	$s5	# wyliczamy Y
	
	move	$t8,	$t4		# zapamietuje nowe wartosci Vx
	
	ble	$s4,	0,	impact_bottom
	bge	$s4,	$t3,	impact_top
	
	j	set_Pixel
	
	# uderzamy w lewa sciane
impact_left:		
	li	$s2,	0x8888		# kolorek do odbicia
	move	$t4,	$t8
	mulu	$t4,	$t4,	-120	# minus bo zmieniam kierunek
	sra	$t4,	$t4,	7	# zmniejszam wartosc skladowej Vx 
	beqz	$t4,	exit	
	
	mulu	$t5,	$t5,	120	# zmniejszam Vy
	sra	$t5,	$t5,	7	# dziele przez 128 zeby uzyskac ulamek
	beqz	$t5,	exit
	
	li	$s3,	0		# jezeli przekroczyl bitmape to ustawiamy ze w tej chwili dotyka sciany
	mulu	$s5,	$t5,	$s0	# Vy * t
	sra	$s5, 	$s5,	10	# przesuwamy przecinek
	subu	$s5,	$s5,	$t6	# Vy * t - (g*t^2)/2
	addu	$s4,	$s4,	$s5	# wyliczam Y
	
	move	$t8,	$t4		# zapamietuje nowe wartosci Vx i Vy
	
	ble	$s4,	0,	impact_bottom
	bge	$s4,	$t3,	impact_top
	
	j	set_Pixel
	
	
exit:
	# otwieramy plik do zapisu
	li 	$v0, 	13 		# 13 - open file
	la 	$a0, 	input 		# otwieramy do zapisu input.bmp
	li 	$a1, 	1 		# zapis
	li	$a2,	0
	syscall
	move 	$t0, 	$v0 		# zapisujemy deskryptor pliku
	
	# zapisujemy naglowek do pliku wynikowego
	li 	$v0, 	15		# 15 - write to file
	move 	$a0, 	$t0		# deskryptor pliku
	la 	$a1, 	header 		# zapisujemy naglowek
	li 	$a2, 	54 		# dlugosc naglowka
	syscall	
	# zapisujemy tablice pikseli do pliku
	li 	$v0, 	15		# 15 - write to file
	move 	$a0, 	$t0		# deskryptor pliku
	la 	$a1, 	($t1)		# zapisujemy z bufora wynikowego funkcji
	move 	$a2, 	$s1		# dlugosc tablicy pikseli
	syscall	
	#zamykanie pliku
	li 	$v0, 	16		# 16 -  close file
	move 	$a0, 	$t0		# deskryptor pliku
	syscall
	# zakonczenie programu
	li 	$v0, 	10
	syscall
	
found_error:
	# wystapil blad przy odczycie pliku - wyswietlamy komunikat
	li 	$v0, 	4
	la 	$a0, 	strErr	
	syscall
	# zakonczenie programu
	li 	$v0, 	10
	syscall
