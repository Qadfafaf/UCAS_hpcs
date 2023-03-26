#include"bitre.h"
void bitreverse(int n,int* narray)
{
	int n2 = 0, i = 0;
	if(n<2)
		{narray[0] = 0; return;}
	n2 = 2;
	narray[0] = 0; narray[1] = 1;
	while(n2 < n)
	{
		for(i=0;i<n2;i++)
		{
			narray[i] *= 2;
			narray[i+n2] = narray[i] + 1;
		}
		n2 *= 2;
	}
	return;
}
void reorder(int n,int* narray,int* number)
{
	int i = 0;
	for(i = 1;i<n/2;i++)
	{
		int tmp = number[i];
		number[i] = number[narray[i]];
		number[narray[i]] = tmp;
	}	
}
