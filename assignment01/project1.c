#include <stdio.h>


/*
* Course: COMP 2510
* Assignment: Assignment 1
* Name: Braeden Sowinski
* Student ID: A01385066
* Date: 2025-09-20
* Description: Calculate download speeds from
*              given file size and download speed
*/

#define MEGABYTES_TO_MEGABITS 8

/**
 * main program entry
 *
 * takes in user input for download speed
 * int Mbs and file size in MBs
 * and calculates the download speed
 */
int main(void)
{
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
