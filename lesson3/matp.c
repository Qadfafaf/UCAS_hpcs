#include"myhead.h"
void mat_multi(float* a,int ar,int ac,float* b,int br,int bc,float* c)
{
    int i=0,j=0,k=0;
    for(i=0;i<ar;i++)
        for(k=0;k<bc;k++)
            for(j=0;j<ac;j++)
            {
                c[i*bc+k] += a[i*ac+j]*b[j*bc+k];
            }
}
void sollowtansys(float *a,int ar,int ac,float *b,int br,int bc,float *c,int cr,int cc)
{
    int i,j;
    float btmp[1000];
    memset(btmp,0,1000);
    for(i=0;i<br;i++)
    for(j=0;j<bc;j++)
    {
        btmp[i*bc+j]=b[i*bc+j];
    }
    for(i=0;i<ac;i++)
    {
        c[i*cc] = btmp[i*cc]/a[i*ac+i];
        for(j=i+1;j<ar;j++)
        {
            btmp[j*cc]-=a[j*ac+i]*c[i*cc];
        }
    }
}
void mpisollowtansys(float *a,int ar,int ac,float *b,int br,int bc,float *c,int cr,int cc,MPI_Comm comm,int iam,int np)
{
    float u[1000];
    float v[1000];
    memset(u,0,1000);
    memset(v,0,1000);
    int i,j;
    int tag=1;
    MPI_Status st;
    int k=0;
    if(iam==0)
    {
        for(i=0;i<br;i++)
        for(j=0;j<bc;j++)
        {
            u[i*bc+j]=b[i*bc+j];
        }
    }
    for(i=iam;i<ac;i+=np)
    {
        k=i;
        if(i>0)
        {
            MPI_Recv(v, 10, MPI_FLOAT, (i-1+np)%np, tag, comm, &st);
        }
        c[k]=(u[i]+v[0])/a[i*ac+k];
        for(j=0;j<=np-3;j++)
        {
            v[j] = v[j+1] + u[i+j+1] - a[(i+j+1)*ac+k]*c[k];
        }
        v[np-2]=u[i+np-1]-a[(i+np-1)*ac+k]*c[k];
        MPI_Send(v, 10, MPI_FLOAT, (i+1)%np, tag, comm);
        for(j=i+np;j<ar;j++)
        {
            u[j]=u[j]-a[j*ac+k]*c[k];
        }
        k=k+1;
    }
}
void mpisolaxb(float *x,MPI_Comm comm,int iam,int np)
{
    float a[1000];
    //float x[1000];
    memset(a,0,1000);
    memset(x,0,1000);
    float at[1000];
    float xt[1000];
    memset(at,0,1000);
    memset(xt,0,1000);
    float b[1000];
    int br,bc;
    memset(b,0,1000);
    int ar,ac;
    int xr,xc;
    int i,j;
    if(iam==0)
    {
        FILE *fp=fopen("inputaxb","r");
        if(!fp)
        {
            printf("read file error!\n");
        }
        fscanf(fp,"%d",&ar);
        fscanf(fp,"%d",&ac);
        for(i=0;i<ar;i++)
        for(j=0;j<ac;j++)
        {
            fscanf(fp,"%f",&at[j*ac+i]);//transposed
        }
        fscanf(fp,"%d",&xr);
        fscanf(fp,"%d",&xc);
        for(i=0;i<xr;i++)
        for(j=0;j<xc;j++)
        {
            fscanf(fp,"%f",&xt[i*xc+j]);
        }
        fscanf(fp,"%d",&br);
        fscanf(fp,"%d",&bc);
        for(i=0;i<br;i++)
        for(j=0;j<bc;j++)
        {
            fscanf(fp,"%f",&b[i*bc+j]);
        }
    }
    MPI_Bcast(&ar, 1, MPI_INT, 0, comm);
    MPI_Bcast(&ac, 1, MPI_INT, 0, comm);
    MPI_Bcast(&xr, 1, MPI_INT, 0, comm);
    MPI_Bcast(&xc, 1, MPI_INT, 0, comm);
    MPI_Scatter(at,ar*ac/np,MPI_FLOAT,a,ar*ac/np,MPI_FLOAT,0,comm);
    MPI_Scatter(xt,xr*xc/np,MPI_FLOAT,x,xr*xc/np,MPI_FLOAT,0,comm);
    // printf("%d\n",iam);
    // for(i=0;i<ar*ac/np;i++)
    // {
    //     printf("%f ",a[i]);
    // }
    // for(i=0;i<xr*xc/np;i++)
    // {
    //     printf("%f ",x[i]);
    // }
    // printf("\n");
    int axr = ar;
    ar = ac/2;
    ac = axr;
    xr /= 2;
    float ax[1000];
    memset(ax,0,1000);
    //printf("%f %f\n",x[0],x[1]);
    for(i=0;i<ar;i++)
    {
        for(j=0;j<ac;j++)
        {
            ax[j]+=a[i*ac+j]*x[i];
            //printf("%f %f\n",a[i*ac+j],x[i]);
            //printf("%d %d %f\n",iam,j,ax[j]);
        }
    }
    //MPI_Barrier(comm);
    float axe[1000];
    memset(axe,0,1000);
    MPI_Reduce(ax,axe,axr,MPI_FLOAT,MPI_SUM,0,comm);
    if(iam==0)
    {
        for(i=0;i<axr;i++)
        {
            x[i]=axe[i]+b[i];
            printf("%f\n",x[i]);
        }
    }
}