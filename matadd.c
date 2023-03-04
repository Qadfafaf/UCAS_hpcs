#define N 100
int matadd(int** A,int arow,int acol,int** B,int brow,int bcol,int** C,int crow,int ccol)
{
    int i=0,j=0;
    for(i=0;i<crow;i++)
    {
        for(j=0;j<ccol;j++)
        {
            *((int*)C+i*N+j)=*((int*)B+i*N+j)+*((int*)A+i*N+j);
        }
    }
}