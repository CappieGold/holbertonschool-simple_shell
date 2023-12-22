#include "shell.h"

/**
 * main - Main loop of the shell for processing user input.
 * This function continuously reads input from the standard input (stdin) and
 * executes commands until an EOF (End Of File)
 * is encountered or an exit command is executed.
 * It supports both interactive and non-interactive modes,
 * dynamically allocating memory for user input and parsed commands.
 *
 * @argc: The count of command-line arguments (not used in this function).
 * @argv: The array of command-line arguments, used for error messaging.
 * Return: Returns 0 upon successful completion.
 *
 * In each iteration, the function checks if the shell is in interactive mode
 * (when input is from a terminal), prompts the user if so, and reads a line
 * of input. The input is then checked for being only whitespace before being
 * tokenized into commands. It then delegates the execution of commands to the
 * appropriate handler function and frees allocated memory.
 */

int main(int argc __attribute__((unused)), char *argv[])
{
	char **parsed_commands = NULL;
	char *user_input = NULL;
	int is_interactive_mode = 1, shell_exit_status = 0;
	size_t input_buffer_size = 0;
	ssize_t getline_return = 0;

	while (is_interactive_mode && getline_return != EOF)
	{
		input_buffer_size = 0;
		is_interactive_mode = isatty(STDIN_FILENO);

		if (is_interactive_mode)
			write(STDOUT_FILENO, "Jérémy_And_Jonathan_Shell$ ", 29);

		getline_return = getline(&user_input, &input_buffer_size, stdin);

		if (getline_return == -1)
		{
			free(user_input);
			break;
		}
		if (check_if_input_is_whitespace(user_input))
		{
			free(user_input);
			continue;
		}
		parsed_commands = tokenize_command_input(user_input);

		if (*parsed_commands[0] == '\0')
			continue;

		is_interactive_mode = execute_builtin_or_command(parsed_commands,
		user_input, argv, &shell_exit_status);

		free(user_input);
		free(parsed_commands);
	}
	return (0);
}
