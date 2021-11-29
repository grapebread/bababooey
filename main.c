#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#include "args.h"
#include "cd.h"
#include "redirection.h"

#define BUFFER_SIZE 512

static void sighandler(int signo);

void a()
{
    chdir("/");
}

int main(void)
{
    char *working = get_working();

    while (1)
    {
        signal(SIGINT, sighandler);

        char c[BUFFER_SIZE];
        printf("@ %s> ", working);
        fgets(c, BUFFER_SIZE, stdin);

        char *p;
        if ((p = strchr(c, '\n')) != NULL)
            *p = '\0';

        int n = count_x(c, ';') + 1;
        char ***commands = parse_multi(c);

        if (strcmp(commands[0][0], "exit") == 0)
        {
            exit(0);
        }

        for (int i = 0; i < n; ++i)
        {
            if (fork())
            {
                int status;
                int child_pid = wait(&status);
            }
            else
            {
                if (strcmp(commands[i][0], "cd") == 0)
                {
                    if (commands[i][1])
                        working = cd(working, commands[i][1]);
                    else{
                        working = cd(working, "~");
                      }
                    ++i;
                }

                if (i < n)
                {
                    int backup_stdout = dup(STDOUT_FILENO);
                    int backup_stdin = dup(STDIN_FILENO);
                    int j = redirection(commands[i]);
                    execvp(commands[i][0], commands[i]);
                    dup2(backup_stdout, STDOUT_FILENO);
                    dup2(backup_stdin, STDIN_FILENO);
                    printf("Command (%s) does not exist.\n", commands[i][0]);
                }
            }

            free(commands[i]);
        }

        free(commands);
    }

    free(working);
}

static void sighandler(int signo)
{
    if (signo == SIGINT)
        exit(0);
}
