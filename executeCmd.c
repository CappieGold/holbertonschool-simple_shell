#include "shell.h"

/**
 * execute_command - Executes a command by creating a new process.
 * This function attempts to execute a given command, which involves resolving
 * the command path, forking a new process, and using execve to run the command
 * in the child process. The parent process waits for the command's execution
 * to complete and captures its exit status.
 *
 * @args: Array of command tokens, where the first token is the
 *        command to be executed.
 * @shell_args: Array of arguments passed to the shell, used for error
 *              messaging.
 * @shell_exit_status: Pointer to an integer to store the exit status
 *                     of the executed command.
 * Return: Returns 1 on successful execution of the function. In the case of
 *         a failure in command execution or process creation, an error
 *         message is printed and 1 is returned.
 *
 * Note: This function handles the dynamic memory allocated for resolving the
 *       command path. It ensures that this memory is freed appropriately to
 *       avoid memory leaks.
 */

int execute_command(char **args, char **shell_args, int *shell_exit_status)
{
	pid_t child_pid;
	int child_status;
	char *resolved_command_path;

	resolved_command_path = check_command_path(args, shell_args);
	if (strcmp(resolved_command_path, "Fail access") == 0)
		return (1);
	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(resolved_command_path, args, environ) == -1)
		{
			perror("execve fail");
			exit(EXIT_FAILURE);
		}
	}
	else if (child_pid < 0)
	{
		perror("Error creating child process");
		free(resolved_command_path);
		return (1);
	}
	else
	{
		waitpid(-1, &child_status, 0);
		if (WIFEXITED(child_status))
			*shell_exit_status = WEXITSTATUS(child_status);
		if (args[0][0] != '/' && args[0][0] != '.')
			free(resolved_command_path);
		return (1);
	}
	return (1);
}

/**
 * execute_builtin_or_command - Executes a builtin command
 *                              or an external command.
 * This function determines whether the provided command is a builtin shell
 * command or an external command. If it's a builtin command, it executes it
 * directly. If it's an external command, it delegates execution to the
 * execute_command function. It's an integral part of the shell's command
 * processing pipeline.
 *
 * @args: Array of command tokens, where the first token is the
 *        command to be executed.
 * @user_input: The original user input string, used by certain builtins.
 * @shell_args: Array of arguments passed to the shell, used for error
 *              messaging and other purposes.
 * @shell_exit_status: Pointer to an integer to store the exit status
 *                     of the executed command.
 * Return: Returns 1 to indicate successful execution or to continue the main
 *         loop; returns 0 to signal an exit from the main loop.
 *
 * Note: This function is responsible for determining the type of command
 *       (builtin or external) and ensuring the appropriate execution path
 *       is taken. It leverages an array of structs mapping builtin command
 *       names to their corresponding functions.
 */

int execute_builtin_or_command(char **args, char *user_input,
			char **shell_args, int *shell_exit_status)
{
	int i = 0;

	builtins_command_t builtin_commands[] = {
		{"exit", exit_shell},
		{"env", print_environment_variables},
		{NULL, NULL}
	};

	while (builtin_commands[i].command_name)
	{
		if (strcmp(builtin_commands[i].command_name, args[0]) == 0)
		{
			return ((int)((*builtin_commands[i].command_func)
			(args, user_input, shell_exit_status)));
		}
		i++;
	}
	return (execute_command(args, shell_args, shell_exit_status));
}
