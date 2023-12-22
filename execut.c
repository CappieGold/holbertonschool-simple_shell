#include "shell.h"

/**
 * handle_command_execution - Execute a shell command.
 * @command_path: The path to the command.
 * @args: The arguments for the command.
 * @program_name: The name of the program.
 *
 * Return: 1 on success, -1 on failure.
 */
int handle_command_execution(char *command_path, char **args, char *program_name) {
    int resultat, status;
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("shell");
        return (-1);
    }
    if (pid == 0) {
        if (execvp(command_path ? command_path : args[0], args) == -1) {
            fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
            exit(EXIT_FAILURE);
        }
    } else {
		do
		{
			waitpid(pid, &status, WUNTRACED);
			}
			while (!WIFEXITED(status) && !WIFSTOPPED(status));

        resultat = WIFEXITED(status);
    }

    return (resultat);
}

/**
 * check_command - Check and execute a shell command.
 * @args: The arguments for the command.
 * @program_name: The name of the program.
 *
 * Return: 1 on success, -1 on failure.
 */
int check_command(char **args, char *program_name)
{
	int resultat;
	char *command_path;

	command_path = find_command_in_path(args[0]);
	if (command_path == NULL && !is_absolute_or_relative_path(args[0]))
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		return (-1);
	}

	resultat = handle_command_execution(command_path, args, program_name);
	free(command_path);
	return (resultat);
}

/**
 * execute - Execute a shell command or built-in function.
 * @args: The arguments for the command.
 * @program_name: The name of the program.
 * @line: The input line.
 *
 * Return: 0 on success, 1 on exit command, -1 on failure.
 */
int execute(char **args, char *program_name, char *line)
{
	if (args[0] == NULL)
	{
		return (0);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		builtin_exit(args, line);
		return (1);
	}

	return (check_command(args, program_name));
}
