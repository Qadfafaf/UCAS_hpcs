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
    int ar,ac;
    int i,j;
    if(iam == 0)
    {
        FILE *fp=fopen("input","r");
        if(!fp)
        {
            printf("read file error!\n");
        }
        fscanf(fp,"%d",&ar);
        fscanf(fp,"%d",&ac);
        for(i=0;i<ar;i++)
        for(j=0;j<ac;j++)
        {
            fscanf(fp,"%f",&a[i*ac+j]);
        }
    }
    int tag,front,next;
    MPI_Status st;
    front = (iam-1+np)%np;
    next = (iam+1)%np;
    tag = 1;
    MPI_Bcast(&ac, 1, MPI_INT, 0, comm);
    MPI_Bcast(&ar, 1, MPI_INT, 0, comm);
#define a2a
#ifdef a2a
    int len = 9;
    memset(a,0,1000);
    memset(b,0,1000);
    for(i=0;i<len;i++)
    {
        a[i] = iam*10 + i;
    }
    if(iam==1)
    {
        for(i=0;i<len;i++)
        {
            printf("%f ",a[i]);
        }
        printf("\n");
    }
    MPI_Alltoall(a, len/np, MPI_FLOAT, b, len/np, MPI_FLOAT, comm);
    if(iam==1)
    {
        for(i=0;i<len;i++)
        {
            printf("%f ",b[i]);
        }
        printf("\n");
    }
    memset(b,0,1000);
    mpi_all2all(a,b,len,iam,np,comm);
    if(iam==1)
    {
        for(i=0;i<len;i++)
        {
            printf("%f ",b[i]);
        }
        printf("\n");
    }
#endif
#ifdef p3
    MPI_Datatype lower_mat;
    MPI_Datatype ex_lower_mat;
    int blocklens_array[2];
    int displs_array[2];
    blocklens_array[0]=1;
    blocklens_array[1]=2;
    displs_array[0]=0;
    displs_array[1]=ac;
    MPI_Type_indexed(2,blocklens_array,displs_array,MPI_FLOAT,&lower_mat);
    MPI_Type_commit(&lower_mat);
    int blocklens[2];
    MPI_Aint displs[2];
    MPI_Datatype type_array[2];
    blocklens[0]=1;
    blocklens[1]=1;
    displs[0]=0;
    displs[1]=14*sizeof(float);
    type_array[0]=lower_mat;
    type_array[1]=MPI_UB;
    MPI_Type_struct(2,blocklens,displs,type_array,&ex_lower_mat);
    MPI_Type_commit(&ex_lower_mat);
    if(iam==0)
    {
        MPI_Send(a, 3, ex_lower_mat, next, tag, comm);
    }
    else
    {
        MPI_Recv(b, 3, ex_lower_mat, front, tag, comm, &st);
        for(i=0;i<ar;i++)
        {
            for(j=0;j<ac;j++)
            {
                printf("%f ",b[i*ac+j]);
            }
            printf("\n");
        }
    }
#endif
#ifdef p2
typedef struct data
{
    int m[3];
    float a[2];
    char c[5];
}data;
    struct data x[10];
    int blocklens_array[3];
    MPI_Aint displs_array[3];
    MPI_Datatype type_array[3];
    MPI_Datatype data_type;
    type_array[0]=MPI_INT;
    type_array[1]=MPI_FLOAT;
    type_array[2]=MPI_CHAR;
    blocklens_array[0]=3;
    blocklens_array[1]=2;
    blocklens_array[2]=5;
    displs_array[0]=0;
    int last_type_byte,gap_byte;
    last_type_byte=displs_array[0]+sizeof(int)*blocklens_array[0];
    if(last_type_byte%sizeof(float))
        gap_byte=sizeof(float)-last_type_byte%sizeof(float);
    else
        gap_byte=0;
    displs_array[1]=last_type_byte+gap_byte;
    last_type_byte=displs_array[1]+sizeof(float)*blocklens_array[1];
    displs_array[2]=last_type_byte;
    // MPI_Address(&x[0].a[0],&displs_array[1]);
    // MPI_Address(&x[0].c[0],&displs_array[2]);
    // MPI_Address(&x[0].m[0],&displs_array[0]);
    // displs_array[2]=displs_array[2]-displs_array[0];
    // displs_array[1]=displs_array[1]-displs_array[0];
    // displs_array[0]=0;
    MPI_Type_struct(3,blocklens_array,displs_array,type_array,&data_type);
    MPI_Type_commit(&data_type);
    if(iam==0)
    {
        for(i=0;i<10;i++)
        {
            for(j=0;j<3;j++)
                x[i].m[j]=i;
            for(j=0;j<2;j++)
                x[i].a[j]=(float)i;
            for(j=0;j<5;j++)
                x[i].c[j]=i+'0';
        }
        for(i=0;i<10;i++)
        {
            MPI_Send(&x[i].m[0],1,data_type,next,tag,comm);
        }
        for(i=0;i<10;i++)
        {   
            for(j=0;j<3;j++)
                printf("%d ",x[i].m[j]);
                printf("\n");
            for(j=0;j<2;j++)
                printf("%f ",x[i].a[j]);
                printf("\n");
            for(j=0;j<5;j++)
                printf("%c ",x[i].c[j]);
                printf("\n");
        }
    }
    else
    {
        for(i=0;i<10;i++)
        {   
            MPI_Recv(&x[i].m[0],1,data_type,front,tag,comm,&st);
        }
        // for(i=0;i<10;i++)
        // {   
        //     for(j=0;j<3;j++)
        //         printf("%d ",x[i].m[i]);
        //         printf("\n");
        //     for(j=0;j<2;j++)
        //         printf("%f ",x[i].a[j]);
        //         printf("\n");
        //     for(j=0;j<5;j++)
        //         printf("%c ",x[i].c[j]);
        //         printf("\n");
        // }
    }
#endif
#ifdef p1
    MPI_Datatype matrix00;
    MPI_Datatype matrix00_20;
    int lda = ac;
    int m1 = 2, n1 = 2, m2 = 2, n2 = 1;
    MPI_Type_vector(m1, n1, lda, MPI_FLOAT, &matrix00);
    MPI_Type_commit(&matrix00);
    MPI_Type_hvector(m2, n2, 16*sizeof(MPI_FLOAT), matrix00, &matrix00_20);
    MPI_Type_commit(&matrix00_20);
    if(iam==0)
    {
        MPI_Send(a, 1, matrix00_20, next, tag, comm);
    }
    else
    {
        MPI_Recv(b, 1, matrix00_20, front, tag, comm, &st);
        for(i=0;i<ar;i++)
        {
            for(j=0;j<ac;j++)
            {
                printf("%f ",b[i*ac+j]);
            }
            printf("\n");
        }
        
    }
#endif

    MPI_Finalize();
}