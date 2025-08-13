#include<stdio.h>

int Fibo(int n)
{
	if(n==0 || n==1)
	return n;
	else
	return Fibo(n-1)+Fibo(n-2);
}


int main()
{
	int n;
	printf("Enter number to find the fibonacci seriese:");
	scanf("%d",&n);
	printf("The Fibonacci seriese till %d th term is:",n);
	for(int i=0;i<=n;i++)
	{
		printf("\t %d",Fibo(i));
	}
	return 0;
}
