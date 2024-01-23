/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:56:25 by aben-cha          #+#    #+#             */
/*   Updated: 2024/01/23 10:08:57 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "get_next_line/get_next_line.h"

void	check_errors(int fd, char *s);
void	ft_close(int fd);
void	ft_dup2(int oldfd, int newfd);
void	ft_pipe(int *fd);
void	ft_wait();
int		ft_check(char *s, char c);
char	*ft_get_path(char **s);
// size_t	ft_strlen(const char *s);
// char	*ft_strdup(const char *s1);
// char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_pathname(char **paths, char **cmdargs);
void	ft_exceve(char *s, char **envp);
// char	*ft_join_free(char *s, const char *buf);

#endif
