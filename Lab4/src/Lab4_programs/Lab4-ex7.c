#include<stdio.h>
int main()
{
	int x=1309;
	int *p = NULL;
	p = x; //point p to x
	printf("\n The value of x is = %d",x);
	printf("\n The pointer points to the value = %d",&p);//print the address
	return 1;
}

