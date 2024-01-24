#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	s_length;

	i = 0;
	if (s == NULL)
		return (NULL);
	s_length = ft_strlen(s);
	if (start >= s_length)
		return (ft_strdup(""));
	if (len > (s_length - start))
		len = s_length - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}

static int	nbr_strings(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			len++;
		while (*s && *s != c)
			s++;
	}
	return (len);
}

static void	free_memory(char **ptr, int j)
{
	while (j)
	{
		j--;
		free(ptr[j]);
	}
	free(ptr);
}

static char	**ft_allocate_words(char const *s, char c, int size, int j)
{
	int		i;
	char	**ptr;

	ptr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ptr)
		return (0);
	while (j < size)
	{
		while (*s != '\0' && *s == c)
			s++;
		i = 0;
		while (s[i] != '\0' && s[i] != c)
			i++;
		ptr[j] = ft_substr(s, 0, i);
		if (!ptr[j])
		{
			free_memory(ptr, j);
			return (0);
		}
		s += i;
		j++;
	}
	ptr[j] = (0);
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	int		size;
	char	**ptr;

	if (!s)
		return (0);
	size = nbr_strings(s, c);
	j = 0;
	ptr = ft_allocate_words(s, c, size, j);
	return (ptr);
}

// void ft_exceve(char *av[], char *envp[])
// {
//     char **pathname;
//     char **cmdargs;
//     char *cmd;
//     int i;
    
//     pathname = ft_split(envp[4], ':');
//     if(!pathname)
//         exit(EXIT_FAILURE);
//     ///bin/ls
//     cmdargs = ft_split(av[1], ' ');
//     if(!cmdargs)
//         exit(EXIT_FAILURE);
//     i = 0;
//     while(pathname[i++])
//     {
//         cmd = ft_strjoin(pathname[i], "/");
//         cmd = ft_strjoin(cmd, cmdargs[0]);
//         if(!cmd)
//         {
//             free(pathname);
//             free(cmdargs);
//             exit(EXIT_FAILURE);
//         }
//         execve(cmd, cmdargs, envp);
//         // printf("TEST\n");
//         // perror
//         free(cmd);
//     }
//     exit(EXIT_FAILURE);
// }
void ft_exceve(char *s)
{
    char *path_env = ft_get_path(environ);
    char **cmdargs;
    char **pathname;
    char *cmd;
    int i;
    
    pathname = ft_split(path_env, ':');
    if(!pathname)
        exit(EXIT_FAILURE);
    
    ///bin/ls
    // cmdargs == "ls -la"
    cmdargs = ft_split(s, ' ');
    if(!cmdargs)
        exit(EXIT_FAILURE);
    fprintf(stderr,"%s", cmdargs[1]);
    i = 0;
    while(pathname[i++])
    {
        if(cmdargs[0][0] == '/' /*|| (cmdargs[0][0] == '.' && cmdargs[0][1] == '/')*/)
            cmd = ft_strjoin(pathname[i], cmdargs[0]);
        else
        {
            cmd = ft_strjoin(pathname[i], "/");
            cmd = ft_strjoin(cmd, cmdargs[0]);
        }
        if(!cmd)
        {
            free(pathname);
            free(cmdargs);
            exit(EXIT_FAILURE);
        }
        if(access(cmd, F_OK | X_OK) == 0) 
            break;
        else 
            free(cmd);
    }
    execve(cmd, cmdargs, NULL);
        printf("error TEST\n");
        // perror
    free(cmd);
    exit(EXIT_FAILURE);
}

// "ls '-l''a'"