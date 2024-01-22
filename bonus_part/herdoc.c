#include <stdio.h>
#include <stdlib.h>      
#include <string.h>
#include <unistd.h>
#include "pipex.h"
#include <stdbool.h>



void ft_herdoc(char *av)
{
    char *s;
    char *p = ft_strjoin(av, "\n");
    if(!p)
        return ;
    while(1)
    {
        s = get_next_line(0);
        if(!s)
            return ;
        if(!strcmp(s, p))
            break;
        free(s);
    }
    free(p);
}

int main(int ac, char **av, char **envp)
{
    
    if(!strcmp(av[1], "here_doc"))
    {
        int hh = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND , 0644);
        if(hh == -1)
        {
            printf("Error open file : %s\n", av[ac - 1]);
            exit(EXIT_FAILURE);
        }

            
        
            int i =3;
            ft_herdoc(av[2]);
            dup2(hh, 1);

            while(i <= 5)
            {
                ft_child(av[i],envp,(i + 1 == ac -1), &hh);
                i++;
            }
            close(hh);
            while(i--)
            {
                wait(NULL);
            }   
    }
    return (0);
}