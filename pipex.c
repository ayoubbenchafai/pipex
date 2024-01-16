#include <stdio.h>
#include <string.h>
#include "pipex.h"
#define SIZE 10000

void ft_error(int fd, char *s, char *buffer)
{
    if(fd == -1)
    {
        perror(s);
        exit(EXIT_FAILURE);
        free(buffer);
    }
}
//< infile ls -l | wc -l > outfile
int main(int ac, char **av)
{
    int fpipe[2];
    
    //execute command
    char *shell = "/bin/sh";
    char *args[]= {shell, "-c", av[2], NULL};
    char *args1[]= {shell, "-c", av[3], NULL};
    char *env[] = {NULL};
    //buffer : array of char 
    char *buffer = malloc(SIZE + 1);
    if(!buffer)
        return (1);

    

    ft_error(pipe(fpipe), "Error pipe",buffer);
    int id = fork();

    ft_error(id,"Error fork",buffer);
    if(id == 0)
    {
        //close reading ..
        close(fpipe[0]);
        //child process.
        ft_error(access(av[1], R_OK), "Error access to file",buffer);

        int fd1 = open(av[1], O_CREAT | O_RDONLY);
        ft_error(fd1, "Error opening",buffer);
        // read(fd1, buffer,SIZE);
        write(fpipe[1], buffer, SIZE);
        dup2(fpipe[1], 1);
        // dup2(fd1, 0);
        close(fpipe[1]);
        close(fd1);
        // ft_error(execve(shell, args, env),"Error execve",buffer);
        ft_exceve(av,envp)
    }
    else
    {
        close(fpipe[1]);
        //parent process.
        wait(NULL);
        ft_error(access(av[4], W_OK), "Error access to file",buffer);

        int fd2 = open(av[4], O_CREAT | O_WRONLY);
        ft_error(fd2, "Error opening",buffer);

        read(fpipe[0], buffer ,SIZE);
        dup2(fpipe[0],0);
        dup2(fd2,1);
        close(fpipe[0]);
        close(fd2);
        // int i = 3;
        ft_error(execve(shell, args1, env),"Error execve",buffer);
        printf("hello ayoub.\n");
    }
    free(buffer);  
    exit(EXIT_SUCCESS);
    return (0);
}


//./a.out infile "ls -la" "wc -lwc" outfile