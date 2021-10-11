#include "get_path.h"

int pid;
int sh( int argc, char **argv, char **envp);
char *which(char *command, struct pathelement *pathlist);
char *where(char *command, struct pathelement *pathlist);
void listPrint( char *d );
void printenv(char **envp);
void listFree(struct pathelement *head);
#define PROMPTMAX 32
#define MAXARGS 10
