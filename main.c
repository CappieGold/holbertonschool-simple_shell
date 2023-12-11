#include "shell.h"

#define MAX_INPUT_SIZE 1024

int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t chars_read;
	pid_t pid;
	char **args;

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
		{
			break;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			break;
		}
		else if (pid == 0)
		{
			args = malloc(sizeof(char *) * 2);
			args[0] = input;
			args[1] = NULL;
			execve(input, args, NULL);
			perror("execve");
			free(args);
			_exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
	if (input != NULL)
		free(input);
	return (0);
}
