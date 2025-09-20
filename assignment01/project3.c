#include <stdio.h>

int main(void) {

	int max;
	int min;
	int sumOfSquares;

	do {

		sumOfSquares = 0;

		printf("Enter a lower and upper limit: ");
		scanf("%d %d", &min, &max);

		if (max <= min) {
			break;
		}

		for (int i = min; i <= max; i++) {
			sumOfSquares += i * i;
		}

		printf(
			"The sums of the squares from %d to %d is %d\n",
			min * min,
			max * max,
			sumOfSquares
		);

	} while (max >= min);

	printf("Done\n");

	return 0;
}