#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define EXPECTED_ARGUMENTS 3
#define PROGRAM_FILE 0
#define INPUT_FILE 1
#define OUTPUT_FILE 2
#define EXPECTED_INPUT 1
#define READING 1
#define ERROR_CODE 1
#define OK_CODE 0
#define MAX_STRING_LEN 256
#define IS_EQUAL 0
#define INDEX_OFFSET 1
#define BASE_TEN 10
#define DOUBLE 2

#define SHORT 1
#define INTEGER 2
#define FLOAT 3
#define CHAR 4
#define STRING 5

typedef struct NODE
{
    void        *data;
    struct NODE *next;
} NODE;

void insertNode(NODE **head, void *data)
{
    NODE *node;

    node = malloc(sizeof(NODE));

    node->data = data;
    node->next = *head;

    *head = node;
}

void freeList(NODE *head)
{
    NODE *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;

        free(temp->data);
        free(temp);
    }
}

NODE* readFile(char *filepath, int *type, int *count)
{
    FILE *file;
    file = fopen(filepath, "r");

    if (file == NULL)
    {
        return NULL;
    }

    if (fscanf(file, "%d", type) != EXPECTED_INPUT)
    {
        fclose(file);
        return NULL;
    }

    int ch; // skip newlines characters and EOF
    while ((ch = fgetc(file)) != '\n' && ch != EOF) {}

    char   *format;
    NODE   *head;
    size_t size;

    head   = NULL;
    *count = 0;

    format = *type == SHORT   ? "%hd" :
             *type == INTEGER ? "%d"  :
             *type == FLOAT   ? "%f"  :
             " %c";

    size = *type == SHORT   ? sizeof(short) :
           *type == INTEGER ? sizeof(int)   :
           *type == FLOAT   ? sizeof(float) :
           *type == CHAR    ? sizeof(char)  :
           MAX_STRING_LEN;

    while (READING)
    {
        void *data;

        data = malloc(size);

        if (*type == STRING)
        {
            if (fscanf(file, "%255[^,\n]", (char *)data) != EXPECTED_INPUT ||
                strcmp((char *)data, "E") == IS_EQUAL)
            {
                free(data);
                break;
            }
        }
        else
        {
            if (fscanf(file, format, data) != EXPECTED_INPUT ||
                *type == CHAR && *(char *)data == 'E')
            {
                free(data);
                break;
            }
        }

        insertNode(&head, data);
        (*count)++;

        ch = fgetc(file);
        if (ch == EOF)
        {
            break;
        }
        if (ch == '\n')
        {
            continue;
        }
    }

    fclose(file);
    return head;
}

int compare(void *a, void *b, int type)
{
    if (type == SHORT || type == INTEGER)
    {
        int va;
        int vb;

        va = *(int *)a;
        vb = *(int *)b;

        return (va > vb) - (va < vb);
    }

    if (type == FLOAT)
    {
        float va;
        float vb;

        va = *(float *)a;
        vb = *(float *)b;

        return (va > vb) - (va < vb);
    }

    if (type == CHAR)
    {
        char va;
        char vb;

        va = *(char *)a;
        vb = *(char *)b;

        return (va > vb) - (va < vb);
    }

    return strcmp((char *)a, (char *)b);
}

NODE* split(NODE *head)
{
    NODE *fast;
    NODE *slow;
    NODE *second;

    slow = head;
    fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        if (fast != NULL)
        {
            slow = slow->next;
        }
    }

    second = slow->next;
    slow->next = NULL;

    return second;
}

NODE* merge(NODE *first, NODE *second, int type)
{
    if (first == NULL)
    {
        return second;
    }
    if (second == NULL)
    {
        return first;
    }

    if (compare(first->data, second->data, type) <= IS_EQUAL)
    {
        first->next = merge(first->next, second, type);
        return first;
    }
    else
    {
        second->next = merge(first, second->next, type);
        return second;
    }
}

NODE* mergeSort(NODE *head, int type)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    NODE *second;

    second = split(head);
    head   = mergeSort(head, type);
    second = mergeSort(second, type);

    return merge(head, second, type);
}

void printValue(FILE *file, void *data, int type)
{
    if (type == SHORT)
    {
        short v;
        v = *(short *)data;
        fprintf(file, "%hd", v);
        return;
    }

    if (type == INTEGER)
    {
        int v;
        v = *(int *)data;
        fprintf(file, "%d", v);
        return;
    }

    if (type == FLOAT)
    {
        float v;
        v = *(float *)data;
        fprintf(file, "%.1f", v);
        return;
    }

    if (type == CHAR)
    {
        char v;
        v = *(char *)data;
        fprintf(file, "%c", v);
        return;
    }

    fprintf(file, "%s", (char *)data);
}

void writeOutput(char *filepath, NODE *head, int type, int isError)
{
    FILE *file;

    file = fopen(filepath, "w");

    if (isError == 1)
    {
        fputs("Error\n", file);
        fclose(file);
        return;
    }

    while (head != NULL)
    {
        printValue(file, head->data, type);

        if (head->next != NULL)
        {
            fputc(',', file);
        }

        head = head->next;
    }

    fputc('\n', file);
    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc < EXPECTED_ARGUMENTS)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[PROGRAM_FILE]);
        return 1;
    }

    NODE *head;
    int  type;
    int  count;

    head = readFile(argv[INPUT_FILE], &type, &count);

    if (head == NULL)
    {
        writeOutput(argv[OUTPUT_FILE], head, type, ERROR_CODE);
        return 1;
    }

    head = mergeSort(head, type);

    writeOutput(argv[OUTPUT_FILE], head, type, OK_CODE);

    freeList(head);

    return 0;
}
