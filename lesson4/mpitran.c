#include"myhead.h"
void mpi_all2all(float *a,float *b,int len,int iam,int np,MPI_Comm comm)
{
    int front = iam;
    int next = iam;
    int tag = 1;
    MPI_Status st;
    next = (next+1)%np;
    front = (front+np-1)%np;
    int i;
    for(i=next*len/np;i<(next+1)*len/np;i++)
    {
        b[i]=a[i];
    }
    for(i=front*len/np;i<(front+1)*len/np;i++)
    {
        b[i]=a[i];
    }
    MPI_Send(&b[next*len/np], len/np, MPI_FLOAT, next, tag, comm);
    MPI_Send(&b[front*len/np], len/np, MPI_FLOAT, front, tag, comm);
    MPI_Recv(&b[next*len/np], len/np, MPI_FLOAT, next, tag, comm, &st);
    MPI_Recv(&b[front*len/np], len/np, MPI_FLOAT, front, tag, comm, &st);
    for(i=iam*len/np;i<next*len/np;i++)
    {
        b[i]=a[i];
    }
}