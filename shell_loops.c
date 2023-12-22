#include "shell.h"

#define COMMAND_EXIT -1

/**
 * shell_loop - The main shell loop.
 * @program_name: The name of the shell program.
 *
 * Return: Always EXIT_SUCCESS.
 */
int shell_loop(char *program_name)
{
	char *line;
	char **args;
	int result;
	int running = 1;

	while (running)
	{
		if (isatty(STDIN_FILENO))
		{
			prompt();
		}

		line = read_line();
		if (line == NULL)
		{
			printf(feof(stdin) ? "\n" : "read_line error\n");
			break;
		}

		args = split_line(line);
		if (args)
		{
			result = execute(args, program_name, line);
			if (result == COMMAND_EXIT)
			{
				running = 0;
			}
			clean_up(line, args);
		}
		else
		{
			free(line);
		}
	}
	return (EXIT_SUCCESS);
}
