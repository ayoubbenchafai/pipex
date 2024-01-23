/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 00:17:45 by aben-cha          #+#    #+#             */
/*   Updated: 2024/01/23 11:37:25 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line/get_next_line.h"
static void	ft_read(int *fd)
{
    ft_close(fd[1]);
    ft_dup2(fd[0], 0);
    ft_close(fd[0]);
    ft_wait();
}
int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
// void ft_herdoc(char *av)
// {
//     char *s;
//     char *p = ft_strjoin(av, "\n");
//     if(!p)
//         return ;
//     while(1)
//     {
//         s = get_next_line(0);
//         if(!s)
//             return ;
//         if(!strcmp(s, p))
//             break;
//         free(s);
//     }
//     free(p);
// }

void ft_read_input(char **av, int *fd)
{
    char *s;
    size_t  len;

    len = ft_strlen(av[2]);
    close(fd[0]);
    while(1)
    {
        s = get_next_line(0);
        if(!s)
            return ;
        if(ft_strncmp(s, av[2], len) == 0)
        {
            free(s);
            exit(0);
        }
        write(fd[1], s, (len + 1));
        free(s);
        close(fd[1]);
    }
}
static void ft_herdoc(char **av)
{
    int fd[2];
    int pid ;
    
    ft_pipe(fd);
    pid = fork();
    check_errors(pid, "Error forking first process");
    if(pid == 0)
    {
        ft_close(fd[0]);
        ft_read_from_herdoc(av, fd);
    }
    else
        ft_read(fd);
}
static void ft_child(char *cmd, char **envp,bool c, int *outfile)
{
    int fd[2];
    int pid;
    
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
int  ft_open(char **av, int fd, int ac)
{
    int i;
    i = 2;
    if(!ft_strncmp(av[1], "here_doc",ft_strlen(av[1])))
    {
        fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND , 0644);
        i += 1;
    }
    else
        fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC , 0644);
    check_errors(fd, "Error opening outfile");
    return (i);
}
//./pipex file1     cmd1     cmd2   cmd3 ... cmdn file2
//./pipex here_doc  LIMITER  cmd    cmd1 file
//  0       1         2       3
int main(int ac, char **av, char **envp)
{
    int fd_out;
    int fd1 = open(av[1], O_RDONLY);
	if (fd1 < 0)
		check_errors(fd1, "Error opening infile");
    // ft_dup2(fd1, 0);
    // ft_close(fd1);
    // int i = ft_herdoc(av, fd_out, ac);
    // printf("%d,\n",i);
    // while(++i < ac - 1)
    //     ft_child(av[i], envp , (i + 1 == ac - 1), &fd_out);

    // ft_read_from_herdoc(av[2], fd1);--------------------------------
    
    ft_read_herdoc(av);

    return (0);
}