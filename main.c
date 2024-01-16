#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pipex.h"
// 2   5   24
int main() {
    int pipefd[2];
    pid_t ls_pid, wc_pid;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork the first child process to execute "ls -la"
    ls_pid = fork();
    if (ls_pid == -1) {
        perror("fork");
        return 1;
    } else if (ls_pid == 0) {
        // Child process: ls -la
        close(pipefd[0]); // Close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe write end
        close(pipefd[1]); // Close the pipe write end

        // Execute ls -la
        char *ls_args[] = { "ls", "-la", NULL };
        execve("/bin/ls", ls_args, NULL);
        perror("execve ls");
        return 1;
    }

    // Fork the second child process to execute "wc -l"
    wc_pid = fork();
    if (wc_pid == -1) {
        perror("fork");
        return 1;
    } else if (wc_pid == 0) {
        // Child process: wc -l
        close(pipefd[1]); // Close the write end of the pipe
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the pipe read end
        close(pipefd[0]); // Close the pipe read end

        // Execute wc -l
        char *wc_args[] = { "wc", "-l", NULL };
        execve("/usr/bin/wc", wc_args, NULL);
        perror("execve wc");  
        return 1;
    }

    // Parent process
    close(pipefd[0]); // Close the read end of the pipe
    close(pipefd[1]); // Close the write end of the pipe

    // Wait for both child processes to complete
    waitpid(ls_pid, NULL, 0);
    waitpid(wc_pid, NULL, 0);

    return 0;
}