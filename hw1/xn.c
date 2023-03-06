#include<stdio.h>
#include<math.h>
int main()
{
    printf("Compute x to the power of n.\n");
    printf("Input x:");
    int x;
    scanf("%d",&x);
    printf("Input n:");
    int n;
    scanf("%d",&n);
    int k=log2(n);
    //printf("k = %d\n",k);
    int number[k+1];
    int i;
    int now = n;
    for(i=k;i>=0;i--)
    {
        if(now>=pow(2,i))
        {
            number[i] = 1;
            now -= pow(2,i);
        }
        else
        {
            number[i] = 0;
        }
    }
    int y = 1;
    int t = x;
    for(i=0;i<=k;i++)
    {
        if(number[i]==1)
        {
            y*=t;
        }
        t*=t;
    }
    printf("My answer: %d\n",y);
    int r=(int)pow(x,n);
    printf("True answer: %d\n",r);
    if(y==pow(x,n))
    {
        printf("Result True\n");
    }
    else
    {
        printf("Result False\n");
    }
    /*
    for(i=0;i<=k;i++)
    {
        printf("%d ",number[i]);
    }
    printf("\n");
    */
    return 0;
}