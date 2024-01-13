#include <stdio.h>
#include <string.h>
#include "pipex.h"
#define SIZE 30

//"< infile ls -l | wc -l > outfile"
int main(int ac, char **av)
{
    int fd_open;
    char *buffer = malloc(SIZE + 1);
    if(!buffer)
        return (1);
    
    if(ac == 3)
    {
        int fpipe[2];
        if(pipe(fpipe) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
            free(buffer);
        }
        int id = fork();

        if(id == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
            free(buffer);
        }

        if(id == 0)
        {
            close(fpipe[0]);
            if(access(av[1], R_OK) == -1)
            {
                perror("access");
                exit(EXIT_FAILURE);
                free(buffer);
            }
            int fd_file1 = open(av[1], O_CREAT | O_RDONLY);
            if(fd_file1 == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
                free(buffer);
            }
            int chars_read = read(fd_file1, buffer,30);
            if(write(fpipe[1], buffer, chars_read) == -1)
            {
                perror("write");
                exit(EXIT_FAILURE);
                free(buffer);
            }
            close(fd_file1);
            close(fpipe[1]);
        }
        else
        {
            //parent process
            close(fpipe[1]);
            wait(NULL);
            if(access(av[2], W_OK) == -1)
            {
                perror("access");
                exit(EXIT_FAILURE);
                free(buffer);
            }
            int fd_file2 = open(av[2], O_CREAT | O_WRONLY);
            if(fd_file2 == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
                free(buffer);
            }

            if(read(fpipe[0], buffer, SIZE) == -1)
            {
                perror("write");
                exit(EXIT_FAILURE);
                free(buffer);
            }
            dup2(fd_file2, STDOUT_FILENO);
            close(fd_file2);
            close(fpipe[0]);
            printf("The content of the buffer : %s\n",buffer);
            exit(EXIT_SUCCESS);
        }
    }
    else
        printf("Insufficient arguments.\n");

    free(buffer);  
    return (0);
}
