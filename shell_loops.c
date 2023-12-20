#include "shell.h"

/**
 * shell_loop - Main shell loop.
 * @program_name: The name of the shell program.
 *
 * Return: Always EXIT_SUCCESS.
 */
int shell_loop(char *program_name)
{
	char *line;
	char **args;
	int status;

	do {
		if (isatty(STDIN_FILENO))
		{
			printf("$==> ");
		}

		line = read_line();
		args = split_line(line);
		status = execute(args, program_name);

		free(line);
		free(args);
	} while (status);

	return (EXIT_SUCCESS);
}
