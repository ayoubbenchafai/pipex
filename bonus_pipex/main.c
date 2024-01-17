#include <stdio.h>
#include <stdlib.h>      
#include <string.h>
#include <unistd.h>
#include "pipex.h"

int ft_get_number_of_cmd(int ac)
{
    return (ac - 3);
}

static void ft_child1(int fd1, int *fpipe,char *cmd, int index)
{
    close(fpipe[0]);
    //check dup != -1
    if(index == 0)
    {
        dup2(fd1, 0);
        close(fd1);
    }
    

    //check dup != -1
    dup2(fpipe[1], 1);
    close(fpipe[1]);

    // execute cmd1 for the child process1:
    ft_exceve(cmd);
}

static void ft_child2(int fd2, int *fpipe,char *cmd, int index,int n_cmd)
{
    close(fpipe[1]);
    //check dup != -1
    dup2(fpipe[0], 0);
    close(fpipe[0]);

    //check dup != -1
    if(index == n_cmd - 1)
    {
        dup2(fd2, 1);
        close(fd2);
    }
    

    // execute cmd2 for the child process2:
    ft_exceve(cmd);
}
int main(int ac, char *av[])
{
    if(ac < 5)
    {   
        printf("Insufficient arguments");
        return (0);
    }
    int fd1;
    int fd2;
    // int status;
    int fd[2];

    if(pipe(fd) == -1)
    {
        perror("Error pipe");
        exit(EXIT_FAILURE);
    }
    // check_errors(pipe(fd), "Error pipe");
    fd1 = open(av[1], O_CREAT | O_RDONLY);
    if(fd1 == -1)
    {
        printf("Error open file : %s\n", av[1]);
        exit(EXIT_FAILURE);
    }   
     
    //permission for outfile
    fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC);
    if(fd2 == -1)
    {
        printf("Error open file : %s\n", av[ac - 1]);
        exit(EXIT_FAILURE);
    }
    
// i = 0 1
// ./a.out file1 "ls -la" "wc -lwc" file2
//   0      1       2        3        4
//                           ac - 2       ac - 1
    int i = 0;
    pid_t pid;
    int n_cmd = ft_get_number_of_cmd(ac);
    int j = 2;
    while(i++ < n_cmd && j++ < ac - 1)
    {
        printf("test.\n");
        pid = fork();
        if(pid < 0)
        {
            exit(EXIT_FAILURE);
            break;
        }
        if(pid == 0)
            ft_child1(fd1, fd, av[j], i);
        else
        {
            wait(NULL);
            ft_child2(fd2, fd, av[j + 1], j, n_cmd);
        }
    }
    printf("fin.\n");

    // printf("%s\n", av[2]);
    // printf("len %d\n", ac);
    // printf("len %d\n", ft_get_number_of_cmd(ac));

    return (0);
}

