#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

/* Takes in an array of strings and returns an integer.
The integer is the file descriptor. Depending if the person inputs
a >, <, or >>, it will redirect the stdout or stdin of the program
to the file given. If the person inputs a |, then the stdout for the
first program will be written to the stdin of the second program. */
int redirection(char **command)
{
  char *dest;
  int fd1 = -1;
  int test;
  char **front = command;
  while (*command)
  {
    if (!strcmp(*command, ">"))
    {
      *command = NULL;
      command++;
      dest = *command;
      fd1 = open(dest, O_WRONLY | O_TRUNC | O_CREAT, 0644);
      test = dup2(fd1, STDOUT_FILENO);
    }
    if (!strcmp(*command, "<"))
    {
      *command = NULL;
      command++;
      dest = *command;
      fd1 = open(dest, O_RDONLY, 0);
      if (fd1 == -1)
      {
        printf("%s\n", strerror(errno));
        exit(0);
      }
      test = dup2(fd1, STDIN_FILENO);
    }
    if (!strcmp(*command, ">>"))
    {
      *command = NULL;
      command++;
      dest = *command;
      fd1 = open(dest, O_WRONLY | O_APPEND | O_CREAT, 0644);
      test = dup2(fd1, STDOUT_FILENO);
    }
    if (!strcmp(*command, "|"))
    {
      *command = NULL;
      command++;
      char str[1000];
      char **start = front;
      while (*start)
      {
        strcat(str, *start);
        strcat(str, " ");
        start++;
      }
      FILE *test = popen(str, "r");
      FILE *test2 = popen(*command, "w");
      char buffer[512];
      while (fgets(buffer, 512, test))
      {
        fputs(buffer, test2);
      }
      *front = NULL;
      pclose(test);
      pclose(test2);
    }
    command++;
  }
  return fd1;
}
