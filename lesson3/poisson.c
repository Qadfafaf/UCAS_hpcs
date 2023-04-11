#include"myhead.h"
float sqnorm2(float *a, int lda, int m, int n)
{
    int i, j;
    float r=0.0;
    for(i=0; i<m; i++)
        for(j=0;j<n; j++)
            r += a[i*lda+j]*a[i*lda+j];
    return r;
}
void righths(float h,float *frhs,int lds,int m,int n,int iam,int np)
{
    int i, j, ioff, ir;

    ir = n % np;
    ioff = n / np;
    ioff = iam*ioff;
    if( iam < ir ) 
        ioff += iam;
    else 
        ioff += ir;
    for(i=1; i<=m; i++)
        for(j=1; j<n; j++)
            frhs[i*lds+j]= 2.0*sinf((i+ioff)*h)*sinf(j*h);
    return;
}
void laplace(MPI_Comm comm,int iam,int np,float h,float *work,int lds,int m,int n,float *frhs,float *sol)
{
    int i, j, k, front, next, max_iter=200;
    float sh=h*h, epsilon=1.0e-3, residual, r0, rt;
    MPI_Status st;
    front = (np+iam-1)%np;
    next = (iam+1)%np;
    if( iam == 0 ) 
        front = MPI_PROC_NULL;
    if( iam == np-1 )
        next = MPI_PROC_NULL;
    /* initialize the solver values */
    for(i=0; i<m+2; i++)
        for(j=0;j<n+2; j++)
            sol[i*lds+j] = 0.0;
    /* initial residual value */
    rt = sqnorm2( &frhs[lds+1], lds, m, n );
    MPI_Allreduce( &rt, &r0, 1, MPI_FLOAT, MPI_SUM, comm );
    r0 = sqrtf( r0 )*sh;
    /* iterate for solving discretized equations */
    for(k=0; k<max_iter; k++) 
    {
    /* calculate the residual in 5 point DS*/
        for(i=1; i<=m; i++)
            for(j=1; j<=n; j++)
                work[i*lds+j]=sh*frhs[i*lds+j]+sol[i*lds+j-1]+ \
                    sol[i*lds+j+1]+sol[(i-1)*lds+j]+ \
                    sol[(i+1)*lds+j]-4.0*sol[i*lds+j];
                rt = sqnorm2( &work[lds+1], lds, m, n );
                MPI_Allreduce( &rt, &residual, 1, MPI_FLOAT, MPI_SUM, comm );
                residual = sqrtf( residual )/r0;
                if( epsilon < residual )
                    break;
                /* update the new solution */
                for(i=1; i<=m; i++)
                    for(j=1; j<=n; j++)
                        sol[i*lds+j]+=0.25*work[i*lds+j];
                        /* send the sol 1st row to front process */
                        MPI_Sendrecv( &sol[lds+1], n, MPI_FLOAT, front, 1, &sol[(m+1)*lds+1], n, MPI_FLOAT, next, 1, comm, &st );
                        /* send the sol last row to next process */
                        MPI_Sendrecv( &sol[m*lds+1], n, MPI_FLOAT, next, 2, &sol[1], n, MPI_FLOAT, front, 2, comm, &st );
    }
    return;
}
