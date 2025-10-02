#include <stdio.h>
#include <stdlib.h>

#define MIN_ARGUMENTS 3
#define MAX_COORDS 5
#define COORD_2D 2

// Absolutely no array notation anywhere

void drawLine(
    int x1,
    int y1,
    int x2,
    int y2,
    char **matrix,
    int h
)
{
    int x, y;

    x = x1;
    y = y1;

    while (x != x2 || y != y2)
    {
        if (x2 > x) {
            x++;
        } else if (x2 < x) {
            x--;
        }

        if (y2 > y) {
            y++;
        } else if (y2 < y) {
            y--;
        }

        *(*(matrix + x) + (h - 1 - y)) = '*';
    }
}

void drawShape(
    char *outputPath,
    int **coords,
    int numCoords,
    int width,
    int height
)
{
    char **matrix;
    FILE *writeFile;

    writeFile = fopen(outputPath, "w");

    if (writeFile == NULL)
    {
        perror("Failed to open output file\n");
        return;
    }

    // malloc matrix rows (width)
    matrix = (char**) malloc(width * sizeof(char*));

    if (matrix == NULL)
    {
        perror("Failed to malloc matrix width");
        return;
    }

    // malloc matrix columns (height);
    for (int x = 0; x < width; x++)
    {
        *(matrix + x) = (char*) malloc(height * sizeof(char));

        // Free any allocated memory if failure
        if (*(matrix + x) == NULL)
        {
            perror("Failed to mallox matrix height\n");
            for (int i = 0; i < x; i++)
            {
                free(*(matrix + i));
            }
            free(matrix);
            return;
        }
    }

    // set matrix to all spaces
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            *(*(matrix + x) + y) = ' ';
        }
    }

    // Insert coords into matrix
    for (int i = 0; i < numCoords; i++)
    {
        int x = *(*(coords + i));
        int y = *(*(coords + i) + 1);
        *(*(matrix + x) + (height - 1 - y)) = '*';

        // draw line between coordinates
        if (i < numCoords - 1)
        {
            int nextX = *(*(coords + i + 1));
            int nextY = *(*(coords + i + 1) + 1);

            drawLine(x, y, nextX, nextY, matrix, height);
        }
    }

    // Check for spaces in matrix surrounded by coords
    for (int y = 0; y < height; y++)
    {
        int endX;
        for (int x = 0; x < width; x++)
        {
            if (*(*(matrix + x) + y) == '*')
            {
                for (int i = x; i < width; i++)
                {
                    if (*(*(matrix + i) + y) == '*') {
                        endX = i;
                    }
                }

                drawLine(x, y, endX, y, matrix, y * 2 + 1);
            }
            break;
        }
    }

    // matrix to output file
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            fputc(*(*(matrix + x) + y), writeFile);
        }
        fputc('\n', writeFile);
    }

    fclose(writeFile);

    for (int x = 0; x < width; x++)
    {
        free(*(matrix + x));
    }

    free(matrix);
}

int main(int argc, char **argv)
{
    if (argc != MIN_ARGUMENTS)
    {
        perror("Usage: lab5.c <input_file> <output_file>\n");
        return 1;
    }

    char *inputPath;
    char *outputPath;
    FILE *inputFile;

    inputPath  = *(argv + 1);
    outputPath = *(argv + 2);
    inputFile  = fopen(inputPath, "r");

    if (inputFile == NULL)
    {
        perror("Failed to open input file");
        return 1;
    }

    int **coords;
    int numCoords;
    int width, height;

    numCoords = 0;
    coords = malloc(MAX_COORDS * sizeof(int*));

    if (coords == NULL)
    {
        perror("Failed to malloc coords\n");
        return 1;
    }

    for (int i = 0; i< MAX_COORDS; i++)
    {
        *(coords + i) = malloc(COORD_2D * sizeof(int));

        if (*(coords + i) == NULL)
        {
            perror("Failed to malloc coords entry\n");

            for (int j = 0; j < i; j++)
            {
                free(*(coords + j));
            }
            free(coords);

            return 1;
        }
    }

    while (numCoords < MAX_COORDS)
    {
        int x, y;

        if (fscanf(inputFile, "%d,%d", &x, &y) == 2)
        {
            if (x > width)  width  = x;
            if (y > height) height = y;

            *(*(coords + numCoords))     = x;
            *(*(coords + numCoords) + 1) = y;
            numCoords++;
        }
        else
        {
            char c;
            if (fscanf(inputFile, " %c", &c) == 1 && c == 'E') {
                break;
            } else {
                break;
            }
        }
    }

    fclose(inputFile);

    drawShape(
        outputPath,
        coords,
        numCoords,
        ++width,
        ++height
    );

    return 0;
}
