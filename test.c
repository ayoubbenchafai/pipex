#include <stdio.h>
#include <stdlib.h>      
#include <string.h>
#include <unistd.h>
#include "pipex.h"



char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	size_dest;

	i = 0;
    if(!dest)
        return (ft_strcpy(dest,src));
	size_dest = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[size_dest] = src[i];
		i++;
		size_dest++;
	}
	dest[size_dest] = '\0';
	return (dest);
}
// ls -la | wc -la
int main(int ac, char **av, char **envp) 
{
    int fd[2];
    int i = 0;

    if(pipe(fd) == -1)
        exit(EXIT_FAILURE);

    pid_t pid1,pid2;

    pid1 = fork();
    if(pid1 == -1)
    {
        perror("Error fork for child 1");
        exit(EXIT_FAILURE);
    }
    else if( pid1 == 0)
    {
        //child 1: ls -la
        int fd_out = open(av[1], O_CREAT | O_RDONLY );
        if(fd_out == -1)
        {
            printf("Error open file : %s", av[1]);
            exit(EXIT_FAILURE);
        }
        dup2(fd_out,0);

        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd_out);
        // execute command : ls -la
        ft_exceve(av[2]);
    }

    pid2 = fork();
    if(pid2 == -1)
    {
        perror("Error fork for child 2");
        exit(EXIT_FAILURE);
    }
    else if( pid2 == 0)
    {
        //child 1: wc -l
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        int fd_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC | 420);
        if(fd_out == -1)
        {
            printf("Error open file : %s", av[4]);
            exit(EXIT_FAILURE);
        }
        dup2(fd_out,1);
        close(fd_out);
        // execute command : wc -la
        ft_exceve(av[3]);
    }
    //close for parent process
    close(fd[0]);
    close(fd[1]);

    //waiting for each child process
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    // printf("hhhhhh.\n");
    return (0);
}

