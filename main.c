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

        char **args = parse_args(c);

        if (fork())
        {
            int status;
            int child_pid = wait(&status);
        }
        else
        {
            int i = execvp(args[0], args);
            return i;
        }
    }
}

static void sighandler(int signo)
{
    if (signo == SIGINT)
        exit(0);
}