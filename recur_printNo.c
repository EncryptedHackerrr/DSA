#include <stdio.h>

void countPrint(int n)
{
    if(n<=0)
        return; 
    else
	countPrint(n-1);

        printf("%d\t",n);
        
    
    
        
}

int main() {
    int n;
    printf("Enter the number to count:");
    scanf("%d",&n);
    
    countPrint(n);

    return 0;
}
