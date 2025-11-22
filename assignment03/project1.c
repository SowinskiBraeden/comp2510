#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NO_LEN 0
#define MIN_SIZE 2
#define INDEX_OFFSET 1
#define INSERTION_SORT 1
#define SELECTION_SORT 2

void insertionSort(int *arr, size_t size)
{
    if (size < MIN_SIZE)
    {
        return;
    }

    int key;
    int cmp;

    for (int i = 0; i < size - INDEX_OFFSET; i++)
    {
        key  = i + INDEX_OFFSET;
        cmp = i;

        while (arr[key] < arr[cmp])
        {
            int tmp;

            tmp      = arr[key];
            arr[key] = arr[cmp];
            arr[cmp] = tmp;

            key--;
            cmp--;
        }
    }
}

void selectionSort(int *arr, size_t size)
{
    if (size < MIN_SIZE)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        int min;
        int tmp;

        min = i;

        for (int j = i + INDEX_OFFSET; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        tmp      = arr[i];
        arr[i]   = arr[min];
        arr[min] = tmp;
    }
}

void printArr(int *arr, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        char *padding;
        padding = i < size - INDEX_OFFSET ? ", " : "\n";
        printf("%d%s", arr[i], padding);
    }
}

int main(void)
{
    size_t arrSize;
    int    *arr;

    printf("Enter Number of elements: ");
    scanf("%ld", &arrSize);

    arr = (int*) malloc(sizeof(int) * arrSize);

    for (int i = 0; i < arrSize; i++)
    {
        printf("Element %d: ", i + INDEX_OFFSET);
        scanf("%d", &arr[i]);
    }

    int sortAlgorithm;
    int validAlgorithm;

    do
    {
        printf("\nChoose a sorting algorithm:\n");
        printf("Insertion Sort (1)\n");
        printf("Selection Sort (2)\n");

        scanf("%d", &sortAlgorithm);

        validAlgorithm = sortAlgorithm == INSERTION_SORT ||
                         sortAlgorithm == SELECTION_SORT;

        if (!validAlgorithm)
        {
            printf("Invalid sort algorithm\n");
        }

    } while (!validAlgorithm);

    printf("\nBefore:\n");
    printArr(arr, arrSize);

    char *algorithm;

    switch (sortAlgorithm)
    {
        case INSERTION_SORT:
            algorithm = "insertion";
            insertionSort(arr, arrSize);
            break;

        case SELECTION_SORT:
            algorithm = "selection";
            selectionSort(arr, arrSize);
            break;

        default:
            printf("Error: bad input");
            return 1;
    }

    printf("\nAfter %s sort:\n", algorithm);
    printArr(arr, arrSize);

    free(arr);
}
