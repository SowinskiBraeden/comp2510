#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Update this with your A number
char a_num[] = "01385066";

void writeOutput(char outputPath[], char **arr, int *rows, int *cols)
{
    FILE *writeFile;

    writeFile = fopen(outputPath, "w");

    if (writeFile == NULL)
    {
        perror("Failed to open output file\n");
        return;
    }

    // matrix to output file
    for (int x = 0; x < *rows; x++)
    {
        for (int y = 0; y < *cols; y++)
        {
            fputc(arr[x][y], writeFile);
        }

        if (x < *rows - 1) fputc('\n', writeFile);
    }

    fclose(writeFile);
}

void zoomArray(char **arr, float n, int *rows, int *cols, char outputFileName[])
{

    int newRows = (int)(*rows * n);
    int newCols = (int)(*cols * n);

    char **scaled = malloc(sizeof(char*) * newRows);

    if (scaled == NULL)
    {
        printf("Failed to malloc scaled");
        return;
    }

    for (int i = 0; i < newRows; i++)
    {
        scaled[i] = malloc(sizeof(char) * newCols);
        if (scaled[i] == NULL)
        {
            printf("Failed to malloc scaled[i]");
            for (int j = 0; j < i; j++)
                free(scaled[i]);

            free(scaled);
            return;
        }
    }

    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            int srcRow = (int)(i / n);
            int srcCol = (int)(j / n);

            if (srcRow >= *rows) srcRow = *rows - 1;
            if (srcCol >= *cols) srcCol = *cols - 1;

            scaled[i][j] = arr[srcRow][srcCol];
        }
    }

    writeOutput(outputFileName, scaled, &newRows, &newCols);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    char **arr = NULL;
    int rows = 0, cols = 0;
    float zoomFactor = 0;

    // Read the input array from the specified file
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    // Read the row value
    fscanf(file, "%d", &rows);
    // Read the column value
    fscanf(file, "%d", &cols);
    // Read the zoom factor
    fscanf(file, "%f", &zoomFactor);

    // Allocate memory for the 2D array
    arr = (char **)malloc(rows * sizeof(char *));
    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < rows; i++)
    {
        arr[i] = (char *)malloc(cols * sizeof(char));
        if (arr[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    // Read the elements of the array until 'E' is encountered
    char inputChar;
    int i = 0, j = 0;
    while ((inputChar = fgetc(file)) != 'E')
    {
        if (inputChar >= '0' && inputChar <= '9' && i < rows && j < cols)
        {
            arr[i][j++] = inputChar;
            if (j == cols)
            {
                j = 0;
                i++;
            }
        }
    }

    fclose(file);
    printf("A%s\n", a_num);

    // Output the input array
    printf("Input Array:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Call the zoomArray function
    zoomArray(arr, zoomFactor, &rows, &cols, outputFileName);

    // Free the memory allocated for the 2D array
    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
