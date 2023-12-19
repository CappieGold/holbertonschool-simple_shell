#include "shell.h"
/**
 * main - Main entry point for the custom shell.
 *
 * Description: This function implements a simple shell. It enters an infinite loop 
 * where it prompts the user to enter commands, interprets these commands,
 * and executes them. It also handles special cases like the 'exit' command 
 * to quit the shell and 'fork' to create child processes.
 * 
 * Return: Returns 0 on successful exit, or a different
 * value if an error occurs.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *prompt = "#J.C&J.HShell$ ";
	char *argv[MAX_ARGS];
	int argc;
	char *token;

	while (1)
	{
		printf("%s", prompt);
		if ((read = getline(&line, &len, stdin)) == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("getline");
				continue;
			}
		}

		if (line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}

		argc = 0;
		token = strtok(line, " ");
		while (token != NULL && argc < MAX_ARGS - 1)
		{
			argv[argc++] = token;
			token = strtok(NULL, " ");
		}
		argv[argc] = NULL;

		if (argc > 0)
		{
			if (strcmp(argv[0], "exit") == 0)
			{
				break;
			}

			if (check_command_exists(argv[0]))
			{
				pid_t pid = fork();
				if (pid == -1)
				{
					perror("fork");
				} 
				else if (pid == 0)
				{
					if (execvp(argv[0], argv) == -1)
					{
						perror(argv[0]);
						exit(EXIT_FAILURE);
					}
				} else
				{
					wait(NULL);
				}
			}
			else
			{
				fprintf(stderr, "%s: Command not found\n", argv[0]);
			}
		}
	}

	free(line);
	return 0;
}
