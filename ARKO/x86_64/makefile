all:	asm main link

link:	asm.o main.o
	gcc -m64 main.o asm.o -lglut -lGL -lGLEW -lGLU -o program

main:	main.c
	gcc -c -m64 main.c -lglut -lGL -lGLEW -lGLU -o main.o

asm:	asm.s
	nasm -f elf64 asm.s -o asm.o

clean:
	rm *.o *~
