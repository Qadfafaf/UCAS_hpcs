#makefile for lesson4

LIB =
INCL =

DEBUG = 
CC = gcc
MPI = mpicc

main : main.o
	$(MPI) -o main main.o

main.o : main.c
	$(MPI) -c main.c -o main.o

clean :
	rm *.o
	rm main