#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"

#define  MAXLINE  128

int sh( int argc, char **argv, char **envp )
{
  char *prompt = calloc(PROMPTMAX, sizeof(char));
  char *commandline = calloc(MAX_CANON, sizeof(char));
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  char **args = calloc(MAXARGS, sizeof(char*));
  int uid, i, status, argsct, go = 1;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;

  uid = getuid();
  password_entry = getpwuid(uid);               /* get passwd info */
  homedir = password_entry->pw_dir;		/* Home directory to start
						  out with*/
     
  if ( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL )
  {
    perror("getcwd");
    exit(2);
  }
  owd = calloc(strlen(pwd) + 1, sizeof(char));
  memcpy(owd, pwd, strlen(pwd));
  prompt[0] = ' '; prompt[1] = '\0';

  /* Put PATH into a linked list */
  pathlist = get_path();

  while ( go )
  {
        /* print your prompt*/
        printf("%s[%s]>", prompt, pwd);
        /* get command line and process */
        while(fgets(buf, MAXLINE, stdin) != NULL){
                if(buf[strlen(buf)-1]=='\n'){
                        buf[strlen(buf)-1]=0;
                }

                strcpy(commandline, buf);
                char *arr[6];
                int i=0;
                arr[i] = strtok(commandline, " ");
                while(arr[i]!=NULL){
                        arr[i++]=strtok(NULL," ");
                }




        if(fgets(buf, MAXLINE, stdin) == NULL){
                continue;
        }


        /* check for each built in command and implement */
        if (strcmp(commandline, "pwd") == 0) {   /* built-in command pwd */
               char *ptr = getcwd(NULL, 0);
               printf("CWD = [%s]\n", ptr);
               free(ptr);
             }
        else if (strcmp(commandline, "EXIT") == 0 || strcmp(commandline, "exit")) {   /* built-in command pwd */
               printf("EXITING PROGRAM");
               go=0;
             }
     /*  else  program to exec */
       /* find it */
       /* do fork(), execve() and waitpid() */

      /* else */
        /* fprintf(stderr, "%s: Command not found.\n", args[0]); */
    }
  }
  return 0;
}


char *which(char *command, struct pathelement *pathlist )
{
   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */

} /* which() */

char *where(char *command, struct pathelement *pathlist )
{
  /* similarly loop through finding all locations of command */
} /* where() */

void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */

