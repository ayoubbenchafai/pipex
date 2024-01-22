#include <stdio.h>
#include <stdlib.h>      
#include <string.h>
#include <unistd.h>
#include "pipex.h"
#include <stdbool.h>

void ft_child(char *cmd, char **envp,bool c, int *outfile)
{
    int fd[2];
    ft_pipe(fd);

    int pid = fork();

    if(pid < 0)
    {
        perror("Error forking first process");
        exit(1); 
    }
    if(pid == 0)
    {
        close(fd[0]);
        if(c)
        {
            dup2(*outfile, 1);
            close(*outfile);
        }
        else
        {
            dup2(fd[1], 1);
            close(fd[1]);
        }

        ft_exceve(cmd, envp);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }
}

int main(int ac, char **av, char **envp)
{
    

    int fd1,fd2;


    fd1 = open(av[1], O_CREAT | O_RDONLY);
    if(fd1 == -1)
    {
        printf("Error open file : %s\n", av[1]);
        exit(EXIT_FAILURE);
    }   
    dup2(fd1, 0);
    close(fd1);
    
    fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC , 0644);
    if(fd2 == -1)
    {
        printf("Error open file : %s\n", av[ac - 1]);
        exit(EXIT_FAILURE);
    }

    int i = 2;
    while(i < ac - 1)
    {
        
        ft_child(av[i], envp , (i + 1 == ac - 1), &fd2);
        i++;
    }
    return (0);
}