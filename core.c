#include "headers.h"

int num_separated(char *line, char *separator){
  int i;
  char *copy = malloc(sizeof(char*) * strlen(line));
  strcpy(copy, line);
  for(i = 0; copy; i++){
    strsep(&copy, separator);
  }
  return i;
}

char **separate_commands(char *line, char *separator){
  int i = num_separated(line, separator);
  char **commands = calloc(i+1, sizeof(char **));
  for(i = 0; line; i++){
    commands[i] = strsep(&line, separator);
    commands[i] = trim(commands[i]);
    //printf("SC:%s\n", commands[i]);
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

//NEEDS EXECSSIVE TESTING
int execute(char **args){
  if(!strcmp(args[0],"exit")){
    printf("\nlogout\n");
    sleep(1);
    exit(0);
  }
  if(!strcmp(args[0], "cd")){
    return cd(args);
  }
  int status;
  int f = fork();
  if(!f){
    if(execvp(args[0], args) == -1){
      printf("%s: command not found\n", args[0]);
    }
    exit(0);
  }
  else{
    wait(&status);
  }
  return 1;
}

void redir(char ** file, int destination){
  /*
    if(destination == STDOUT_FILENO){
    int new_fd = open(file[1], O_RDWR | O_CREAT, 0666);
    int x = dup(destination);
    dup2(new_fd, destination);
    printf("%s\n", file[0]);
    dup2(x, destination);
    close(new_fd);
    }
    if(destination == STDIN_FILENO){
    //im tired, stuff ought to work with scanf, us it properly though
    int new_fd = open(file[1], O_RDWR | O_CREAT, 0666);
    int x = dup(destination);
    dup2(new_fd, destination);
    scanf("%s\n", file[0]);
    dup2(x, destination);
    close(new_fd);
    }
  */
  int new_fd = open(file[1], O_RDWR | O_CREAT, 0666);
  int x = dup(destination);
  dup2(new_fd, destination);
  run(file[0]);
  dup2(x, destination);
  close(new_fd);

}

void pipin(char * first, char * second){
  FILE * fp1 = popen(first, "r");
  FILE * fp2 = popen(second, "w");
  char path[1000];
  while(fgets(path, sizeof(path), fp1)){
    fprintf(fp2, "%s", path);
  }
  pclose(fp1);
  pclose(fp2);
}

//trimming trailing is causing too many bugs
char * trim(char * bush){
  int i = 0;
  if(bush[i] == ' '){
    while(bush[i] == ' '){
      i++;
    }
    //printf("MSG: TRIMMING DONE\n");
  }
  return &bush[i];
}

//started func to run single command, must come back to edit
int command(char * cmd){
  char *c = ">";
  if(strchr(cmd, *c) != NULL){
    printf("MSG: If for > is being run\n");
    char **cmds = separate_commands(cmd,">");
    cmds[1] = trim(cmds[1]);
    redir(cmds, STDOUT_FILENO);
    return 1;
  }

  c = "<";
  if(strchr(cmd, *c) != NULL){
    printf("MSG: If for < is being run\n");
    char **cmds = separate_commands(cmd, "<");
    redir(cmds, STDIN_FILENO);
    return 1;
  }
  c = "|";
  if(strchr(cmd, *c) != NULL){
    char **cmds = separate_commands(cmd, "|");
    pipin(cmds[0], cmds[1]);
    return 1;
  }
  return 0;
}

int path(){
  int status;
  int f = fork();
  if(!f){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL){
      printf("%s$ ", cwd);
    }
    else {
      perror("Technical Difficulties with Path");
    }
    exit(0);
  }
  else{
    wait(&status);
  }
  return 0;
}
