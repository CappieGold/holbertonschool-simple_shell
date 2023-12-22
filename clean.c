#include "shell.h"

/**
 * clean_up - Free allocated memory for line and args.
 * @line: The line to free.
 * @args: The args to free.
 */
void clean_up(char *line, char **args)
{
	if (line)
		free(line);
	if (args)
		free(args);
}

/**
 * signal_handler - Handle signals by exiting.
 * @signum: The signal number.
 */
void signal_handler(int signum)
{
	exit(signum);
}
