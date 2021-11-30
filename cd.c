#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>

#include "err.h"

#define BUFF_SIZE 512

/* Uses the current user's username to create a string which leads
to their home directory. */
char *get_home()
{
    char *home = "/home/";
    struct passwd *pwd = getpwuid(getuid());
    char *user = pwd->pw_name;
    char *start = malloc((strlen(home) + strlen(user)) * sizeof(char));
    strcpy(start, home);
    strcat(start, user);

    return start;
}

/* Get the current working directory (i.e. where the program executable
is located) using getcwd() in <unistd.h> */
char *get_working()
{
    char *cwd = malloc(BUFF_SIZE * sizeof(char)); // this is both wasteful and not enough
    getcwd(cwd, BUFF_SIZE);

    return cwd;
}

/* Check for specific prefixes in the arguments (path variable) and
set and return the current directory to the correct path or just return
the current working directory if there's any issues. */
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

                free(home);

                return check_cd_err(working, temp);
            }
        }

        err = chdir(home);
        return check_cd_err(working, home);
    }
    else if (!strncmp(path, "..", 2))
    {
        if (!strcmp(path, ".."))
        {
            char *cwd = get_working();
            if (!strcmp(cwd, "/"))
                return working;

            for (int i = strlen(cwd) - 1; i > 0; --i)
            {
                if (cwd[i] == '/')
                {
                    cwd[i] = '\0';
                    break;
                }
            }

            free(home);

            int err = chdir(cwd);
            return check_cd_err(working, cwd);
        }
        else
        {
            char *cwd = get_working();
            int w_len = strlen(cwd);
            char *temp = malloc((w_len + p_len - 2) * sizeof(char));
            strcpy(temp, cwd);
            free(cwd);

            int slash;
            for (int i = w_len - 1; i > 0; --i)
            {
                if (cwd[i] == '/')
                {
                    slash = i;
                    break;
                }
            }

            int final;
            for (int i = 2; i < p_len; ++i)
            {
                temp[slash + i - 2] = path[i];
                final = slash + i - 2;
            }
            temp[final + 1] = '\0';

            int err = chdir(temp);
            return check_cd_err(working, temp);
        }
    }
    else if (!strncmp(path, "/", 1))
    {
    	printf("here\n");
        int err = chdir(path);
        printf("err: %d\n", errno);

        return check_cd_err(working, path);
    }
    else if (!strncmp(path, ".", 1))
    {
        if (!strncmp(path, "./", 2))
        {
            char *cwd = get_working();
            int c_len = strlen(cwd);
            char *temp = malloc((c_len + p_len - 1) * sizeof(char));
            strcpy(temp, cwd);
            free(cwd);

            for (int i = 1; i < p_len; ++i)
                temp[c_len + i - 1] = path[i];

            int err = chdir(temp);
            return check_cd_err(working, temp);
        }

        return working;
    }
    else
    {
    	if (!strcmp(working, "/"))
    	{
    		char *temp = malloc((p_len + 1) * sizeof(char));
    		temp[0] = '/';
    		for (int i = 0; i < p_len; ++i)
    			temp[i + 1] = path[i];
    		
    		int err = chdir(temp);
    		char *t = check_cd_err(working, temp);
    		free(working);
    		return t;
    	}
    	else
    	{
			int w_len = strlen(working);
			char *temp = malloc((w_len + p_len + 1) * sizeof(char));
			strncpy(temp, working, w_len);
			temp[w_len] = '/';
			for (int i = 0; i < p_len; ++i)
				temp[w_len + i + 1] = path[i];

			free(home);

			int err = chdir(temp);
			return check_cd_err(working, temp);
		}
    }
}
