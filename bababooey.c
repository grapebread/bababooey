#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <dirent.h>

int count_space(char *line){
  int i = 0;
  while (*line){
    if (*line == ' '){
      i++;
    }
    line++;
  }
  return i;
}

char **parse_args(char *line){
  char **args = malloc(sizeof(char *) * (count_space(line) + 2));
  char **front = args;
  char *seg;
  seg = strsep(&line, " ");
  while (seg){
    *args = seg;
    args++;
    seg = strsep(&line, " ");
  }
  return front;
}

int main(){
	while(1){
		char line[100];
  	printf("Enter Action: \n");
  	fgets(line, sizeof(line) - 1, stdin);
		char **args = parse_args(line);
		int pid = fork();
		if (pid){
			int status;
			int child_pid = wait(&status);
			printf("Parent is done\n");
		}
		else{
			int i = execvp(args[0], args);
			return i;
		}
	}
}
