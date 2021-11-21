#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int count_x(char *str, char c)
{
    int x = 0;
    while (*str)
    {
        if (*str == c)
        {
            ++x;
        }
        ++str;
    }

    return x;
}

char **parse_args(char *line)
{
    int n = count_x(line, ' ');

    char **args = malloc((n + 1) * sizeof(char *));
    char *l = malloc(strlen(line) * sizeof(char));
    strcpy(l, line);

    int i = 0;
    args[0] = 0;
    while (l)
    {
        char *s = strsep(&l, " ");
        if (*s != 0)
        {
            args[i] = s;
            args[++i] = 0;
        }
    }

    free(l);
    return args;
}

char ***parse_multi(char *line)
{
    int n = count_x(line, ';');

    char ***commands = malloc((n + 1) * sizeof(char **));
    char *l = malloc(strlen(line) * sizeof(char));
    strcpy(l, line);

    int i = 0;
    commands[0] = 0;
    while (l)
    {
        char *s = strsep(&l, ";");
        if (*s != 0)
        {
            char **args = parse_args(s);
            commands[i] = args;
            commands[++i] = 0;
        }
    }

    return commands;
}