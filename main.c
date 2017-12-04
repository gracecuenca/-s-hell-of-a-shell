#include "headers.h"

static void sighandler(int signo){
  //user wants to exit
  if (signo == SIGINT){
    printf("\nlogout\n");
    exit(0);
  }
}

void run(char *line){
  //DEBUGG NEED TO CLEAN LATER
  //printf("%s\n", line);
  int l = strlen(line);
  if (l > 0 && line[l - 1] == '\n'){
    line[l - 1] = 0; //replaces new line with null
  }
  int size = num_separated(line, ";");
  char ** args = separate_commands(line, ";");
  int i;
  for(i = 0; i < size; i++){
    if(!command(args[i])){
      char ** arg = separate_commands(args[i], " ");
      execute(arg);
    }
  }
}

int main(){
  while (1) {
    signal(SIGINT, sighandler);
    path();
    char line [100];
    fgets(line, sizeof(line), stdin);
  
    run(line);
  }
  return 0;
}
