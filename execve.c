#include "shell.h"

/**
 * execute_command - fonction that execute a command enter in input.
*/

void execute_command(char *input)
{
    pid_t pid;
    char **args;

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }

    else if (pid == 0)
    {
        args = malloc(sizeof(char *) * 2);
        args[0] = input;
        args[1] = NULL;

        execve(input, args, __environ);
        perror("execve");

        free(args);
        _exit(EXIT_FAILURE);
    }

    else
        waitpid(pid, NULL, 0);
}