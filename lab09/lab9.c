#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define EXPECTED_ARGUMENTS 3
#define PROGRAM_FILE 0
#define INPUT_FILE 1
#define OUTPUT_FILE 2
#define EXPECTED_INPUT 1

#define SHORT 1
#define INTEGER 2
#define FLOAT 3
#define CHAR 4
#define STRING 5

#define MAX_STRING_LEN 256
#define READING 1
#define IS_EQUAL 0
#define INDEX_OFFSET 1
#define BASE_TEN 10
#define DOUBLE 2

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
        // printf("Failed to read file %s\n", filepath);
        return NULL;
    }

    if (fscanf(file, "%d", type) != EXPECTED_INPUT)
    {
        // printf("Error: failed to read type from file\n");
        fclose(file);
        return NULL;
    }

    int ch; // skip new line characters and EOF
    while ((ch = fgetc(file)) != '\n' && ch != EOF) {}

    NODE *head;
    char token[MAX_STRING_LEN];

    head   = NULL;
    *count = 0;

    while (READING)
    {
        // read till comma or new line
        if (fscanf(file, " %255[^,\n]", token) != EXPECTED_INPUT)
        {
            break;
        }

        // end of file
        if (strcmp(token, "E") == IS_EQUAL)
        {
            break;
        }

        void *data;

        data = NULL;

        switch (*type)
        {
            case SHORT:
            {
                long value;

                value = strtol(token, NULL, BASE_TEN);

                if (value < SHRT_MIN || value > SHRT_MAX)
                {
                    // printf("Error: %ld is out of range for SHORT type (%d to %d)\n",
                    //     value, SHRT_MIN, SHRT_MAX);

                    fclose(file);
                    freeList(head);
                    return NULL;
                }

                data = malloc(sizeof(short));
                *(short *)data = (short)value;
                break;
            }


            case INTEGER:
            {
                data = malloc(sizeof(int));
                *(int *)data = atoi(token);
                break;
            }

            case FLOAT:
            {
                data = malloc(sizeof(float));
                *(float *)data = atof(token);
                break;
            }

            case CHAR:
            {
                data = malloc(sizeof(char));
                *(char *)data = token[0];
                break;
            }

            case STRING:
            {
                data = malloc(MAX_STRING_LEN);
                strncpy((char *)data, token, MAX_STRING_LEN - INDEX_OFFSET);
                ((char *)data)[MAX_STRING_LEN - INDEX_OFFSET] = '\0';
                break;
            }

            default:
                // printf("Error: Bad input type\n");
                fclose(file);
                return NULL;
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

void printList(NODE *head, int type)
{
    while (head != NULL)
    {
        switch (type)
        {
            case SHORT:   printf("%hd -> ",  *(short *)head->data); break;
            case INTEGER: printf("%d -> ",   *(int *)  head->data); break;
            case FLOAT:   printf("%.1f -> ", *(float *)head->data); break;
            case CHAR:    printf("%c -> ",   *(char *) head->data); break;
            case STRING:  printf("%s -> ",    (char *) head->data); break;
        }

        head = head->next;
    }

    printf("null\n");
}

int compare(void *a, void *b, int type)
{
    switch (type)
    {
        case SHORT:
        case INTEGER:
        {
            int va;
            int vb;

            va = *(int *)a;
            vb = *(int *)b;

            return (va > vb) - (va < vb);
        }

        case FLOAT:
        {
            int va;
            int vb;

            va = *(float *)a;
            vb = *(float *)b;

            return (va > vb) - (va < vb);
        }

        case CHAR:
        {
            char va;
            char vb;

            va = *(char *)a;
            vb = *(char *)b;

            return (va > vb) - (va < vb);
        }

        case STRING:
            return strcmp((char *)a, (char *)b);
    }

    return 0;
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

void writeOutput(char *filePath, char *data)
{
    FILE *file;

    file = fopen(filePath, "w");

    fputs(data, file);
    fputs("\n", file);

    fclose(file);
}

char* toString(NODE *head, int type)
{
    size_t capacity;
    char   *result;

    capacity  = MAX_STRING_LEN;
    result    = malloc(capacity);
    result[0] = '\0';

    char temp[MAX_STRING_LEN];

    while (head != NULL)
    {
        switch (type)
        {
            case SHORT:
                snprintf(temp, sizeof(temp), "%hd", *(short *)head->data);
                break;

            case INTEGER:
                snprintf(temp, sizeof(temp), "%d", *(int *)head->data);
                break;

            case FLOAT:
                snprintf(temp, sizeof(temp), "%.1f", *(float *)head->data);
                break;

            case CHAR:
                snprintf(temp, sizeof(temp), "%c", *(char *)head->data);
                break;

            case STRING:
                snprintf(temp, sizeof(temp), "%s", (char *)head->data);
                break;
        }

        while (strlen(result) + strlen(temp) + 2 >= capacity)
        {
            capacity *= DOUBLE;
            result = realloc(result, capacity);
        }

        strcat(result, temp);

        if (head->next != NULL)
            strcat(result, ",");

        head = head->next;
    }

    return result;
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
        writeOutput(argv[OUTPUT_FILE], "Error");
        // printf("Failed to read list.\n");
        return 1;
    }

    printf("\nOriginal:\n");
    printList(head, type);
    printf("\n");

    head = mergeSort(head, type);

    char *listString;

    listString = toString(head, type);

    writeOutput(argv[OUTPUT_FILE], listString);

    printf("Sorted:\n");
    printList(head, type);
    printf("\n");

    freeList(head);

    return 0;
}
