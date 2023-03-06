#include<stdio.h>
#include<string.h>
#include"matadd.c"
int main()
{
	FILE *fp=fopen("mat_content","r");
    char buffer[200];
    char c;
    int A[N][N] = {0};
    int a_row = 0, a_col = 0;
    int B[N][N] = {0};
    int b_row = 0, b_col = 0;
    int inrow=0;
    int mat_sign = 0;//0 = no mat input [1 = A input,2 = B input]
    if(!fp)
    {
        printf("read file error!\n");
    }
    while (fgets(buffer, 200, fp) != NULL)//read only one row per cycle
	{
        printf("%s",buffer);
        if(buffer[0]=='A')
        {
            mat_sign = 1;//input A content
            inrow = 0;
            continue;
        }
        else if(buffer[0]=='B')
        {
            mat_sign = 2;//input B content
            inrow = 0;
            continue;
        }
        if(mat_sign==1)//input A rownum & colnum
        {
            char buf[100];
            int i=0;
            strcpy(buf,"");
            for(i=0;i<200;i++)
            {
                if(buffer[i]==' ')
                {
                    break;
                }
                else
                {
                    buf[i]=buffer[i];
                }
            }
            //extract A's rownum
            if(!strcmp(buf,"row"))
            {
                int j=0;
                for(j=i+1;j<200;j++)
                {
                    if(buffer[j]==' '||buffer[j]=='\0'||buffer[j]=='\n')
                    {
                        break;
                    }
                    else
                    {
                        buf[j]=buffer[j];
                    }
                }
                //now A's rownum is store in buf[i+1,j-1]
                int k=0;
                a_row = 0;
                for(k=i+1;k<j;k++)
                {
                    a_row = a_row * 10 + buf[k] - '0';
                }
            }
            else if(!strcmp(buf,"col"))//extract A's colnum
            {
                int j=0;
                for(j=i+1;j<200;j++)
                {
                    if(buffer[j]==' '||buffer[j]=='\0'||buffer[j]=='\n')
                    {
                        break;
                    }
                    else
                    {
                        buf[j]=buffer[j];
                    }
                }
                //now A's colnum is store in buf[i+1,j-1]
                int k=0;
                a_col = 0;
                for(k=i+1;k<j;k++)
                {
                    a_col = a_col * 10 + buf[k] - '0';
                }
            }
            else
            {
                //extract a's content
                int index = 0;
                for(i=0;i<a_col;i++)
                {
                    //input a integer to matrix
                    int j=index,k=0;
                    while(!(buffer[j]==' '||buffer[j]=='\0'||buffer[j]=='\n'))
                    {
                        j++;
                    }
                    int temp = 0;
                    for(k=index;k<j;k++)
                    {
                        temp = temp * 10 + buffer[k] - '0';
                    }
                    index=j+1;
                    A[inrow][i] = temp;
                }
                inrow++;
            }
        }
        else if(mat_sign==2)//input b rownum & colnum
        {
            char buf[100];
            int i=0;
            strcpy(buf,"");
            for(i=0;i<200;i++)
            {
                if(buffer[i]==' ')
                {
                    break;
                }
                else
                {
                    buf[i]=buffer[i];
                }
            }
            //extract b's rownum
            if(!strcmp(buf,"row"))
            {
                int j=0;
                for(j=i+1;j<200;j++)
                {
                    if(buffer[j]==' '||buffer[j]=='\0'||buffer[j]=='\n')
                    {
                        break;
                    }
                    else
                    {
                        buf[j]=buffer[j];
                    }
                }
                //now b's rownum is store in buf[i+1,j-1]
                int k=0;
                b_row = 0;
                for(k=i+1;k<j;k++)
                {
                    b_row = b_row * 10 + buf[k] - '0';
                }
            }
            else if(!strcmp(buf,"col"))//extract b's colnum
            {
                int j=0;
                for(j=i+1;j<200;j++)
                {
                    if(buffer[j]==' '||buffer[j]=='\0'||buffer[j]=='\n')
                    {
                        break;
                    }
                    else
                    {
                        buf[j]=buffer[j];
                    }
                }
                //now b's colnum is store in buf[i+1,j-1]
                int k=0;
                b_col = 0;
                for(k=i+1;k<j;k++)
                {
                    b_col = b_col * 10 + buf[k] - '0';
                }
            }
            else
            {
                //extract b's content
                int index = 0;
                for(i=0;i<b_col;i++)
                {
                    //input b integer to matrix
                    int j=index,k=0;
                    while(!(buffer[j]==' '||buffer[j]=='\0'||buffer[j]=='\n'))
                    {
                        j++;
                    }
                    int temp = 0;
                    for(k=index;k<j;k++)
                    {
                        temp = temp * 10 + buffer[k] - '0';
                    }
                    index=j+1;
                    B[inrow][i] = temp;
                }
                inrow++;
            }
        }
	}
	fclose(fp);
    int c_row = a_row > b_row ? a_row : b_row;
    int c_col = a_col > b_col ? a_col : b_col;
    int C[N][N] = {0};
    matadd((int**)A,a_row,a_col,(int**)B,b_row,b_col,(int**)C,c_row,c_col);
    int a=0,b=0;
    for(a=0;a<c_row;a++)
    {
        for(b=0;b<c_col;b++)
        {
            printf("%d ",C[a][b]);
        }
        printf("\n");
    }
    return 0;
}