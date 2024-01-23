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
void ft_read_input(char **av, int *fd)
{
    char *s;
    char *p =ft_strjoin(av[2], "\n");
    if(!p)
        return ;
    size_t len_s;
    close(fd[0]);
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
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        ft_wait();
    }
        // ft_read(fd);
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
    }
    else
        ft_read(fd);
}
int  ft_open(char **av, int fd, int ac)
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
int main(int ac, char **av, char **envp)
{
    int i = 1;
    int infile;
    int outfile;

    if(ac < 5)
        exit(1);
    if(ft_strcmp(av[1], "here_doc") == 0)
    {
        if(ac < 6)
            exit(1);
        outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		check_errors(outfile, "Error opening outfile");
        if(outfile < 0)
            exit(1);
        ft_herdoc(av);
        // dup2(outfile, 1);
        i += 1;
    }
    else
    {
        infile = open(av[1], O_RDONLY);
		check_errors(infile, "Error opening infile");
        ft_dup2(infile, 0);
        ft_close(infile);
	    outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	    check_errors(outfile, "Error opening outfile");
    }


    while(++i < ac - 1)
        ft_child(av[i], envp , (i + 1 == ac - 1), &outfile);

    return (0);
}


//        1       2       6
// int	main(int ac, char **av, char **env)
// {
// 	int		i;
// 	int		fd_in;
// 	int		fd_out;

// 	if (ac < 5)
// 		exit_handler(1);
// 	if (ft_strcmp(av[1], "here_doc") == 0)
// 	{
// 		if (ac < 6)
// 			exit_handler(1);
// 		i = 3;
// 		fd_out = open_file(av[ac - 1], 2);
// 		here_doc(av);
// 	}
// 	else
// 	{
// 		i = 2;
// 		fd_in = open_file(av[1], 0);
// 		fd_out = open_file(av[ac - 1], 1);
// 		dup2(fd_in, 0);
// 	}
// 	while (i < ac - 2)
// 		do_pipe(av[i++], env);
// 	dup2(fd_out, 1);
// 	exec(av[ac - 2], env);
// }
