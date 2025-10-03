#include <stdio.h>
#include <stdlib.h>

#define MIN_ARGUMENTS 3
#define MAX_COORDS 5
#define COORD_2D 2

// Absolutely no array notation anywhere

// A01385066

typedef struct {
    int x;
    int y;
} vector;

void drawLine(
    vector start,
    vector end,
    char **matrix,
    int h
)
{
    vector new;

    new.x = start.x;
    new.y = start.y;

    while (new.x != end.x || new.y != end.y)
    {
        *(*(matrix + new.x) + (h - 1 - new.y)) = '*';

        if (end.x > new.x) {
            new.x++;
        } else if (end.x < new.x) {
            new.x--;
        }

        if (end.y > new.y) {
            new.y++;
        } else if (end.y < new.y) {
            new.y--;
        }
    }
}

void drawShape(
    char *outputPath,
    vector *coords,
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

    // draw lines between each coordinate
    for (int i = 0; i < numCoords; i++)
    {
        vector start = *(coords + i);

        if (i < numCoords - 1)
        {
            vector end = *(coords + i + 1);

            drawLine(start, end, matrix, height);
        }
    }

    // Check for spaces in matrix surrounded by coords
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (*(*(matrix + x) + y) == '*')
            {
                int endX;
                for (int i = x; i < width; i++)
                {
                    if (*(*(matrix + i) + y) == '*') endX = i;
                }

                if (endX == x) continue;

                vector start = {x, y};
                vector end   = {endX, y};
                drawLine(start, end, matrix, y * 2 + 1);
                break;
            }
        }
    }

    // matrix to output file
    for (int y = 0; y < height; y++)
    {
        // only print up until last '*', dont
        // print trailing spaces
        int lastPoint;
        for (int i = width - 1; i >= 0; i--)
        {
            if (*(*(matrix + i) + y) == '*')
            {
                lastPoint = i;
                break;
            }
        }

        for (int x = 0; x <= lastPoint; x++)
        {
            fputc(*(*(matrix + x) + y), writeFile);
        }
        if (y < height - 1) fputc('\n', writeFile);
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

    vector *coords;
    int numCoords;
    int width, height;

    numCoords = 0;
    coords = malloc(MAX_COORDS * sizeof(vector));

    if (coords == NULL)
    {
        perror("Failed to malloc coords\n");
        return 1;
    }

    while (numCoords < MAX_COORDS)
    {
        vector coord;

        if (fscanf(inputFile, "%d,%d", &coord.x, &coord.y) == 2)
        {
            if (coord.x > width)  width  = coord.x;
            if (coord.y > height) height = coord.y;

            *(coords + numCoords) = coord;
            numCoords++;
        }
        else
        {
            if (fscanf(inputFile, "%d", &coord.x) == 0 ||
                fscanf(inputFile, "%d", &coord.x) == 0)
            {
                // Free and close file before exiting
                free(coords);
                fclose(inputFile);

                perror("Error: bad input file\n");
                return 1;
            }

            char c;
            if (fscanf(inputFile, "%c", &c) == 1 && c == 'E') {
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

    free(coords);

    return 0;
}
