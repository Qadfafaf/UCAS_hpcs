#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

#define PI atan(1)*4

void mpi_all2all(float *a,float *b,int len,int iam,int np,MPI_Comm comm);