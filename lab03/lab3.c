#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// update this with your A number
char a_num[] = "01385066";

void rotateArray(int arr[10][10], int n, int rows, int cols) {

    // Invalid rotation angle
    if (n % 90 != 0) {
      return;
    }

    int numRotations = n / 90;
    int tmp[rows][cols];

    // rotate by 90 or -90 for numRotations
    for (int t = 0; t < abs(numRotations); t++) {
      
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

          if (numRotations > 0) {
            // rotate by 90
            tmp[i][cols - 1 - j] = arr[j][i];
          } else {
            // rotate by -90
            tmp[rows - 1 - i][j] = arr[j][i];
          }

        }
      }

      // update arr and rotate again if needed
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          arr[i][j] = tmp[i][j];
        }
      }

    }

    // Do NOT write any code below
    // Output the rotated array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
	    if(arr[i][j] == 0)
	      printf(" ");
	    else
	      printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file> <input_angle_degrees>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    int rotationAngle = 0;
    int dimensions = 0;
    int arr[10][10] = {0};  // Initialize the array with zeros
    int rows = 0, cols = 0;
    char inputChar;

    // Read the input array from the specified file
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Read the first line for angle of rotation and second line for array dimensions
    fscanf(file, "%d", &rotationAngle);
    fscanf(file, "%d", &dimensions);
    // Read the input array character by character
    int counter = 0; //To skip first two lines in the file
    while (rows < 10 && (inputChar = fgetc(file)) != 'E') {
        if (inputChar == '\n'){counter++;}
        if (inputChar == '\n' && counter>=2) {
            rows++;
            cols = 0;
        } else if (cols < 10 && inputChar >= '0' && inputChar <= '9') {
            arr[rows][cols++] = inputChar - '0';
        }
    }

    fclose(file);
    printf("A%s\n", a_num);
    // Actual dimensions of the input array
    rows = cols = dimensions;

    printf("Input array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
	    if(arr[i][j] == 0)
	      printf(" ");
	    else
	      printf("%d", arr[i][j]);
        }
        printf("\n");
    }

    printf("\nRotated array (%d degrees):\n", rotationAngle);
    rotateArray(arr, rotationAngle, rows, cols);

    return 0;
}
