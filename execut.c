#include "shell.h"

/**
 * execute - Execute a command.
 * @args: List of arguments.
 *
 * Return: Always 1 to continue the shell.
 */
int execute(char **args, char *program_name)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
	{
		int exit_status = args[1] ? atoi(args[1]) : EXIT_SUCCESS;

		exit(exit_status);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("shell");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
