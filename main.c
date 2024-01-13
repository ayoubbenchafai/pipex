#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    int pipefd[2];
    pid_t pid;
    char buffer[20];

    //pipefd[0] ==> lecture   ==> read
    //pipefd[1] ==> écriture  ==> write


    // Création du pipe  
    if(pipe(pipefd) == -1)
    {
        perror("Erreur lors de la création du pipe");
        exit(1);// exit(EXIT_FAILURE);
    }

    // Création d'un processus enfant
    pid = fork();

    if(pid < 0)
    {
        perror("Erreur lors de la création du processus enfant");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        // Processus enfant
        close(pipefd[1]);  // Fermeture de l'extrémité d'écriture du pipe

        // Lecture des données du pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Processus enfant - Message reçu : %s\n", buffer);
        close(pipefd[0]);  // Fermeture de l'extrémité de lecture du pipe
    }
    else
    {
        // Processus parent
        close(pipefd[0]);  // Fermeture de l'extrémité de lecture du pipe

        // Écriture des données dans le pipe
        char message[] = "Bonjour, monde!";
        write(pipefd[1], message, sizeof(message));

        close(pipefd[1]);  // Fermeture de l'extrémité d'écriture du pipe
    }

    return (0);
}
