#include"myhead.h"
#define paxb
int main(int argc, char *argv[])
{
    int iam, np;
    MPI_Comm comm;
    MPI_Init(&argc,&argv);
    MPI_Comm_dup(MPI_COMM_WORLD,&comm);
    MPI_Comm_size(comm, &np);
    MPI_Comm_rank(comm, &iam);
#ifdef mat
    float a[1000];
    float b[1000];
    float c[1000];
    memset(a,0,1000);
    memset(b,0,1000);
    memset(c,0,1000);
    float buffer[200];
#endif
//solve ax = b np=2

#ifdef paxb
    mpisolaxb(comm,iam,np);
#endif
//parallel solve triangular system np=3
#ifdef p_sts
    FILE *fp=fopen("input","r");
    double startwtime,endwtime;
    if(!fp)
    {
        printf("read file error!\n");
    }
    int ar,ac;
    int br,bc;
    int cr,cc;
    fscanf(fp,"%d",&ar);
    fscanf(fp,"%d",&ac);
    int i,j;
    for(i=0;i<ar;i++)
    for(j=0;j<ac;j++)
    {
        fscanf(fp,"%f",&a[i*ac+j]);
    }
    fscanf(fp,"%d",&br);
    fscanf(fp,"%d",&bc);
    for(i=0;i<br;i++)
    for(j=0;j<bc;j++)
    {
        fscanf(fp,"%f",&b[i*bc+j]);
    }
    cr = ac;
    cc = bc;
    if(iam == 0)
    {
        startwtime = MPI_Wtime();
        sollowtansys(a, ar, ac, b, br, bc, c, cr, cc);
        endwtime = MPI_Wtime();
        printf("single clock time = %f\n", endwtime-startwtime);
        for(i=0;i<cr;i++)
        for(j=0;j<cc;j++)
        {
            printf("%f\n",c[i*cc+j]);
        }
        memset(c,0,1000);
    }
    startwtime = MPI_Wtime();
    mpisollowtansys(a, ar, ac, b, br, bc, c, cr, cc, comm, iam, np);
    MPI_Gather(c,cr,MPI_FLOAT,buffer,cr,MPI_FLOAT,0,comm);
    for(i=0;i<np;i++)
    {
        for(j=0;j<cr;j++)
        {
            if(buffer[i*cr+j]!=0.0)
            {
                c[j]=buffer[i*cr+j];
            }
        }
    }
    if(iam==0)
    {
        endwtime = MPI_Wtime();
        printf("parallel clock time = %f\n", endwtime-startwtime);
        for(i=0;i<cr;i++)
        for(j=0;j<cc;j++)
        {
            printf("%f\n",c[i*cc+j]);
        }
    }
#endif
#ifdef matmul
    int i,j;
    int ar=3,ac=3;
    int br=3,bc=3;
    int cr=3,cc=3;
    for(i=0;i<ar;i++)
        for(j=0;j<ac;j++)
        {
            a[i*ac+j]=1;
            b[i*bc+j]=1;
        }
#endif
#ifdef arraysor
    array_s_r(iam, np, comm);
#endif
#ifdef arraysar
    array_sr(iam, np, comm);
#endif
    MPI_Finalize();
}