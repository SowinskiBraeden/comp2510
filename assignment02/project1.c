#include <stdio.h>

/**
 * Course: COMP 2510
 * Assignment: Assignment 2
 * Name: Braeden Sowinski
 * Student ID: A01385066
 * Date: 2025-10-29
 * Description: Checks if both the second
 * and fourth bit of a given number are
 * on or not.
 */
void printBinary(int n)
{
    printf("Binary: ");

    // sizeof(int) * 2 - 1 = number of bits. i.e. 7 bits, range 7 to 0 inclusive
    for (int i = sizeof(int) * 2 - 1; i >= 0; i--)
    {
        // shift bit 'i' to bit index 0, use '&' to check if bit is 1 or 0
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
}

int areSecondAndFourthBitsOn(int n)
{
    int mask = 0b00010100;

    return (n & mask) == mask;
}

int main(void)
{
    int n;

    printf("Enter an integer: ");
    scanf("%d", &n);

    printBinary(n);
    areSecondAndFourthBitsOn(n) == 1 ? printf("Second and fourth bits are ON.\n") :
                                       printf("Second and fourth bits are NOT both ON.\n");

    return 0;
}
