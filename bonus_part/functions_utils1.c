/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 00:42:03 by aben-cha          #+#    #+#             */
/*   Updated: 2024/01/24 00:19:40 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_check(char *s, char c)
{
	if (!s)
		return (1);
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
		if (cmdargs[0][0] == '/')
			cmd = ft_join_free(paths[i], cmdargs[0]);
		else
		{
			cmd = ft_join_free(paths[i], "/");
			cmd = ft_join_free(cmd, cmdargs[0]);
		}
		if (access(cmd, F_OK | X_OK) == 0)
			break ;
	}
	return (cmd);
}

void	ft_exceve(char *s, char **envp)
{
	char	*cmd;
	char	**paths;
	char	**cmdargs;

	paths = ft_split(ft_get_path(envp), ':');
	cmdargs = ft_split(s, ' ');
	cmd = ft_pathname(paths, cmdargs);
	if (!cmd)
		exit(1);
	if (ft_check(s, 39))
		cmdargs = ft_split(s, 39);
	else if (ft_check(s, '"'))
		cmdargs = ft_split(s, '"');
	execve(cmd, cmdargs, envp);
	perror("Error execve.");
	free(cmdargs);
}
