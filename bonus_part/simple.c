#include <stdio.h>
#include <stdlib.h>      
#include <string.h>
#include <unistd.h>
#include "pipex.h"
#include <stdbool.h>
void	here_doc_put_in(char **av, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(ret);
			exit(0);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

void	here_doc(char **av)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_put_in(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
}
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