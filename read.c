#include "shell.h"

/**
 * read_line - Read a line from the standard input.
 *
 * Return: The line read from the standard input.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(line);
			return (NULL);
		}
		else
		{
			perror("read_line");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}
