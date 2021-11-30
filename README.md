# Bababooey Shell
Made by Shuprovo Sikder and Geoffrey Lin

## Features
- Read and run commands with arguments
- Cd and exit within the shell
- Read multiple commands using semicolons
- Multiple redirection through >, <, and >> (Must have one space between each argument)
- Simple piping

## Bugs
- If you cd into a folder (x) and cd out of the parent folder (y) and you try to cd back into y it will cd into x.
    (might just be on my [Geoffrey] end)
- Sometimes cding fails. We have no clue why.
    (also might just be on Geoffrey's end)
- Piping and redirection still runs the end of the pipe (Ex: ls -a | cat > yes still prints out the cat and then redirects it into yes)
    
## Function Headers
```
int count_x(char *str, char c);
char ***parse_multi(char *line);
char **parse_args(char *line, char delimiter);
char *get_home();
char *get_working();
char *cd(char *working, char *path);
int redirection(char ** command);
```
