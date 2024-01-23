/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 00:17:45 by aben-cha          #+#    #+#             */
/*   Updated: 2024/01/23 00:53:01 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line/get_next_line.h"
static void	ft_read(int *fd)
{
    ft_close(fd[1]);
    ft_dup2(fd[0], 0);
    ft_close(fd[0]);
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
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

void ft_read_from_herdoc(char *av, int *fd)
{
    char *s;
    char *p;
    
    p = ft_join_free(av, "\n");
    if(!p)
        return ;
    while(1)
    {
        s = get_next_line(0);
        if(!s)
            return ;
        if(ft_strcmp(s, p) == 0)
        {
            break;
            exit(0);
        }
        write(fd[1], s, ft_strlen(s));
        close(fd[1]);
        free(s);
    }
}
// static void ft_child(char *av, char **envp,bool c, int *outfile)
// {
//     int fd[2];
//     int pid ;
    
//     ft_pipe(fd);
//     pid = fork();
//     check_errors(pid, "Error forking first process");
//     if(pid == 0)
//     {
//         ft_close(fd[0]);
//         if(c)
//         {
//             ft_dup2(*outfile, 1);
//             ft_close(*outfile);
//         }
//         else
//             ft_read_from_herdoc(&av[2], fd);
//     }
//     else
//         ft_read(fd);
// }
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
char	*ft_join_free(char *s, const char *buf)
{
	char	*r;

	r = ft_strjoin(s, buf);
	free(s);
	return (r);
}
int  ft_herdoc(char **av, int fd, int ac)
{
    int i;
    i = 2;
    if(!ft_strcmp(av[1], "here_doc"))
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
    int i = ft_herdoc(av, fd_out, ac);
    while(++i < ac - 1)
        ft_child(av[i], envp , (i + 1 == ac - 1), &fd_out);
    // i = i - 2;
    // while(i--)
    //     ft_wait();
    return (0);
}