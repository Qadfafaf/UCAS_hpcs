#include"xn1.h"
void solvexn1(int length,double complex* solution)
{
    int i = 0;
    solution[0] = 1.0;
    double complex wn;
    double up = -2 * (PI/length);
	printf("0 = %lf\n",up);
    wn = cos(up) + I * sin(up);
    for(i=1;i<length;i++)
    {
        solution[i] = solution[i-1] * wn;
    }
}
