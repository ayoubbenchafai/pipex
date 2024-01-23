/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:28:56 by aben-cha          #+#    #+#             */
/*   Updated: 2024/01/23 16:21:36 by aben-cha         ###   ########.fr       */
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
static void ft_read_input(char **av, int *fd)
{
    size_t len_s;
    char *s;
    char *p;
    
    p = ft_strjoin(av[2], "\n");
    if(!p)
        return ;
    while(1)
    {
        s = get_next_line(0);
        if(!s)
            return ;
        if(ft_strcmp(s, p) == 0)
        {
            free(s);
            exit(0);
        }
        len_s  = ft_strlen(s); 
        write(fd[1], s, sizeof(char) *(len_s));
        free(s);
    }
}
static void ft_child(char *cmd, char **envp, bool c, int *outfile)
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
        ft_read_input(av, fd);
        ft_close(fd[1]);
    }
    else
        ft_read(fd);
}
int  ft_open(char **av,int ac, int *outfile, int i)
{
    int infile;
    
    if(ft_strcmp(av[1], "here_doc") == 0)
    {
        if(ac < 6)
            exit(1);
        *outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		check_errors(*outfile, "Error opening outfile");
        ft_herdoc(av);
        i += 1;
    }
    else
    {
        infile = open(av[1], O_RDONLY);
		check_errors(infile, "Error opening infile");
        ft_dup2(infile, 0);
        ft_close(infile);
	    *outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	    check_errors(*outfile, "Error opening outfile");
    }
    return (i);
}
int main(int ac, char **av, char **envp)
{
    int i;
    int outfile;
    
    if(ac < 5)
    {
        perror("Invalid Arguments!.");
        exit(1);        
    }
    outfile = 0;    
    i = ft_open(av, ac, &outfile, 1);
    while(++i < ac - 1)
        ft_child(av[i], envp , (i + 1 == ac - 1), &outfile);
    int j = i - 2;
    while(j--)
        ft_wait();
    return (0);
}
