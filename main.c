#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

char **parse_args(char *line);
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

char **parse_args(char *line)
{
    int spaces = 0;
    char *c = line;
    while (*c)
    {
        if (*c == ' ')
            ++spaces;
        ++c;
    }

    char **args = malloc((spaces + 2) * sizeof(char *));
    char *l = malloc(strlen(line) * sizeof(char));
    strcpy(l, line);

    int i = 0;
    args[0] = 0;
    while (l)
    {
        args[i] = strsep(&l, " ");
        args[++i] = 0;
    }

    free(l);
    return args;
}

static void sighandler(int signo)
{
    if (signo == SIGINT)
        exit(0);
}