#include "headers.h"

/*======== int num_separated() ==========
Inputs:  char * line
         char * separator
Returns: Number of tokens separated by separator
Iterates through string using strsep
=======================================*/
int num_separated(char *line, char *separator){
  int i;
  char *copy = malloc(sizeof(char*) * strlen(line));
  strcpy(copy, line);
  for(i = 0; copy; i++){
    strsep(&copy, separator);
  }
  return i;
}

/*======== char **separate_commands() ==========
Inputs:  char *line
         char *separator
Returns: An array of pointers filled with inputed commands
Separates input into commands separated by separator
===============================================*/
char **separate_commands(char *line, char *separator){
  int i = num_separated(line, separator);
  char **commands = calloc(i+1, sizeof(char **));
  for(i = 0; line; i++){
    commands[i] = strsep(&line, separator);
    commands[i] = trim(commands[i]);
  }
  return commands;
}

/*======== int cd() ==========
Inputs:  char **args
Returns: nothing
Utilizes chdir to switch between directories
===============================*/
int cd(char **args){
  if(!chdir(args[1])){
    return 0;
  }
  printf("%s\n",strerror(errno));
  return 1; //shows problematic, but keeps shell running hopefully
}

/*======== int execute() ==========
Inputs:  char **args
Returns: nothing
Constantly chekcs inputs and utilizers execvp() to run commands
=================================*/
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

/*======== void redir() ==========
Inputs:  char ** file
         int destination
Returns: nothing
Utilizes dup and dup2 (file redirection in C to run redirection commands
================================*/
void redir(char ** file, int destination){
  int new_fd = open(file[1], O_RDWR | O_CREAT, 0666);
  int x = dup(destination);
  dup2(new_fd, destination);
  run(file[0]);
  dup2(x, destination);
  close(new_fd);

}

/*======== void pipin() ==========
Inputs:  char * first
         char * second
Returns: nothing
Utilizes popen() two open a pipe between first and second. fgets and fprint are then used to copy contents for first into second.
================================*/
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

/*======== char * trim() ==========
Inputs:  char * bush
Returns: A trimmed bush!
Eliminates the leading and trailing spaces of a string
==================================*/
char * trim(char * bush){
  int i = 0;
  if(bush[i] == ' '){
    while(bush[i] == ' '){
      i++;
    }
  }
  return &bush[i];
}

/*======== int command() ==========
Inputs:  char * cmd
Returns: nothing
Function that executes redirection and piping by detecting presence of '<', '>', '|'
==================================*/
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

/*======== int path() ==========
Inputs:  nothing
Returns: nothing
Displays the user's cwd
==================================*/
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
