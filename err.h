#ifndef ERR_H
#define ERR_H

/* If there is an error (caught through errno), print the error and
return the current working directory, otherwise return the new directory. */
char *check_cd_err(char *working, char *path);

#endif