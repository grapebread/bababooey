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
  int test;
  char **front = command;
  while (*command){
    if (!strcmp(*command, ">")){
      *command = NULL;
      command++;
      dest = *command;
      fd1 = open(dest, O_WRONLY | O_TRUNC | O_CREAT, 0644);
      test = dup2(fd1, STDOUT_FILENO);
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
    }
    if (!strcmp(*command, ">>")){
      *command = NULL;
      command++;
      dest = *command;
      fd1 = open(dest, O_WRONLY | O_APPEND | O_CREAT, 0644);
      test = dup2(fd1, STDOUT_FILENO);
    }
    if (!strcmp(*command, "|")){
      char buff[500];
      *command = NULL;
      command++;
      dest = *command;
      FILE * output = popen(*command, "w");
    }
    command++;
  }
  return fd1;
}
