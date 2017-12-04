# (s)hell-of-a-shell | Grace Cuenca & Khinshan Khan

## Features!
- Forks and execs commands
- Can separate multiple commands on a line
- Redirection with > and <
- Simple pipes | working
- Can see current working directory

## Attempted
- Attempted to tackle all cases of trailing spaces but it didn't work out
- Attempted to make `run()` and `main()` the only functions within main.c but got error with `sighandler()` when it wasn't in the same file as main.c
- Attempted multiple pipes but it would only execute the first one
- Attempted to make redirection of STDOUT end with ctrl + C, but that resulted in a forever loop of bad commands, and it went horribly wrong. We took this out completely...

## Bugs
- Entering `ls > hi.txt` doesn't execute `ls` because of the trailing " " after the ls. User must instead input `ls> hi.txt`. This is the case for `ls ` (with a space at the end) vs `ls` as well.
- Exiting using Ctrl + D is bad
- Piping limited to single pipes
- When using `cat> textfile`, send Ctrl + D for EOF instead of trying to use Ctrl + C, or else it terminates the whole application
- Sometimes created files have an extra space to them. You can still write to them without accounting for that, but can't remove them without accounting for it. This usually happens when you try to make two files of the same name in the same directory, when you hit space by accident, etc.

## Files & Function Headers
### main.c
The Driver
```
/*======== void sighandler() ==========
Inputs:  int signo
Returns: nothing
Handles signals and allows user to exit upon ctrl + C
=====================================*/

/*======== void run() ==========
Inputs:  char * line
Returns: nothing
Function that calls for parsing and executing
===============================*/

/*======== int main() ==========
Inputs:  nothing
Returns: the shell
Runs the stuffies in a forever while loop
===============================*/
```

### core.c
Contains all the functions that are to be executed (yikes @ multiple files)
```
/*======== int num_separated() ==========
Inputs:  char * line
         char * separator
Returns: Number of tokens separated by separator
Iterates through string using strsep
=======================================*/

/*======== char **separate_commands() ==========
Inputs:  char *line
         char *separator
Returns: An array of pointers filled with inputed commands
Separates input into commands separated by separator
===============================================*/

/*======== int cd() ==========
Inputs:  char **args
Returns: nothing
Utilizes chdir to switch between directories
===============================*/

/*======== int execute() ==========
Inputs:  char **args
Returns: nothing
Constantly checks inputs and utilizers execvp() to run commands
=================================*/

/*======== void redir() ==========
Inputs:  char ** file
         int destination
Returns: nothing
Utilizes dup and dup2 (file redirection in C to run redirection commands
================================*/

/*======== void pipin() ==========
Inputs:  char * first
         char * second
Returns: nothing
Utilizes popen() two open a pipe between first and second. fgets and fprint are then used to copy contents for first into second.
================================*/

/*======== char * trim() ==========
Inputs:  char * bush
Returns: A trimmed bush!
Eliminates the leading and trailing spaces of a string
==================================*/

/*======== int command() ==========
Inputs:  char * cmd
Returns: nothing
Function that executes redirection and piping by detecting presence of '<', '>', '|'
==================================*/

/*======== int path() ==========
Inputs:  nothing
Returns: nothing
Displays the user's cwd
==================================*/
```

### headers.h
Contains all `#include` and most function headers to allow for multiple files to work harmoniously 
