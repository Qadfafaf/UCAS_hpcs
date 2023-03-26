#include"xn1.h"
#include"bitre.h"
int main()
{
#ifdef xn1
    int n = 8;
    double complex s[20];
    solvexn1(n,s);
    int i = 0;
    for(i=0;i<n;i++)
    {
        printf("%lf+%lfi\n",creal(s[i]),cimag(s[i]));
    }
#endif
#define bitre
#ifdef bitre
	int n = 16;
	int i = 0;
	int narray[60];
	int num[60];
	for(i=0;i<n;i++)
	{
		narray[i]=i;
		num[i]=i;
	}
	bitreverse(n,narray);
	for(i=0;i<n;i++)
	{
		printf("%d ",narray[i]);
	}
	printf("\n");
	reorder(n,narray,num);
	for(i=0;i<n;i++)
	{
		printf("%d ",num[i]);
	}
	printf("\n");
#endif
    return 0;
}
