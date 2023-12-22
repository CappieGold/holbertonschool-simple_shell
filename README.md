# C - Simple Shell

create our own shell, a simple UNIX command interpreter written in the C programming language.

## Learning Objectives

At the end of this project, you are expected to be able to explain to anyone, without the help of Google:
- Who designed and implemented the original Unix operating system
- Who wrote the first version of the UNIX shell
- Who invented the B programming language (the direct predecessor to the C programming language)
- Who is Ken Thompson
- How does a shell work
- What is a pid and a ppid
- How to manipulate the environment of the current process
- What is the difference between a function and a system call
- How to create processes
- What are the three prototypes of `main`
- How does the shell use the `PATH` to find the programs
- How to execute another program with the `execve` system call
- How to suspend the execution of a process until one of its children terminates
- What is `EOF` / “end-of-file”?


## Output

- Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
- The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)

Example of error with `sh`:
```bash
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```

Same error with our own program `hsh`:
```bash
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```

## Functions and system calls+ use

- all functions from string.h
- `access` (man 2 access)
- `close` (man 2 close)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getline` (man 3 getline)
- `isatty` (man 3 isatty)
- `perror` (man 3 perror)
- `printf` (man 3 printf)
- `fprintf` (man 3 fprintf)
- `sprintf` (man 3 sprintf)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `write` (man 2 write)

## Compilation

To compile the project, use the following command:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Testing

Our own shell should work like this in interactive mode:

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

But also in non-interactive mode:

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
## exemple output of own shell

```bash
Jérémy_And_Jonathan_Shell$ ls
AUTHORS  builtins.c  check.c  executeCmd.c  function_need.c  hsh  man_1_simple_shell  README.md  shell.c  shell.h  tokenizer.c
Jérémy_And_Jonathan_Shell$ pwd
/workspaces/workplace/holbertonschool-simple_shell
Jérémy_And_Jonathan_Shell$ /bin/ls
AUTHORS  builtins.c  check.c  executeCmd.c  function_need.c  hsh  man_1_simple_shell  README.md  shell.c  shell.h  tokenizer.c
Jérémy_And_Jonathan_Shell$ 
```

```bash
Jérémy_And_Jonathan_Shell$ ls -la
total 72
drwxr-xr-x 16 vscode vscode   512 Dec 21 23:57 .
drwxr-xr-x  8 vscode vscode   256 Dec 11 10:08 ..
-rw-r--r--  1 vscode vscode   185 Dec 22 00:12 AUTHORS
-rw-r--r--  1 vscode vscode  3623 Dec 21 01:19 builtins.c
-rw-r--r--  1 vscode vscode  3341 Dec 21 23:57 check.c
-rw-r--r--  1 vscode vscode   336 Dec 11 15:13 .editorconfig
-rw-r--r--  1 vscode vscode  3690 Dec 21 01:19 executeCmd.c
-rw-r--r--  1 vscode vscode  2988 Dec 21 01:19 function_need.c
drwxr-xr-x 16 vscode vscode   512 Dec 22 00:12 .git
-rw-r--r--  1 vscode vscode    18 Dec 21 01:13 .gitignore
-rwxr-xr-x  1 vscode vscode 19136 Dec 21 23:57 hsh
-rw-r--r--  1 vscode vscode  1109 Dec 21 01:19 man_1_simple_shell
-rw-r--r--  1 vscode vscode  4331 Dec 22 00:12 README.md
-rw-r--r--  1 vscode vscode  1923 Dec 21 01:19 shell.c
-rw-r--r--  1 vscode vscode  1645 Dec 21 01:19 shell.h
-rw-r--r--  1 vscode vscode  3818 Dec 21 01:19 tokenizer.c
Jérémy_And_Jonathan_Shell$ 
```

## FLOWCHART

The following flowchart illustrates the basic operation of the shell:

```mermaid
flowchart TD
    A[Start Shell] --> B[Read User Input]
    B --> C{Is Input Empty?}
    C -- Yes --> B
    C -- No --> D{Is Input a Builtin Command?}
    D -- Yes --> E[Execute Builtin Command]
    E --> F{Was Execution Successful?}
    F -- Yes --> B
    F -- No --> G[Handle Error]
    G --> B
    D -- No --> H[Parse and Tokenize Input]
    H --> I[Resolve Command Path]
    I --> J{Is Path Valid?}
    J -- Yes --> K[Execute Command]
    K --> M[Wait for Command Completion with waitpid]
    M --> L{Was Execution Successful?}
    L -- Yes --> B
    L -- No --> G
    J -- No --> G