#include <stdio.h>
#include <stdlib.h>      
#include <string.h>
#include <unistd.h>
#include "pipex.h"
#include <stdbool.h>

void ft_open(int *infile, int *outfile,char **av, int ac)
{
    *infile = open(av[1], O_CREAT | O_RDONLY);
    if(*infile)
    {
        perror("Error open infile");
        exit(1);
    }
    *outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC , 0644);
    if(*outfile)
    {
        perror("Error open outfile");
        exit(1);
    }
}
void ft_pipe(int *fd)
{
    if(pipe(fd) == -1)
    {
        perror("Error pipe");
        exit(1);
    }
}
void ft_child(char *cmd, char **envp,bool c, int *outfile)
{
    int fd[2];
    ft_pipe(fd);

    int pid = fork();

    if(pid < 0)
    {
        perror("Error fork");
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
        wait(NULL);
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }
}
// ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
int main(int ac, char **av, char **envp)
{
    if(ac < 5)
    {
        printf("insuficient arguments.\n");
        exit(1);
    }

    int fd1,fd2;

    // ft_open(&fd1, &fd2, av, ac);

    fd1 = open(av[1], O_RDONLY);
    if(fd1 == -1)
    {
        printf("Error open file : %s\n", av[1]);
        exit(EXIT_FAILURE);
    }   
     
    //permission for outfile
    fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC , 0644);
    if(fd2 == -1)
    {
        printf("Error open file : %s\n", av[ac - 1]);
        exit(EXIT_FAILURE);
    }

    int i = 2;
    while(i < ac - 1)
    {
        // printf("av[i] : %s,%d\n",av[ac -1],i);
        ft_child(av[i], envp , (i + 1 == ac - 1), &fd2);
        i++;
    }
    return (0);
}