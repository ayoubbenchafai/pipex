#include <stdio.h>
#include <string.h>
#include "pipex.h"
void ft_error(int fd, char *s)
{
    if(fd == -1)
    {
        perror(s);
        exit(EXIT_FAILURE);
    }
}
int main(int ac, char *av[], char *envp[]) 
{
    if(ac < 5)
    {
        printf("Insufficient arguments.\n");
        exit(EXIT_FAILURE);
    }
    int fd[2];
    pid_t pid1,pid2;

    if(pipe(fd) == -1)
    {
        perror("Error pipe");
        exit(EXIT_FAILURE);
    }
    
    pid1 = fork();
    if(pid1 == -1)
    {
        perror("Error fork for pid1.");
        exit(EXIT_FAILURE);
    }
    else if(pid1 == 0)
    {
        //child process : ls -la 
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        if(access(av[1], R_OK) == -1)
        {
            perror("Error access file : infile");
            exit(EXIT_FAILURE);
        }
        int  f_1 = open(av[1], O_CREAT | O_RDONLY);
        if(f_1 == -1)
        {
            perror("Error opening file : infile");
            exit(EXIT_FAILURE);
        }

        dup2(f_1, 0);
        close(f_1);

        char *shell = "/bin/sh";
        char *args[]= {shell, "-c",av[2], NULL};
        execve(shell, args, NULL);
        perror("Error execve wc");
        exit(EXIT_FAILURE);

        // ft_exceve(av, envp);

    }

    pid2 = fork();
    if(pid2 == -1)
    {
        perror("Error fork for pid2.");
        exit(EXIT_FAILURE);
    }
    else if(pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        //child process : ls -la 
        if(access(av[4], W_OK) == -1)
        {
            perror("Error access file : outfile");
            exit(EXIT_FAILURE);
        }
        int  f_2 = open(av[4], O_CREAT | O_WRONLY | O_APPEND);
        if(f_2 == -1)
        {
            perror("Error opening file : outfile");
            exit(EXIT_FAILURE);
        }

        dup2(f_2,STDOUT_FILENO);
        close(f_2);
        // ft_exceve(av, envp);
        char *shell = "/bin/sh";
        // char **arg_split = ft_split(av[2],' ');
        char *args[]= {shell, "-c",av[3], NULL};
        if(execve(shell, args, NULL) == -1)
        {
            perror("Error execve wc");
            exit(EXIT_FAILURE);
        }
    }

    
    
    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    
    // printf("zahia.\n");
    return 0;
}
