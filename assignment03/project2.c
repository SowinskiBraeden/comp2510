#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_SIZE 0
#define INTEGER 1
#define FLOAT   2
#define STRING  3
#define BUFFER_SIZE 256

/*
* Course: COMP 2510
* Assignment: Assignment 3
* Name: Braeden Sowinski
* Student ID: A01385066
* Date: 2025-11-22
* Description: Demo a generic swap function to swap
*              void pointers based on a user input.
*/

void swap(void *a, void *b, size_t size)
{
    void *tmp;

    tmp = malloc(size);

    memcpy(tmp, a,   size);
    memcpy(a,   b,   size);
    memcpy(b,   tmp, size);

    free(tmp);
}

void printValue(char *message, void *data, int type)
{
    printf("%s ", message);

    switch (type)
    {
        case INTEGER:
            printf("%d\n", *((int*) data));
            break;

        case FLOAT:
            printf("%.1f\n", *((float *) data));
            break;

        case STRING:
            printf("%s\n", (char *) data);
            break;
    }
}

int main(void)
{
    int type;
    int validType;

    do
    {
        printf("Choose a data type:\n");
        printf("Integer (1)\n");
        printf("Float   (2)\n");
        printf("String  (3)\n");

        scanf("%d", &type);

        validType = type >= INTEGER && type <= STRING;

        if (!validType)
        {
            printf("Invalid Data Type\n\n");
        }

    } while (!validType);

    char   *format;
    size_t size;

    format = type == INTEGER ? "%d" :
             type == FLOAT   ? "%f" :
             type == STRING  ? "%255s" :
             NULL;

    size = type == INTEGER ? sizeof(int)   :
           type == FLOAT   ? sizeof(float) :
           type == STRING  ? sizeof(char) * BUFFER_SIZE  :
           0;

    if (format == NULL || size == NO_SIZE)
    {
        printf("Invalid Data Type");
        return 1;
    }

    void *a;
    void *b;

    a = malloc(size);
    b = malloc(size);

    printf("\nEnter value A: ");
    scanf(format, a);

    printf("Enter value B: ");
    scanf(format, b);

    printValue("\nA value before: ", a, type);
    printValue("B value before: ", b, type);

    printf("\nSwapping...\n\n");
    swap(a, b, size);

    printValue("A value after:  ", a, type);
    printValue("B value after:  ", b, type);

    free(a);
    free(b);

    return 0;
}
