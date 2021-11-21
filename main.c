#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#include "args.h"

static void sighandler(int signo);

int main(void)
{
    char *user = getlogin();

    while (1)
    {
        signal(SIGINT, sighandler);

        char c[256];
        printf("%s>", user);
        fgets(c, 256, stdin);

        char *p;
        if ((p = strchr(c, '\n')) != NULL)
            *p = '\0';

        int n = count_x(c, ';') + 1;
        char ***commands = parse_multi(c);

        for (int i = 0; i < n; ++i)
        {
            if (fork())
            {
                int status;
                int child_pid = wait(&status);
            }
            else
            {
                execvp(commands[i][0], commands[i]);
                printf("Command (%s) does not exist.\n", commands[i][0]);
            }

            free(commands[i]);
        }

        free(commands);
    }
}

static void sighandler(int signo)
{
    if (signo == SIGINT)
        exit(0);
}