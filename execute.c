#include "shell.h"

/**
 * execute_command - Main function to execute a command entered in the shell.
 * It determines the type of command
 * and calls the appropriate function to handle it.
 *
 * @shell_name: name of my shell.
 * @cmd: The command string entered by the user.
 */

void execute_command(char *shell_name, char *cmd)
{
	char *argv[64];
	int argc = 0;

	if (cmd == NULL)
	{
		perror("execute: cmd is NULL");
		return;
	}

	tokenize_command(cmd, argv, &argc);

	if (argc == 0)
		return;

	handle_builtin_commands(argv);

	if (argv[0][0] == '/')
	{
		if (!execute_full_path_command(argv))
			printf("%s: 1: %s: not found\n", shell_name, argv[0]);
	}
	else
	{
		if (!execute_path_command(argv))
			printf("%s: 1: %s: not found\n", shell_name, argv[0]);
	}
}

/**
 * tokenize_command - Splits a command string into tokens.
 * @cmd: The command string to tokenize.
 * @argv: Array to store the tokenized command arguments.
 * @argc: Pointer to an integer to store the number of arguments.
 */

void tokenize_command(char *cmd, char *argv[], int *argc)
{
	char *token = strtok(cmd, " \n");

	while (token != NULL && *argc < 63)
	{
		argv[(*argc)++] = token;
		token = strtok(NULL, " \n");
	}
	argv[*argc] = NULL;
}

/**
 * handle_builtin_commands - Handles built-in shell commands
 * like 'exit' and 'env'.
 *
 * @argv: Array of command arguments.
 */

void handle_builtin_commands(char *argv[])
{
	int i = 0;

	if (strcmp(argv[0], "exit") == 0)
		exit(0);
	if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
	}
}

/**
 * execute_full_path_command - Executes a command given with its full path.
 * @argv: Array of command arguments.
 * Return: 1 if successful, 0 otherwise.
 */

int execute_full_path_command(char *argv[])
{
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
	return (1);
}

/**
 * execute_path_command - Executes a command by searching it
 * in the system PATH.
 *
 * @argv: Array of command arguments.
 * Return: 1 if successful, 0 otherwise.
 */

int execute_path_command(char *argv[])
{
	pid_t pid;
	char *full_path = find_command_in_path(argv[0]);

	if (full_path == NULL)
		return (0);

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		return (0);
	}
	else if (pid == 0)
	{
		argv[0] = full_path;
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("execve");
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
		free(full_path);
	}
	return (1);
}
