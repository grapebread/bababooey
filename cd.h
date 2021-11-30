#ifndef CD_H
#define CD_H

/* Uses the current user's username to create a string which leads
to their home directory. */
char *get_home();

/* Get the current working directory (i.e. where the program executable
is located) using getcwd() in <unistd.h> */
char *get_working();

/* Check for specific prefixes in the arguments (path variable) and
set and return the current directory to the correct path or just return
the current working directory if there's any issues. */
char *cd(char *working, char *path);

#endif