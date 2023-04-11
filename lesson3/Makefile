#makefile for lesson3

LIB =
INCL =

DEBUG = 
CC = gcc
MPI = mpicc

main : main.o mpit.o mat.o
	$(MPI) -o main main.o mpit.o mat.o

main.o : main.c
	$(MPI) -c main.c -o main.o

mpit.o : mpitest.c
	$(MPI) -c mpitest.c -o mpit.o

mat.o : matp.c
	$(MPI) -c matp.c -o mat.o

clean :
	rm *.o
	rm main