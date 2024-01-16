#include <stdio.h>
#include <stdlib.h>      
#include <string.h>
#include <unistd.h>
#include "pipex.h"

void ft_exceve(char *av[], char **envp)
{
    char *path_env = ft_get_path(environ);
    char **cmdargs;
    char **pathname;
    char *cmd;
    int i;
    
    pathname = ft_split(path_env, ':');
    if(!pathname)
        exit(EXIT_FAILURE);
    
    ///bin/ls
    // cmdargs == "ls -la"
    cmdargs = ft_split(av[1], ' ');
    if(!cmdargs)
        exit(EXIT_FAILURE);
    i = 0;
    while(pathname[i++])
    {
        if(cmdargs[0][0] == '/' /*|| (cmdargs[0][0] == '.' && cmdargs[0][1] == '/')*/)
            cmd = ft_strjoin(pathname[i], cmdargs[0]);
        else
        {
            cmd = ft_strjoin(pathname[i], "/");
            cmd = ft_strjoin(cmd, cmdargs[0]);
        }
        if(!cmd)
        {
            free(pathname);
            free(cmdargs);
            exit(EXIT_FAILURE);
        }
        if(access(cmd, X_OK) == 0)
            break;
        else 
            free(cmd);
    }
    printf("cmd : %s\n",cmd);
    execve(cmd, cmdargs, envp);
        printf("error TEST\n");
        // perror
    free(cmd);
    exit(EXIT_FAILURE);
}
int main(int ac, char **av, char **envp) 
{
    // char **cmdargs = ft_split("./ls -la", ' ');

    // if(!cmdargs)
    //     exit(EXIT_FAILURE);
    //     printf("No to join, %c\n",cmdargs[0][1]);

    ft_exceve(av,envp);

    return (0);
}

