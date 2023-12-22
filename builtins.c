#include "shell.h"

/**
 * print_environment_variables - Displays the environment variables
 * of the current process.
 * This function iterates through the global 'environ' array,
 * printing each environment variable to standard output.
 * It's a built-in shell command used to list all the
 * environment variables and their values.
 * It can be helpful for debugging and understanding
 * the shell's environment context.
 *
 * @args: Array of command arguments. This parameter is not used in this
 * function, as the printing of environment variables
 * does not require any arguments.
 * @user_input: User's input string from the standard input. This is not used
 * in this function, but is included for consistency with the function
 * signature required for built-in shell commands.
 * @shell_exit_status: Pointer to the shell's current exit status. Not used
 * in this
 * function, but included for signature consistency.
 * The function does not modify the exit status.
 *
 * Return: Always returns 1, indicating that the shell should continue
 * execution after this command is executed. The return value is used by the
 * shell to determine whether to continue the read-eval-print loop (REPL).
 */

int print_environment_variables(char **args, char *user_input, int
*shell_exit_status)
{
	int i = 0;

	(void)args;
	(void)user_input;
	(void)shell_exit_status;

	if (environ[i] == NULL)
	{
		printf("%s\n", "No environment variables found.");
		return (1);
	}

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);

	return (1);
}

/**
 * exit_shell - Exits the shell program.
 * This function is responsible for terminating the shell program. It can be
 * triggered by the user through a built-in 'exit' command.
 * The function allows for an optional exit status to be specified,
 * which will be used as the exit status of the shell. If no status is provided
 * it uses the current exit status of the shell.
 * The function also handles the case where too many arguments are provided
 * to the 'exit' command, in which case it prints an error message
 * and returns an error code without exiting.
 *
 * @args: Array of command arguments. The first argument
 * (command_args[1]) is optional and, if provided, specifies the exit status.
 * If no argument is provided, or if the argument is not a valid number,
 * the shell exits with the current exit status.
 * @user_input: User's input string from the standard input. This is not used
 * in this function, but is included for consistency with the function
 * signature required for built-in shell commands.
 * @shell_exit_status: Pointer to the shell's current exit status. If the exit
 * command is called without specifying an exit status,
 * the value pointed to by this parameter is used as the exit status.
 *
 * Return: The function returns 0 if an error occurs
 * (e.g., too many arguments are provided). If the function executes
 * successfully, it does not return as the shell process
 * is terminated using the exit() system call.
 *
 * Note: The function takes care of freeing memory allocated for command_args
 * and user_input before exiting the shell.
 * This is important for preventing memory leaks in the shell program.
 */

int exit_shell(char **args, char *user_input, int *shell_exit_status)
{
	int custom_exit_status = 0;

	(void)user_input;

	if (args[1] == NULL)
	{
		free(args);
		free(user_input);
		exit(*shell_exit_status);
	}

	if (args[2] != NULL)
	{
		fprintf(stderr, "Error: Too many arguments for 'exit'.\n");
		return (0);
	}

	custom_exit_status = atoi(args[1]);
	free(args);
	free(user_input);
	exit(custom_exit_status);
}
