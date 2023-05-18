#include"myhead.h"
int main(int argc, char *argv[])
{
    int iam, np;
    MPI_Comm comm;
    MPI_Init(&argc,&argv);
    MPI_Comm_dup(MPI_COMM_WORLD,&comm);
    MPI_Comm tcomm;
    MPI_Comm rowcomm,colcomm;
    int p = 2, q = 2;
    mesh2d(p,q,comm,tcomm,&rowcomm,&colcomm);
    MPI_Finalize();
}