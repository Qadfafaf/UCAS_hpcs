#include"myhead.h"
int main(int argc, char *argv[])
{
    int iam, np;
    MPI_Comm comm;
    MPI_Init(&argc,&argv);
    MPI_Comm_dup(MPI_COMM_WORLD,&comm);
    MPI_Comm_size(comm, &np);
    MPI_Comm_rank(comm, &iam);
    float a[1000];
    float b[1000];
    memset(a,0,1000);
    memset(b,0,1000);
    // int ar,ac;
    // int i,j;
    // if(iam == 0)
    // {
    //     FILE *fp=fopen("input","r");
    //     if(!fp)
    //     {
    //         printf("read file error!\n");
    //     }
    //     fscanf(fp,"%d",&ar);
    //     fscanf(fp,"%d",&ac);
    //     for(i=0;i<ar;i++)
    //     for(j=0;j<ac;j++)
    //     {
    //         fscanf(fp,"%f",&a[i*ac+j]);
    //     }
    // }
    int tag,front,next;
    MPI_Status st;
    front = (iam-1+np)%np;
    next = (iam+1)%np;
    tag = 1;
    // MPI_Bcast(&ac, 1, MPI_INT, 0, comm);
    // MPI_Bcast(&ar, 1, MPI_INT, 0, comm);
    int ar = 6, ac = 6;
    int i=0,j=0;
    for(i=0;i<ar;i++)
        for(j=0;j<ac;j++)
        {
            a[i*ac+j] = iam*100+i*ac+j;
        }
    for(i=0;i<ar;i++)
    {
        for(j=0;j<ac;j++)
        {
            printf("%f ",a[i*ac+j]);
        }
        printf("\n");
    }
    int m1 = 2, n1 = 2;
    int lda = ac;
    MPI_Type_vector(m1, n1, lda, MPI_FLOAT, &matrix00_22);
    MPI_Type_commit(&matrix00_22);
    int root = 0;
    int coor = 0;
    my_mpi_reduce(a,b,coor,root,iam,np,comm);
    MPI_Finalize();
}