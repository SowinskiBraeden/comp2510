#include <stdio.h>

/**
 * Course: COMP 2510
 * Assignment: Assignment 2
 * Name: Braeden Sowinski
 * Student ID: A01385066
 * Date: 2025-10-29
 * Description: Sum of digits uses recursion to
 * calculate the sum of digits of a number.
 * e.g. 12345 -> 1 + 2 + 3 + 4 + 5 = 15
 */
int sumOfDigits(int n)
{
    if (n == 0)
    {
        return 0;
    }

    return (n % 10) + sumOfDigits(n / 10);
}

int main(void)
{
    int n;
    int sum;

    printf("Enter a number: ");
    scanf("%d", &n);

    sum = sumOfDigits(n);

    printf("Sum of digits = %d\n", sum);

    return 0;
}
