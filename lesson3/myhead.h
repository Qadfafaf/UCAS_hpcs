#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

#define PI atan(1)*4

#define mpi_buf_size 16
void array_s_r(int iam, int np, MPI_Comm comm);
void array_sr(int iam, int np, MPI_Comm comm);
void mat_multi(float *a,int ar,int ac,float *b,int br,int bc,float *c);
void sollowtansys(float *a,int ar,int ac,float *b,int br,int bc,float *c,int cr,int cc);
void mpisollowtansys(float *a,int ar,int ac,float *b,int br,int bc,float *c,int cr,int cc,MPI_Comm comm,int iam,int np);
void mpisolaxb(float *x,MPI_Comm comm,int iam,int np);