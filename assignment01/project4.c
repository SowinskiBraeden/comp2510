#include <stdio.h>

/*
* Course: COMP 2510
* Assignment: Assignment 1
* Name: Braeden Sowinski
* Student ID: A01385066
* Date: 2025-09-20
* Description: Demonstrate how to copy arrays using different methods
*/

#define ARRAY_SIZE 5

/**
 * printArray to validate copy
 */
void printArray(char arrName[], double arr[]) {
    printf("\n%s\n", arrName);
    for (int i = 0; i < 5; i++) {
		printf("%.1f, ", arr[i]);
	}
	printf("\n");
}

/**
 * copy_arr using array notatoin
 */
void copy_arr(double target[], double source[], int size) {
	for (int i = 0; i < size; i++) {
		target[i] = source[i];
	}

	printArray("target 1:", target);
}

/**
 * copy_ptr copies an array using pointer arithmatic
 */
void copy_ptr(double *target, double *source, int size) {
	for (int i = 0; i < size; i++) {
		*(target + i) = *(source + i);
	}

	printArray("target 2:", target);
}

/**
 * copy_ptrs copies an array using pointers
 */
void copy_ptrs(double *target, double *source, double *lastElement) {
	while (source <= lastElement) {
		target = source;
		source++;
		target++;
	}

	printArray("target 3:", target);
}

/**
 * main program entry to test different ways
 * of copying arrays
 */
int main(void) {

	double source[ARRAY_SIZE] = {1.1, 2.2, 3.3, 4.4, 5.5};
	double target1[ARRAY_SIZE];
	double target2[ARRAY_SIZE];
	double target3[ARRAY_SIZE];

	printArray("source:", source);

	copy_arr(target1, source, ARRAY_SIZE);
	copy_ptr(target2, source, ARRAY_SIZE);
	copy_ptrs(target3, source, source + ARRAY_SIZE);

	return 0;
}
