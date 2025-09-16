#include <stdio.h>

void multiplicationTable(int n) {
  printf("Multiplication table of %d\n", n);

  for (int i = 1; i <= 10; i++) {
    printf("%d x %d = %d\n", n, i, n * i);
  }

  printf("\n");
}

void numberAnalysis(int n) {
  int c = (n > 0) - (n < 0);

  switch (c) {
    case -1: // n is negative
      multiplicationTable(n);

      printf("Sum not applicable for negative numbers\n");
      printf("The number is Negative.\n");

      break;
    case 0: // n is zero
      multiplicationTable(n);

      printf("Sum not applicable for zero\n");
      printf("The number is Zero.\n");

      break;
    default: // n is positive
      multiplicationTable(n);

      int sum = 0;
      int current = 0;
      while (current <= n) {
        sum += current;
        current++;
      }

      printf("Sum of 1 to %d = %d\n", n, sum);
      printf("The number is Positive.\n");

      break;
  }
}

int main(void) {
  int number;

  printf("Enter a number: ");
  scanf("%d", &number);

  numberAnalysis(number);

  return 0;
}
