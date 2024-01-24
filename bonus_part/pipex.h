/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:56:25 by aben-cha          #+#    #+#             */
/*   Updated: 2024/01/24 01:03:15 by aben-cha         ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

//get_ne
char	*ft_join_free(char *s, const char *buf);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strjoin(char *s1, const char *s2);
char	*get_next_line(int fd);

//func2
void	check_errors(int fd, char *s);
void	ft_close(int fd);
void	ft_dup2(int oldfd, int newfd);
void	ft_pipe(int *fd);
void	ft_wait();

//fun1
int	    ft_strcmp(char *s1, char *s2);
int		ft_check(char *s, char c);
char	*ft_get_path(char **s);
char	*ft_pathname(char **paths, char **cmdargs);
void	ft_exceve(char *s, char **envp);


//her_doc
void ft_read_input(char **av, int *fd);
void	ft_read_pipe(int *fd);
int  ft_open(char **av, int ac, int *outfile, int i);
void ft_process(char *cmd, char **envp, bool c, int *outfile);

//split
char	**ft_split(char const *s, char c);

#endif
