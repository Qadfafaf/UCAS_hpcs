#makefile for lesson4

LIB =
INCL =

DEBUG = 
CC = gcc
MPI = mpicc

main : main.o mpit.o
	$(MPI) -o main main.o mpit.o

main.o : main.c
	$(MPI) -c main.c -o main.o

mpit.o : mpitran.c
	$(MPI) -c mpitran.c -o mpit.o

clean :
	rm *.o
	rm main