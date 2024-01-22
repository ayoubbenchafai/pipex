/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:08:45 by aben-cha          #+#    #+#             */
/*   Updated: 2024/01/22 01:28:49 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*tab;

	i = 0;
	tab = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	int		j;
	size_t	size;
	char	*ptr;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	while (i < size)
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

void ft_close(int fd)
{
    int a;
    
    a = close(fd);
    check_errors(a, "Error close");
}

void ft_dup2(int oldfd, int newfd)
{
    int a;
    
    a = dup2(oldfd, newfd);
    check_errors(a, "Error close");
}

void ft_pipe(int *fd)
{
    check_errors(pipe(fd), "Error creating pipe");
}

void ft_wait(int pid)
{
    pid_t terminated_pid;
    
    terminated_pid = waitpid(pid, NULL, 0);
    if (terminated_pid == -1) 
    {
        perror("Error waiting");
        exit(1);
    } 
}


