#include <stdio.h>
#include <stdlib.h>      
#include <string.h>
#include <unistd.h>
#include "pipex.h"

static void check_errors(int fd, char *s)
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
    dup2(fpipe[1], 1);
    close(fpipe[1]);
    
    
    dup2(fd1, 0);
    close(fd1);

    //check dup != -1
    

    // execute cmd1 for the child process1:
    // ft_exceve(cmd);
}

static void ft_child2(int fd2, int *fpipe,char *cmd )
{
    close(fpipe[1]);
    //check dup != -1
    dup2(fpipe[0], 0);
    close(fpipe[0]);

    //check dup != -1
    // if(index == ac - 2)
    
    // {
        dup2(fd2, 1);
        close(fd2);
    // }

    // execute cmd2 for the child process2:
    // ft_exceve(cmd);
}
static void ft_wait(pid_t pid, int *a)
{
    pid_t terminated_pid;
    
    terminated_pid = waitpid(pid, a, 0);
    if (terminated_pid == -1) 
    {
        perror("waitpid");
        exit(EXIT_FAILURE);
    } 
    exit(EXIT_SUCCESS);
}
int main(int ac, char *av[])
{
    int fd1;
    int fd2;
    // int status;
    int fd[2];
    pid_t pid1,pid2;

    if(pipe(fd) == -1)
    {
        perror("Error pipe");
        exit(EXIT_FAILURE);
    }
    // check_errors(pipe(fd), "Error pipe");
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
     
    pid1 = fork();
    check_errors(pid1, "Error fork for child 1");
    if(pid1 == 0)
        ft_child1(fd1, fd, av[2]);
    
    pid2 = fork();
    check_errors(pid2, "Error fork for child 2");
    if(pid2 == 0)
        ft_child2(fd2, fd, av[ac - 2]);
    
    close(fd[0]);
    close(fd[1]);

    ft_wait(pid1, NULL);
    ft_wait(pid2, NULL);
    // waitpid(pid1, &status, 0);
    // waitpid(pid2, &status, 0);
    return (0);
}



