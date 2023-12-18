#include "shell.h"

/**
 * xecute_command - Execute a command (enter in input on our shell)
 * with aguments.
 *
 * @cmd: The command to execute
*/

void execute_command(char *cmd)
{
    char *argv[64];
    char *token;
    pid_t pid;
    int argc = 0, i;

    if (cmd == NULL)
    {
        perror("execute: cmd is NULL");
        return;
    }
    token = strtok(cmd, " \n");
    while (token != NULL && argc < 63)
    {
        argv[argc++] = token;
        token = strtok(NULL, " \n");
    }
    argv[argc] = NULL;
    if (argc == 0)
        return;
    if (strcmp(argv[0], "exit") == 0)
        exit(0);
    if (strcmp(argv[0], "env") == 0)
    {
        for (i = 0; environ[i] != NULL; i++)
            printf("%s\n", environ[i]);
        return;
    }
    if (argv[0][0] == '/')
    {
        if (access(argv[0], X_OK) == 0)
        {
            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                return;
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
        }
        else
        {
            printf("command not found: %s\n", argv[0]);
        }
    }
    else
    {
        char *full_path = find_command_in_path(argv[0]);
        if (full_path == NULL)
        {
            printf("command not found: %s\n", argv[0]);
            return;
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return;
        }
        else if (pid == 0)
        {
            argv[0] = full_path;
            if (execve(argv[0], argv, environ) == -1)
            {
                free(full_path);
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
            free(full_path);
        }
    }
}
