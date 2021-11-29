#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

int redirection(char ** command){
  char * dest;
  int fd1;
  int i = -1;
  int test;
  while (*command){
    if (!strcmp(*command, ">")){
      *command = NULL;
      command++;
      dest = *command;
      fd1 = open(dest, O_WRONLY | O_TRUNC | O_CREAT, 0644);
      test = dup2(fd1, STDOUT_FILENO);
      i = 0;
    }
    if (!strcmp(*command, "<")){
      *command = NULL;
      command++;
      dest = *command;
      fd1 = open(dest, O_RDONLY, 0);
      if (fd1 == -1){
        printf("%s\n", strerror(errno));
        exit(0);
      }
      test = dup2(fd1, STDIN_FILENO);
      i = 1;
    }
    if (!strcmp(*command, ">>")){
      *command = NULL;
      command++;
      dest = *command;
      fd1 = open(dest, O_WRONLY | O_APPEND | O_CREAT, 0644);
      test = dup2(fd1, STDOUT_FILENO);
      i = 0;
    }
    command++;
  }
  return i;
}
