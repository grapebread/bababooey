#ifndef ARGS_H
#define ARGS_H

/* Takes in a string and character. Returns an
Integer based on the number of occurances of the
character in the string */
int count_x(char *str, char c);

/* Takes in a line of string. Parses them into multiple commands
based on the number of semicolons. Then further parses the commands
into arguments using parse_args (see below) */
char ***parse_multi(char *line);

/* Takes in a line of string and parses them into arguments.
Returns an array of strings which are the arguments */
char **parse_args(char *line);

#endif
