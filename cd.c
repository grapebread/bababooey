#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_home()
{
    char *home = "/home/";
    char *user = getlogin();
    char *start = malloc((strlen(home) + strlen(user)) * sizeof(char));
    strcpy(start, home);
    strcat(start, user);

    return start;
}

char *cd(char *working, char *path)
{
    char *home = get_home();
    int p_len = strlen(path);

    if (!strncmp(path, "~", 1))
    {
        int err = 0;

        if (p_len > 1)
        {
            if (!strcmp(path, "~/"))
                err = chdir(home);
            else
            {
                int h_len = strlen(home);

                char *temp = malloc(sizeof(char) * (p_len + h_len - 1));
                strncpy(temp, home, h_len);
                for (int i = 1; i < p_len; ++i)
                    temp[i + h_len - 1] = path[i];

                err = chdir(temp);

                if (err != 0)
                {
                    printf("The directory (%s) does not exist or there has been an error opening this directory.\n", path);
                    return working;
                }

                free(home);
                free(working);

                return temp;
            }
        }
        else
            err = chdir(home);

        if (err != 0)
        {
            printf("The directory (%s) does not exist or there has been an error opening this directory.\n", path);
            return working;
        }

        return home;
    }
    else if (!strncmp(path, "..", 2))
    {
        char *cwd = malloc(512 * sizeof(char)); // this is both wasteful and not enough
        getcwd(cwd, 512);

        if (!strcmp(cwd, "/"))
            return working;

        for (int i = strlen(cwd) - 1; i > 0; --i)
        {
            if (cwd[i - 1] == '/')
            {
                cwd[i] = '\0';
                break;
            }
        }

        chdir(cwd);

        return cwd;
    }
    else if (!strncmp(path, "/", 1))
    {
        int err = chdir(path);

        if (err != 0)
        {
            printf("The directory (%s) does not exist or there has been an error opening this directory.\n", path);
            return working;
        }

        return path;
    }
}