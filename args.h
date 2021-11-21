#ifndef ARGS_H
#define ARGS_H

int count_x(char *str, char c);
char ***parse_multi(char *line);
char **parse_args(char *line, char delimiter);

#endif