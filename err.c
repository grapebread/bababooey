#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* If there is an error (caught through errno), print the error and
return the current working directory, otherwise return the new directory. */
char *check_cd_err(char *working, char *path)
{
    if (errno != 0)
    {
        printf("%s\n", strerror(errno));
        return working;
    }
    else
    {
        free(working);
        return path;
    }
}