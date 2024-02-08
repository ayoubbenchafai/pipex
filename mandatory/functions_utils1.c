/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 00:42:03 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/01 01:38:40 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_get_path(char **s)
{
	int		i;
	char	*cmd;

	if (!s)
		return (NULL);
	i = 0;
	cmd = "PATH";
	while (s[i] != NULL)
	{
		if (ft_check(cmd, *s[i]))
			return (s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_pathname(char **paths, char **cmdargs)
{
	int		i;
	char	*cmd;

	i = -1;
	while (paths[++i])
	{
		cmd = ft_join_free(paths[i], "/");
		cmd = ft_join_free(cmd, cmdargs[0]);
		if (access(cmd, F_OK | X_OK) == 0)
			break ;
	}
	return (cmd);
}

void	check_execve_error(char *cmd, char **cmdargs, char *envp[])
{
	int	res;

	res = execve(cmd, cmdargs, envp);
	if (res == -1)
	{
		perror("Error execve");
		exit(1);
	}
}

void	ft_execve(char *s, char *envp[])
{
	char	*cmd;
	char	**paths;
	char	**cmdargs;

	paths = ft_split(ft_get_path(envp), ':');
	cmdargs = ft_split(s, ' ');
	if (!paths || !cmdargs)
		exit(1);
	if ((cmdargs[0][0] == '/' && cmdargs[0][1] != '/'))
		check_execve_error(cmdargs[0], cmdargs, envp);
	else if ((cmdargs[0][0] == '/' && cmdargs[0][1] == '/'))
	{
		perror("no such file or directory.");
		exit(1);
	}
	if (access(cmdargs[0], F_OK | X_OK) == 0)
		cmd = cmdargs[0];
	else
		cmd = ft_pathname(paths, cmdargs);
	if (!cmd)
		exit(1);
	check_execve_error(cmd, cmdargs, envp);
}
