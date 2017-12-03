#include "headers.h"

static void sighandler(int signo){
  //user wants to exit
  if (signo == SIGINT){
    printf("exiting due to sigint :( cya later\n");
    exit(0);
  }
}

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
    printf("SC:%s\n", commands[i]);
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
    printf("/nlogout\n");
    sleep(1);
    exit(0);
  }
  if(!strcmp(args[0], "cd")){
    return cd(args);
  }
  int status;
  int f = fork();
  if(!f){
    execvp(args[0], args);
  }
  else{
    wait(&status);
  }
  return 1;
}

void redir(char ** file, int destination){
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
}

void pipin(char * first, char * second){
  FILE * fp1 = popen(first, "r");
  FILE * fp2 = popen(second, "w");
  //char path[1000];
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
void command(char * cmd){
  char *c = ">";
  if(strchr(cmd, *c) != NULL){
    printf("MSG: If for > is being run\n");
    char **cmds = separate_commands(cmd,">");
    cmds[1] = trim(cmds[1]);
    int i = 0;
    for(; i < 2; i++){
      printf("%s\n", cmds[i]);
    }
    redir(cmds, STDOUT_FILENO);
  }

  c = "<";
  if(strchr(cmd, *c) != NULL){
    printf("MSG: If for < is being run\n");
    char **cmds = separate_commands(cmd, "<");
    int i = 0;
    for(; i < 2; i++){
      printf("%s\n", cmds[i]);
    }
    redir(cmds, STDIN_FILENO);
  }
  /*c = "|"
    if(strchr(cmd, *p) != NULL){
    char **cmds = separate_commands(cmd, " | ");
    printf("commands: %s\t%s\t%s\n", cmd[0], cmd[1], cmd[2]);
    }*/
  //ADD REST OF RUNNNING COMMAND OPTIONS
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
