#include <stdio.h>
#include <string.h>
#include "pipex.h"
int main(int ac, char **av) {
    if (ac < 2) 
    {
        printf("Usage: %s <command>\n", av[0]);
        return 1;
    }

    // Set up the command and arguments
    char *shell = "/bin/sh";
    char *args[] = { shell, "-c", av[1],NULL };
    char *env[] = { NULL };

    // Execute the command using execve
    execve(shell, args, env);

    // If execve returns, there was an error
    perror("execve");
    return 1;
}
