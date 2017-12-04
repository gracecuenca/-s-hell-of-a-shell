#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <signal.h>



int num_separated(char *line, char *limit);

char **separate_commands(char *line, char *separator);

int cd(char **args);

int execute(char **args);

void redir(char ** file, int destination);

void pipin(char * first, char * second);

char * trim(char * bush);

int command(char * cmd);

int path();

