#include"myhead.h"
void array_s_r(int iam, int np, MPI_Comm comm)
{
    int tag,front,next;
    int buf1[mpi_buf_size],buf2[mpi_buf_size];
    MPI_Status st;
    front = (iam-1+np)%np;
    next = (iam+1)%np;
    tag = 1;
    int i=0;
    for(i=0;i<mpi_buf_size;i++)
    {
        buf1[i]=iam;
    }
    MPI_Send(buf1, mpi_buf_size, MPI_INT, next, tag, comm);
    MPI_Recv(buf2, mpi_buf_size, MPI_INT, front, tag, comm, &st);
    printf("i am %d, i have %d, i received %d\n",iam,buf1[0],buf2[0]);
}

void array_sr(int iam, int np, MPI_Comm comm)
{
    int tag,front,next;
    int buf1[mpi_buf_size],buf2[mpi_buf_size];
    MPI_Status st;
    front = (iam-1+np)%np;
    next = (iam+1)%np;
    tag = 1;
    int i=0;
    for(i=0;i<mpi_buf_size;i++)
    {
        buf1[i]=iam;
    }
    MPI_Sendrecv(buf1, mpi_buf_size, MPI_INT, next, tag, buf2, mpi_buf_size, MPI_INT, front, tag, comm, &st);
    printf("i am %d, i have %d, i received %d\n",iam,buf1[0],buf2[0]);
}