#include <stdio.h>

/*
* Course: COMP 2510
* Assignment: Assignment 1
* Name: Braeden Sowinski
* Student ID: A01385066
* Date: 2025-09-20
* Description: Calculate sum of squares from X to Y
*/

/**
 * main program entry
 *
 * takes in user input for an upper and lower
 * limit, then calculates the sum of squares
 * from the lower to the upper limit.
 *
 * continuously takes input until upper limit
 * is less than or equal to lower limit
 */
int main(void)
{

	int max;
	int min;
	int sumOfSquares;

	do
	{

		sumOfSquares = 0;

		printf("Enter a lower and upper limit: ");
		scanf("%d %d", &min, &max);

		if (max <= min)
		{
			break;
		}

		for (int i = min; i <= max; i++)
		{
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
