#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MIN_OPTION 1
#define MAX_OPTION 5

#define BUFFER_SIZE 50

#define MAX_STUDENTS 111

#define AVERAGE_NINETY_PLUS 1
#define AVERAGE_EIGHTY_TO_NINETY 2
#define AVERAGE_SEVENTY_TO_EIGHTY 3
#define AVERAGE_SIXTY_TO_SEVENTY 4
#define AVERAGE_SIXTY_BELOW 5

#define MIN_THRESHOLD 0
#define MAX_THRESHOLD 101
#define NINETY_PLUS_THRESHOLD 90
#define EIGHTY_PLUS_THRESHOLD 80
#define SEVENTY_PLUS_THRESHOLD 70
#define SIXTY_PLUS_THRESHOLD 60

#define MIN_GRADE 0
#define MAX_GRADE 100
#define EMPTY_STRING ""

char A_NUMBER[] = "A01385066";

typedef struct
{
    char lastName[BUFFER_SIZE];
    char firstName[BUFFER_SIZE];
    char studentNum[BUFFER_SIZE];
    int  midtermGrade;
    int  finalGrade;
} STUDENT;

void writeStudents(
    char    *outputPath,
    STUDENT students[MAX_STUDENTS],
    size_t  numStudents,
    size_t  minThresholdIncusive,
    size_t  maxThresholdExclusive
)
{
    FILE *outputFile;

    outputFile  = fopen(outputPath, "w");

    if (outputFile == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    for (int i = 0; i < numStudents; i++)
    {
        float average = ((float)students[i].midtermGrade + (float)students[i].finalGrade) / 2;

        if (average >= minThresholdIncusive &&
            average < maxThresholdExclusive)
        {
            fprintf(outputFile, "%s %s %s %d %d\n",
                students[i].lastName,
                students[i].firstName,
                students[i].studentNum,
                students[i].midtermGrade,
                students[i].finalGrade
            );
        }
    }

    fclose(outputFile);
}

int compareStudent(const void *a, const void *b)
{
    const STUDENT *studentA = (const STUDENT *)a;
    const STUDENT *studentB = (const STUDENT *)b;

    int cmp = strcmp(studentA->lastName, studentB->lastName);
    if (cmp != 0)
    {
        return cmp;
    }

    cmp = strcmp(studentA->firstName, studentB->firstName);
    if (cmp != 0)
    {
        return cmp;
    }

    cmp = strcmp(studentA->studentNum, studentB->studentNum);
    if (cmp != 0)
    {
        return cmp;
    }

    float diff = studentA->midtermGrade - studentB->midtermGrade;
    if (diff != 0)
    {
        return (diff > 0) - (diff < 0);
    }

    diff = studentA->finalGrade - studentB->finalGrade;
    return (diff > 0) - (diff < 0);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: lab7.c <input_file> <output_file>\n");
        return 1;
    }

    char *inputPath;
    char *outputPath;
    FILE *inputFile;

    inputPath  = argv[1];
    outputPath = argv[2];
    inputFile  = fopen(inputPath, "r");

    if (inputFile == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    int option;
    STUDENT students[MAX_STUDENTS];
    size_t  numStudents;

    numStudents = 0;

    fscanf(inputFile, "%d", &option);
    if (option < MIN_OPTION || option > MAX_OPTION)
    {
        printf("Error: Invalid option\n");
        return -1;
    }

    char lastName[BUFFER_SIZE];
    char firstName[BUFFER_SIZE];
    char studentNum[BUFFER_SIZE];
    int  midtermGrade;
    int  finalGrade;

    while (fscanf(inputFile, "%s %s %s %d %d",
        firstName,
        lastName,
        studentNum,
        &midtermGrade,
        &finalGrade
    ) == 5)
    {
        if (midtermGrade < MIN_GRADE ||
            midtermGrade > MAX_GRADE ||
            finalGrade   < MIN_GRADE ||
            finalGrade   > MAX_GRADE)
        {
            printf("Error: Invalid student grade found\n");
            return -1;
        }

        if (strcmp(firstName,  "") == 0 ||
            strcmp(lastName,   "") == 0 ||
            strcmp(studentNum, "") == 0)
        {
            printf("Error: Missing first name, last name, or student number\n");
            return -1;
        }

        STUDENT newStudent;
        strcpy(newStudent.firstName, lastName);
        strcpy(newStudent.lastName, firstName);
        strcpy(newStudent.studentNum, studentNum);
        newStudent.midtermGrade = midtermGrade;
        newStudent.finalGrade   = finalGrade;

        students[numStudents] = newStudent;
        numStudents++;
    }

    fclose(inputFile);

    qsort(students, numStudents, sizeof(STUDENT), compareStudent);

    size_t minThresholdInclusive;
    size_t maxThresholdExclusive;

    switch (option)
    {
        case AVERAGE_NINETY_PLUS:
            minThresholdInclusive = NINETY_PLUS_THRESHOLD;
            maxThresholdExclusive = MAX_THRESHOLD;
            break;
        case AVERAGE_EIGHTY_TO_NINETY:
            minThresholdInclusive = EIGHTY_PLUS_THRESHOLD;
            maxThresholdExclusive = NINETY_PLUS_THRESHOLD;
            break;
        case AVERAGE_SEVENTY_TO_EIGHTY:
            minThresholdInclusive = SEVENTY_PLUS_THRESHOLD;
            maxThresholdExclusive = EIGHTY_PLUS_THRESHOLD;
            break;
        case AVERAGE_SIXTY_TO_SEVENTY:
            minThresholdInclusive = SIXTY_PLUS_THRESHOLD;
            maxThresholdExclusive = SEVENTY_PLUS_THRESHOLD;
            break;
        case AVERAGE_SIXTY_BELOW:
            minThresholdInclusive = MIN_THRESHOLD;
            maxThresholdExclusive = SIXTY_PLUS_THRESHOLD;
            break;
        default:
            printf("Error: Invalid option\n");
            return -1;
    }

    writeStudents(
        outputPath,
        students,
        numStudents,
        minThresholdInclusive,
        maxThresholdExclusive
    );

    return 0;
}
