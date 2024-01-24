/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:42:44 by aben-cha          #+#    #+#             */
/*   Updated: 2024/01/24 17:42:19 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_read(char *s, int fd)
{
	char	*buf;
	int		cr;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (free(s), NULL);
	cr = read(fd, buf, BUFFER_SIZE);
	while (cr)
	{
		if (cr == -1)
			return (free(buf), free(s), NULL);
		buf[cr] = '\0';
		s = ft_join_free(s, buf);
		if (!s)
			return (free(buf), free(s), NULL);
		if (ft_check(s, '\n'))
			break ;
		cr = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (s);
}

static char	*ft_get_line(char *s)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	i += (s[i] == '\n');
	line = malloc(i + 1);
	if (!line)
		return (free(s), NULL);
	while (s[j] && s[j] != '\n')
	{
		line[j] = s[j];
		j++;
	}
	if (s[j] && s[j] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

static char	*ft_set_pointer(char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	i += (s[i] == '\n');
	if (!s[i])
		return (free(s), NULL);
	j = ft_strlen(s) - i;
	res = malloc(j + 1);
	if (!res)
		return (free(s), NULL);
	j = 0;
	while (s[i])
		res[j++] = s[i++];
	res[j] = '\0';
	free(s);
	return (res);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*s;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (s)
			free(s);
		s = NULL;
		return (NULL);
	}
	s = ft_read(s, fd);
	if (!s)
		return (NULL);
	line = ft_get_line(s);
	if (!line)
		return (s = NULL, NULL);
	s = ft_set_pointer(s);
	return (line);
}
