#include <stdio.h>


/*
* Course: COMP 2510
* Assignment: Assignment 1
* Name: Braeden Sowinski
* Student ID: A01385066
* Date: 2025-09-20
* Description: Convert centimeters to feet and inches
*/


#define CENTIMETERS_PER_FOOT 30.48
#define CENTIMETERS_PER_INCH 2.54
#define INCHES_PER_FOOT 12

/**
 * main program entry
 *
 * continuously takes user input for a height
 * in centimeters and then converts that to
 * feet and inches with proper amount of decimal
 * points.
 *
 * Quits when a number less than or equal to 0
 * is inputed.
 */
int main(void)
{

	float heightCm;
	int   heightFeet;
	float heightInches;

	do
	{

		printf("Enter a height in centimeters (<=0 to quit): ");
		scanf("%f", &heightCm);

		if (heightCm <= 0)
		{
			break;
		}

		heightFeet   = (heightCm / CENTIMETERS_PER_FOOT);
		heightInches = (heightCm / CENTIMETERS_PER_INCH) -
		               (INCHES_PER_FOOT * heightFeet);

		printf(
			"%.1f cm = %d feet, %.1f inches\n",
			heightCm,
			heightFeet,
			heightInches
		);

	} while (heightCm > 0);

	printf("Bye\n");

	return 0;
}
