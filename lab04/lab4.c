#include <stdio.h>
#include <stdlib.h>

// A01385066

/**
 * encrypt_text takes in an input path, encrypts the contents of
 * the file from input path by a given shift amount. Then writes 
 * the encrypted content to the specified output path.
 * 
 * @param inputPath  char[] - input path of file to encrypt
 * @param outputPath char[] - output path of encrypted file
 * @param shift      int    - number to shift characters by
 * @author Braeden Sowinski
 */
void encrypt_text(char inputPath[], char outputPath[], int shift) 
{

	FILE *readFile;
	FILE *writeFile;
	char character;

	readFile  = fopen(inputPath, "r");
	writeFile = fopen(outputPath, "w");

	if (readFile == NULL)
	{
		printf("Error opening file: \"%s\"\n", inputPath);
		return;
	}

	if (writeFile == NULL)
	{
		printf("Error opening file: \"%s\"\n", outputPath);
		return;
	}

	// Iterate over characters till end of file
	while((character = fgetc(readFile)) != EOF)
	{

		if ((character >= 'A' && character <= 'Z') || 
			(character >= 'a' && character <= 'z')) 
		{

			/*
			* if capital letter and adding shift to character goes beyond 'Z'
			* then shift character to 'A' - 1 before adding shift.
			*/
			if (character <= 'Z' && character >= 'A' && (character + shift) > 'Z')
			{
				character -= ('Z' + 1) - 'A';
			}

			character += shift;

			/*
			* if character goes beyond alphabet (> 'z') then
			* shift character back by the number of lower case
			* letters.
		 	*/
			if (character > 'z')
			{
				character -= ('z' + 1) - 'a';
			}
		}

		fputc(character, writeFile);
	}

	fclose(readFile);
	fclose(writeFile);

	return;
}

int main(int argc, char *argv[])
{

	if (argc != 4)
	{
		printf("Usage: %s <input_file> <output_file> <shift>\n", argv[0]);
		return 1;
	}

	char *inputPath;
	char *outputPath;
	int  shift;

	inputPath  = argv[1];
	outputPath = argv[2];
	shift      = atoi(argv[3]);

	encrypt_text(inputPath, outputPath, shift);

	return 0;
}
