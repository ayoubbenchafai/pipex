/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:12:49 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/01 12:45:58 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_child1(int fd1, int *fd, char *cmd, char **envp)
{
	ft_close(fd[0]);
	ft_dup2(fd1, 0);
	ft_close(fd1);
	ft_dup2(fd[1], 1);
	ft_close(fd[1]);
	ft_execve(cmd, envp);
}

static void	ft_child2(int fd2, int *fd, char *cmd, char **envp)
{
	ft_close(fd[1]);
	ft_dup2(fd[0], 0);
	ft_close(fd[0]);
	ft_dup2(fd2, 1);
	ft_close(fd2);
	ft_execve(cmd, envp);
}

static void	ft_exec(int fd1, int fd2, char **av, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	ft_pipe(fd);
	pid1 = fork();
	check_errors(pid1, "Error forking first process");
	if (pid1 == 0)
		ft_child1(fd1, fd, av[2], envp);
	pid2 = fork();
	check_errors(pid2, "Error forking second process");
	if (pid2 == 0)
		ft_child2(fd2, fd, av[3], envp);
	ft_close(fd[0]);
	ft_close(fd[1]);
	ft_close(fd1);
	ft_close(fd2);
	ft_wait(pid1);
	ft_wait(pid2);
}

int	main(int ac, char *av[], char *envp[])
{
	int	fd1;
	int	fd2;

	if (ac != 5)
	{
		perror("Invalid arguments.");
		exit(1);
	}
	fd1 = open(av[1], O_RDONLY);
	check_errors(fd1, "Error opening infile");
	fd2 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	check_errors(fd2, "Error opening outfile");
	ft_exec(fd1, fd2, av, envp);
	return (0);
}
