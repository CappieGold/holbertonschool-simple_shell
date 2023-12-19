#include "shell.h"

/**
 * main - Entry point of the custom shell.
 * This function initializes and runs a loop
 * that continually prompts the user for commands,
 * reads them from standard input, and executes them.
 * The shell supports executing commands
 * either by their full path or by searching in the PATH environment variable.
 * It also handles built-in commands like 'exit' and 'env'.
 * The shell displays a prompt "#OnePieceShell$ "
 * when waiting for a command in interactive mode.
 * It handles the 'end of file' condition (Ctrl+D)
 * and frees allocated resources before exiting.
 *
 * @argc: The count of command-line arguments (unused in this function).
 * @argv: The array of command-line arguments.
 *        argv[0] contains the name of the shell program,
 *        which is used in error messages.
 * Return: 0 for successful execution, non-zero values for errors.
 */

int main(__attribute__((unused)) int argc, char *argv[])
{
	char *cmd = NULL;
	size_t input_size = 0;
	ssize_t chars_read;

	int is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_interactive)
		{
			printf("#OnePieceShell$ ");
		}

		chars_read = getline(&cmd, &input_size, stdin);
		if (chars_read == -1)
		{
			if (is_interactive)
			{
				printf("\n");
			}
			break;
		}

		if (chars_read > 0 && cmd[chars_read - 1] == '\n')
		{
			cmd[chars_read - 1] = '\0';
		}

		execute_command(argv[0], cmd);

		free(cmd);
		cmd = NULL;
		input_size = 0;
	}

	return (0);
}
