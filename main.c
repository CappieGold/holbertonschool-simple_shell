#include "shell.h"

/**
 * main - entry point of the shell
 * Return: 0 for success
*/

int main(void)
{
	char *cmd = NULL;
	size_t input_size = 0;
	ssize_t chars_read;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#OnePieceShell$ ");
		}
		chars_read = getline(&cmd, &input_size, stdin);
		if (chars_read == -1)
		{
			printf("\n");
			free(cmd);
			break;
		}

		execute_command(cmd);
	}

	if (cmd != NULL)
		free(cmd);
	return (0);
}
