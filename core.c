#include "headers.h"

int num_separated(char *line, char *limit){
  int i;
  char *copy = malloc(sizeof(char*));
  char *point = copy;
  strcpy(copy, line);
  
  for(i = 0; copy; i++){
    strsep(&copy, limit);
  }
  //printf("%d\n", i);
  free(point);
  return i;
}

char **separate_commands(char *line){
  int i = num_separated(line, ";");
  char **commands = calloc(i, sizeof(char **));

  for(i = 0; line; i++){
    commands[i] = strsep(&line, ";");
  }
  
  return commands;
}

char **parse_args(char *line){
  int i = num_separated(line, " ");
  char **commands = calloc(i, sizeof(char **));

  for(i = 0; line; i++){
    commands[i] = strsep(&line, " ");
  }
  
  return commands;
}

int cd(char **args){
  if(!chdir(args[1])){
    return 0;
  }
  //printf("Error number: %d\n", errno);
  printf("%s\n",strerror(errno));
  return 1; //shows problematic, but keeps shell running hopefully
}
