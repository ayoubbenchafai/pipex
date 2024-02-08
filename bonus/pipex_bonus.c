/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:28:56 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/01 12:42:04 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_execve_error(char *cmd, char **cmdargs, char *envp[])
{
	int	res;

	res = execve(cmd, cmdargs, envp);
	if (res == -1)
	{
		perror("Error execve.");
		exit(1);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	int	i;
	int	outfile;

	if (ac < 5)
	{
		perror("Invalid Arguments!.");
		exit(1);
	}
	outfile = 0;
	i = ft_open(av, ac, &outfile, 1);
	while (++i < ac - 1)
		ft_process(av[i], envp, (i + 1 == ac - 1), &outfile);
	ft_close(outfile);
	i -= 2;
	while (i--)
		ft_wait();
	return (0);
}
