#include"myhead.h"

void my_mpi_reduce(float *a,float *b,int coor,int root,int iam,int np,MPI_Comm comm)
{
    int tag = 1;
    MPI_Status st;
    int i = 0;
    MPI_Request request;
    MPI_Isend(a, 1, matrix00_22, root, tag, comm, &request);
    if(iam == root)
    {
        for(i=0;i<np;i++)
        {
            MPI_Recv(&b[i*2], 1, matrix00_22, i, tag, comm, &st);
        }
    }
    MPI_Barrier(comm);
    if(iam==0)
    {
        int j=0;
        int ar = 6,ac = 6;
        for(i=0;i<ar;i++)
        {
            for(j=0;j<ac;j++)
            {
                printf("%f ",b[i*ac+j]);
            }
            printf("\n");
        }
    }
}