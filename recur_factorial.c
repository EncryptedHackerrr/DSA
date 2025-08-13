#include <stdio.h>

// Function to calculate factorial using recursion
long long factorial(int n) {
    // Base case: factorial of 0 or 1 is 1
    if (n == 0 || n == 1) {
        return 1;
    } 
    // Recursive step: n! = n * (n-1)!
    else {
        return n * factorial(n - 1);
    }
}

int main() {
    int number;
    printf("Enter a non-negative integer: ");
    scanf("%d", &number);

    // Check for negative input
    if (number < 0) {
        printf("Error: Factorial is not defined for negative numbers.\n");
    } else {
        long long result = factorial(number);
        printf("Factorial of %d is %lld.\n", number, result);
    }

    return 0;
}
