#include "headers.h"

int main(){
  /*
    - is important
    -> is subset
    --- is not needed, but will add flair
  */

  /*
    -infinite loop so program never dies
    ->make it so only parent survives until the end
    ---print out the pwd and keep it so the newlining doesnt happen
    -make a for loop in the while loop to manage each command given
    ->might make it req. for ; to separate commands
    ->might also req. that everything is separated w/ spaces
    ->flags might need to be separated too
  */
  //char line[]="ab;hello friend;hi;hey stranger";
  char test[] = "ls -l ;echo hello";
  printf("commands being tested: %s\n", test);
  int size = num_separated(test, ";");
  printf("num commands: %d\n", size);
  char ** commands = separate_commands(test, ";");
  int i;
  for(i=0; i < size; i++){
    printf("command: %s\n", commands[i]);
    execvp(commands[i], commands);
  }

  /*
  printf("%s\n", line);
  int size = num_separated(line, ";");
  char **command = separate_commands(line);
  int j;
  for(j = 0; j < size; j++){
    printf("%s\n", command[j]);
    int asdf = num_separated(command[j], " ");
    char **arg = parse_args(command[j]);
    int afg;
    for(afg = 0; afg < asdf; afg++){
      printf("\t%s\n", arg[afg]);
    }
  }
  */
  char firstcmd[] = "hi > hi.txt";
  command(firstcmd);

  return 0;
}
