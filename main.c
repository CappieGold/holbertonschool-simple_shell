#include "shell.h"

/**
 * main - entry point of the shell
 * Return: 0 for success
*/

#define MAX_INPUT_SIZE 1024

int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t chars_read;

	while (1)
	{
		printf("#OnePieceShell$ ");
		chars_read = getline(&input, &input_size, stdin);
		if (chars_read == -1)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "exit") == 0)
			break;
		execute_command(input);
	}
	if (input != NULL)
		free(input);
	return (0);
}
