#include <stdio.h>

#define ARRAY_SIZE 5

void printArray(double arr[]) {
	for (int i = 0; i < 5; i++) {
		printf("%.1f, ", arr[i]);
	}
	printf("\n");
}

void copy_arr(double target[], double source[], int size) {
	for (int i = 0; i < size; i++) {
		target[i] = source[i];
	}

	printArray(target);
}

void copy_ptr(double *target, double *source, int size) {
	for (int i = 0; i < size; i++) {
		*(target + i) = *(source + i);
	}

	printArray(target);
}

void copy_ptrs(double *target, double *source, double *lastElement) {
	while (source <= lastElement) {
		target = source;
		source++;
		target++;
	}
	
	printArray(target);
}

int main(void) {

	double source[ARRAY_SIZE] = {1.1, 2.2, 3.3, 4.4, 5.5};
	double target1[ARRAY_SIZE];
	double target2[ARRAY_SIZE];
	double target3[ARRAY_SIZE];

	copy_arr(target1, source, ARRAY_SIZE);
	copy_ptr(target2, source, ARRAY_SIZE);
	copy_ptrs(target3, source, source + ARRAY_SIZE);

	return 0;
}