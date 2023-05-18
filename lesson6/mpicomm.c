#include"myhead.h"
//split the comm to p*q 2d
void mesh2d(int p,int q,MPI_Comm comm,MPI_Comm tcomm,MPI_Comm *rowcomm,MPI_Comm *colcomm)
{
    int np, iam, color, key;
    int rowid = 0, colid = 0;

    MPI_Comm_size(comm, &np);
    MPI_Comm_rank(comm, &iam);
    if( p*q>np )
    {
        color = MPI_UNDEFINED;
        key = iam;
        MPI_Comm_split(comm, color, key, rowcomm);
        MPI_Comm_split(comm, color, key, colcomm);
        return;
    }
    key = iam;
    if(iam < p*q)
        color = 0;
    else
        color = MPI_UNDEFINED;
    MPI_Comm_split(comm, color, key, &tcomm);
    if(tcomm != MPI_COMM_NULL)
    {
        color = iam / q;
        MPI_Comm_split(tcomm, color, key, rowcomm);
        color = iam % q;
        MPI_Comm_split(tcomm, color, key, colcomm);
        if(iam < p*q)
        {
            MPI_Comm_rank(*rowcomm, &colid);
            MPI_Comm_rank(*colcomm, &rowid);
        }
    }
    printf("i am %d, colid %d, rowid %d \n", iam, colid, rowid);
}