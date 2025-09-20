#include <stdio.h>

#define CENTIMETERS_PER_FOOT 30.48
#define CENTIMETERS_PER_INCH 2.54
#define INCHES_PER_FOOT 12

int main(void) {

	float heightCm;
	int   heightFeet;
	float heightInches;

	do {
		
		printf("Enter a height in centimeters (<=0 to quit): ");
		scanf("%f", &heightCm);

		if (heightCm <= 0) {
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