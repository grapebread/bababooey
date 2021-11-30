#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Takes in a string and character. Returns an
Integer based on the number of occurances of the
character in the string */
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

/* Takes in a line of string. Parses them into multiple commands
based on the number of semicolons. Then further parses the commands
into arguments using parse_args (see below) */
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

/* Takes in a line of string and parses them into arguments.
Returns an array of strings which are the arguments */
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