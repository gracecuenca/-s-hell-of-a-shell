#include "headers.h"

char *separate_commands(char *line){
  char *copy;
  strcpy(copy, line);
  int i;
  for(i = 0; copy; i++){
    char *fragment = strsep(&line, ";");
  }
  /*
    for(i = 0; line; i++){
    char *fragment = strsep(&line, ";");
    printf("%s\n", fragment);
    //args[i] = fragment;
    }
  */
  printf("%s\n%s\n", line, i);
  return copy;
}
