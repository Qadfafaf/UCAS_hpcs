#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
    FILE *fp=fopen("poly_content","r");
    char buffer[200];
    int input_sign = 0;// 0 is input other information [1 is input the max order, 2 is input each number of the orders]
    int order = 0;
    int number[100] = {0};// from lowest order to highest until 0 order
    if(!fp)
    {
        printf("read file error!\n");
    }
    while (fgets(buffer, 200, fp) != NULL)
	{
        printf("%s",buffer);
        if(input_sign == 1)
        {
            //input only one int number as the order
            int index=0,i=0;
            for(i=index;i<200;i++)
            {
                if(buffer[i]==' '||buffer[i]=='\n')
                {
                    break;
                }
            }
            int j=0;
            for(j=index;j<i;j++)
            {
                order = order * 10 + buffer[j] - '0';
            }
            //printf("order is %d \n",order);
            input_sign = 0;
        }
        else if(input_sign == 2)
        {
            int num = order + 1;
            int index = 0, i = 0, j = 0;
            for(i = 0;i < num;i++)
            {
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
                number[i] = temp;
                //printf("%d\n",number[i]);
            }
        }
        //set input signal
        if(!strcmp(buffer,"order\n"))
        {
            input_sign = 1;
        }
        else if(!strcmp(buffer,"number\n"))
        {
            input_sign = 2;
        }
    }
    fclose(fp);

    printf("the polynomial is P = ");
    int i = 0;
    for(i = 0;i <= order;i++)
    {
        if(i!=0)
        {
            printf("+");
        }
        printf("%dx^%d",number[i],i);
    }
    printf("\n");

    printf("x:");
    int x;
    scanf("%d",&x);
    int poly = 0;
    int temp = 1;
    for(i=0;i<=order;i++)
    {
        poly += temp * number[i];
        temp *= x;
    }
    printf("P(%d)=%d\n",x,poly);
    int poly_test = 0;
    for(i=0;i<=order;i++)
    {
        poly_test += number[i] * (int)pow(x,i);
    }
    printf("True answer: P(%d)=%d\n",x,poly_test);
    if(poly==poly_test)
    {
        printf("Result True\n");
    }
    else
    {
        printf("Result False\n");
    }
    return 0;
}