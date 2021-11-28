#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 512

char *get_home()
{
    char *home = "/home/";
    char *user = getlogin();
    char *start = malloc((strlen(home) + strlen(user)) * sizeof(char));
    strcpy(start, home);
    strcat(start, user);

    return start;
}

char *get_working()
{
    char *cwd = malloc(BUFF_SIZE * sizeof(char)); // this is both wasteful and not enough
    getcwd(cwd, BUFF_SIZE);

    return cwd;
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

        err = chdir(home);

        free(path);
        if (err != 0)
        {
            printf("The directory (%s) does not exist or there has been an error opening this directory.\n", path);
            return working;
        }

        return home;
    }
    else if (!strncmp(path, "..", 2))
    {
        char *cwd = get_working();
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

        free(home);
        free(working);

        int err = chdir(cwd);
        if (err != 0)
        {
            printf("The directory (%s) does not exist or there has been an error opening this directory.\n", path);
            return working;
        }

        return cwd;
    }
    else if (!strncmp(path, "/", 1))
    {
        free(home);
        int err = chdir(path);

        if (err != 0)
        {
            printf("The directory (%s) does not exist or there has been an error opening this directory.\n", path);
            return working;
        }

        return path;
    }
    else
    {
        int h_len = strlen(home);
        char *temp = malloc((h_len + p_len + 1) * sizeof(char));
        strncpy(temp, home, h_len);
        temp[h_len] = '/';
        for (int i = 0; i < p_len; ++i)
            temp[h_len + i + 1] = path[i];

        free(home);
        free(path);

        int err = chdir(temp);

        if (err != 0)
        {
            printf("The directory (%s) does not exist or there has been an error opening this directory.\n", path);
            return working;
        }

        free(working);

        return temp;
    }
}