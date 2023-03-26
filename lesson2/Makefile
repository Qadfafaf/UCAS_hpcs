#makefile for lesson2

LIB = -lm
INCL =

DEBUG = 
CC = gcc


main : main.o xn1.o bit.o
	$(CC)  main.o xn1.o bit.o $(LIB) -o main

main.o : main.c 
	$(CC) -c main.c -o main.o

xn1.o : xn1.c
	$(CC) -c xn1.c -o xn1.o

bit.o: bitre.c
	$(CC) -c bitre.c -o bit.o

clean :
	rm *.o
	rm main
