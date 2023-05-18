#makefile for lesson6

LIB =
INCL =

DEBUG = 
CC = gcc
MPI = mpicc

main : main.o mpic.o
	$(MPI) -o main main.o mpic.o

main.o : main.c
	$(MPI) -c main.c -o main.o

mpic.o : mpicomm.c
	$(MPI) -c mpicomm.c -o mpic.o

clean :
	rm *.o
	rm main