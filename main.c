#include "headers.h"

int main(){
  //INSTRUCTIONS, DONT ERASE UNTIL THE END
  /*
    - is important
    -> is subset
    --- is not needed, but will add flair
    --------------------------------------------------------------------
    -infinite loop so program never dies
    ->make it so only parent survives until the end
    ---print out the pwd and keep it so the newlining doesnt happen
    -make a for loop in the while loop to manage each command given
    ->might make it req. for ; to separate commands
    ->might also req. that everything is separated w/ spaces
    ->flags might need to be separated too
  */

  //QUICK TESTING
  char test[] = "ls -l ; echo hello";
  printf("commands being tested: %s\n", test);
  int size = num_separated(test, ";");
  printf("num commands: %d\n", size);
  char ** commands = separate_commands(test, ";");
  int i;
  for(i=0; i < size; i++){
    printf("command: %s\n", commands[i]);
    execvp(commands[i], commands);
  }

  char firstcmd[] = "grace > hi.txt";
  command(firstcmd);
  printf("MSG: Should be the end\n");

  char seccmd[] = "./a.out < hi.txt";
  command(seccmd);

  //char sec[] = "ls | wc";
  //command(sec);

  //trying to chain them together
  /*
    char line[]="ab;hello friend;hi;hey stranger";
    printf("%s\n", line);
    int size = num_separated(line, ";");
    char **command = separate_commands(line);
    int j;
    for(j = 0; j < size; j++){
    printf("%s\n", command[j]);
    int asdf = num_separated(command[j], " ");
    char **arg = separate_commands(command[j], " ");
    int afg;
    for(afg = 0; afg < asdf; afg++){
    printf("\t%s\n", arg[afg]);
    }
    }

  */

  //ACTUAL SHELL STARTS HERE!
  /*
    char line [100];
    while (1) {
    path();
    fgets(line, sizeof(line), stdin);
    //DEBUGG NEED TO CLEAN LATER
    printf("%s\n", line);
    int l = strlen (string);
    if (l > 0 && string [l - 1] == '\n'){
    string [l - 1] = '\0';
    }
    char ** args = separate_commands(line, ";");
    int i = 0;
    }
  */
  return 0;
}
