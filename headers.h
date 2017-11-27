#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int num_separated(char *line, char *limit);
char **separate_commands(char *line);
char **parse_args(char *line);
