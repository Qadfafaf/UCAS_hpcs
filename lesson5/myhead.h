#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

MPI_Datatype matrix00_22;
#define PI atan(1)*4

void my_mpi_reduce(float *a,float *b,int coor,int root,int iam,int np,MPI_Comm comm);