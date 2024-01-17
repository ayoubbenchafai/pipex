#include <stdio.h>
#include <stdlib.h>      
#include <string.h>
#include <unistd.h>
#include "pipex.h"

static void ft_error(int fd, char *s)
{
    if(!s)
        return ;
    if(fd == -1)
    {
        perror(s);
        exit(EXIT_FAILURE);
    }
}
static void ft_child1(int fd1, int *fpipe,char *cmd)
{
    close(fpipe[0]);
    //check dup != -1
    dup2(fd1, 0);
    close(fd1);

    //check dup != -1
    dup2(fpipe[1], 1);
    close(fpipe[1]);

    // execute cmd1 for the child process1:
    ft_exceve(cmd);
}

static void ft_child2(int fd2, int *fpipe,char *cmd)
{
    close(fpipe[1]);
    //check dup != -1
    dup2(fpipe[0], 0);
    close(fpipe[0]);

    //check dup != -1
    dup2(fd2, 1);
    close(fd2);

    // execute cmd2 for the child process2:
    ft_exceve(cmd);
}
int main(int ac, char *av[], char *envp[])
{
    int fd1;
    int fd2;
    int status;
    int fd[2];
    pid_t pid1,pid2;

    //check of argv 

    if(pipe(fd) == -1)
    {
        perror("Error pipe");
        exit(EXIT_FAILURE);
    }    
    fd1 = open(av[1], O_CREAT | O_RDONLY);
    if(fd1 == -1)
    {
        printf("Error open file : %s\n", av[1]);
        exit(EXIT_FAILURE);
    }    
    //permission for outfile
    fd2 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC );
    if(fd2 == -1)
    {
        printf("Error open file : %s\n", av[4]);
        exit(EXIT_FAILURE);
    }
    printf("HHHhh4.\n");

    pid1 = fork();
    if(pid1 == -1)
    {
        perror("Error fork for child 1");
        exit(EXIT_FAILURE);
    }
    else if(pid1 == 0)
        ft_child1(fd1, fd, av[2]);

    pid2 = fork();
    if(pid2 == -1)
    {
        perror("Error fork for child 2");
        exit(EXIT_FAILURE);
    }
    else if(pid2 == 0)
        ft_child2(fd2, fd, av[3]);
    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    //pipe() oui 100
    //child 1 oui 100
    //child 2 oui 100
    //close(0) && close(1); ==> for the parent
    //waiting each child

    printf("test.\n");
    return (0);
}



