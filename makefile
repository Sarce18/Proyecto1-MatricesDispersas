CFLAGS = -I

all: matriz.o main.o 
	gcc -g matriz.o proy1.o -o proy

matriz.o: matriz.c
	gcc -c matriz.c -o matriz.o

proy.o: proy1.c
	gcc -c proy1.c -o proy1.o

Matrix: 
	gcc -o Matrix proy.o matriz.o 
	
