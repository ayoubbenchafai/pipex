/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:12:49 by aben-cha          #+#    #+#             */
/*   Updated: 2024/01/23 00:02:34 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_read(int *fd)
{
    ft_close(fd[1]);
        ft_dup2(fd[0], 0);
        ft_close(fd[0]);
}
static void ft_child(char *cmd, char **envp,bool c, int *outfile)
{
    int fd[2];
    int pid ;
    ft_pipe(fd);

    pid = fork();

    check_errors(pid, "Error forking first process");
    if(pid == 0)
    {
        ft_close(fd[0]);
        if(c)
        {
            ft_dup2(*outfile, 1);
            ft_close(*outfile);
        }
        else
        {
            ft_dup2(fd[1], 1);
            ft_close(fd[1]);
        }
        ft_exceve(cmd, envp);
    }
    else
        ft_read(fd);
}

int	main(int ac, char **av, char **envp)
{
	int	fd1;
	int	fd2;
    int i;
    
	if (ac < 5)
	{
		perror("Insufficient arguments.");
		exit(1);
	}
	fd1 = open(av[1], O_RDONLY);
	if (fd1 < 0)
		check_errors(fd1, "Error opening infile");
    ft_dup2(fd1, 0);
    ft_close(fd1);
	fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	check_errors(fd1, "Error opening outfile");
    i = 1;
    while(++i < ac - 1)
        ft_child(av[i], envp , (i + 1 == ac - 1), &fd2);
    i = i - 2;
    while(i--)
        ft_wait();
	return (0);
}
