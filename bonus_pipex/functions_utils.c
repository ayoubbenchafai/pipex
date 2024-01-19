#include "pipex.h"
#include <stdio.h>

int ft_check(char *s, char c)
{
    if(!s)
        return (1);
    while(*s)
    {
        if(*s == c)
            return (1);
           s++; 
    }
    return (0);
}

char *ft_get_path(char **s)
{
    int i;
    char *cmd;
    
    if (!s)
        return (NULL);
    i = 0;
    cmd = "PATH";
    while(s[i] != NULL)
    {
        if(ft_check(cmd, *s[i]))
            return (s[i]);
        i++;
    }
    return (NULL);
}
//2 5 27
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
void ft_exceve(char *s, char **envp)
{
    // printf("hhh%s\n",s);
    // printf("%s\n",s);
    char *path_env = ft_get_path(envp);
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
        if(access(cmd, X_OK) == 0)
            break;
        else 
            free(cmd);
    }
    execve(cmd, cmdargs, envp);
        // perror("error TEST\n");
        // perror
    free(cmd);
    exit(EXIT_FAILURE);
}

