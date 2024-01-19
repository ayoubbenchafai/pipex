#include "pipex.h"
#include <stdbool.h>

void ft_child(char *av,char **envp)
{
}

void ft_open(int *infile, int *outfile, char **av, int ac)
{
    *infile = open(av[1],  O_CREAT | O_RDONLY);
    if(*infile == -1)
    {
        perror("Error open infile.");
        exit(1);
    }

    *outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC , 0644);
    if(*outfile == -1)
    {
        perror("Error open infile.");
        exit(1);
    }
}

void  ft_pipe(int *fpipe)
{
    if(pipe(fpipe) == -1)
    {
        perror("Error pipe.");
        exit(1);
    }
}
// ft_child_process(char **av,int ac)
// {

// }
void ft_process(char **av, char **envp, bool c, int outfile)
{
    int pid;
    int fd[2];

    ft_pipe(fd);
    
    pid = fork();
    if(pid < 0)
    {
        perror("Error fork.");
        exit(1);
    }
    if(pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        if(c) // i == ac - 1
        {
            dup2(outfile, 0);
            close(outfile);
        }
        ft_exceve(*av,envp);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
    }
}
int  main(int ac,char **av,char **envp)
{
    if(ac < 5)
    {
        printf("Insufficient arguments.\n");
        exit(1);
    }
    int fd1,fd2;

    ft_open(&fd1, &fd2, av, ac);


    int pid = fork();

    if(pid < 0)
    {
        perror("Error fork.");
        exit(1);
    }

    if(pid == 0)

    return (0);
}