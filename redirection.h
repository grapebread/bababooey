#ifndef REDIRECT_H
#define REDIRECT_H

/* Takes in an array of strings and returns an integer.
The integer is the file descriptor. Depending if the person inputs
a >, <, or >>, it will redirect the stdout or stdin of the program
to the file given. */
int redirection(char ** command);

#endif
