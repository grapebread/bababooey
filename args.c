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

char **parse_args(char *line, char delimiter)
{
    int n = count_x(line, delimiter);

    char **args = malloc((n + 2) * sizeof(char *));
    char *l = malloc(strlen(line) * sizeof(char));
    strcpy(l, line);

    int i = 0;
    args[0] = 0;
    while (l)
    {
        char *s = strsep(&l, &delimiter);
        if (*s != 0)
        {
            args[i] = s;
            args[++i] = 0;
        }
    }

    free(l);
    return args;
}