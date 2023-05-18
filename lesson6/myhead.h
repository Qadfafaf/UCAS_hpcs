#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

#define PI atan(1)*4

void mesh2d(int p,int q,MPI_Comm comm,MPI_Comm tcomm,MPI_Comm *rowcomm,MPI_Comm *colcomm);