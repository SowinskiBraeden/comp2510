#include <stdio.h>

#define MEGABYTES_TO_MEGABITS 8

int main(void) {
	float downloadSpeedMbs;
	float fileSizeMB;
	float downloadTimeSeconds;

	printf("Enter download speed (Mbs): ");
	scanf("%f", &downloadSpeedMbs);

	printf("Enter file size (MB): ");
	scanf("%f", &fileSizeMB);

	downloadTimeSeconds = (fileSizeMB * MEGABYTES_TO_MEGABITS) / downloadSpeedMbs;

	printf(
		"At %.2f megabits per second, a file of %.2f megabytes downloads in %.2f seconds.\n",
		downloadSpeedMbs,
		fileSizeMB,
		downloadTimeSeconds
	);

	return 0;
}
