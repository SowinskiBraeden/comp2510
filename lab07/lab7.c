#include <stdint.h>
#include <stdio.h>

#define SIGN_MASK 0x0000000000000001

long getClamp(long q, long min, long max)
{
    long diffToMin;
    long diffToMax;
    long diffToMinSign;
    long diffToMaxSign;

    diffToMin = q + (~min + 1);
    diffToMax = q + (~max + 1);
    diffToMinSign = (diffToMin >> 63) & SIGN_MASK;
    diffToMaxSign = (diffToMax >> 63) & SIGN_MASK;

    // If diff to min is 0, or the diff to min
    // is greater than the min (positive sign),
    // then check max
    if (diffToMin == 0 || diffToMinSign == 0)
    {
        // if the diff to min is 0, or the diff to max
        // is less than the min, (negative sign),
        // return q
        // otherwise return max
        return (diffToMax == 0 || diffToMaxSign == 1) ? q : max;
    }

    return min;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        perror("Usage: lab5.c <input_file> <output_file>\n");
        return 1;
    }

    char *inputPath;
    char *outputPath;
    FILE *inputFile;
    FILE *outputFile;

    inputPath  = argv[1];
    outputPath = argv[2];
    inputFile  = fopen(inputPath, "r");
    outputFile = fopen(outputPath, "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        perror("Failed to open file");
        return 1;
    }

    long bits;
    long min;
    long max;
    long x;
    long y;
    long q;
    long result;

    fscanf(inputFile, "%ld", &bits);
    fscanf(inputFile, "%ld", &x);
    fscanf(inputFile, "%ld", &y);

    min = (1 << (bits - 1)) * -1;
    max = (1 << (bits - 1)) - 1;

    if (x == 0 && y == 0)
    {
        fprintf(outputFile, "min: %ld\t0x%016lx\n", min, min);
        fprintf(outputFile, "max: %ld\t0x%016lx\n", max, max);
    }
    else
    {
        q = x * y;

        result = getClamp(q, min, max);

        fprintf(outputFile, "%ld\n", result);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
