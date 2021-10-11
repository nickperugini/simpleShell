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

#define MAXLINE 128

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
  char buf[MAXLINE];
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
  //pathlist = get_path();

  while ( go )
  {
	pathlist=get_path();
        /* print your prompt*/
        printf("%s[%s]>", prompt, pwd);
        /* get command line and process */
	if(fgets(buf, MAXLINE, stdin) != NULL){
		/*printf("^D\n");
      		free(pathlist->element);
      		listFree(pathlist);
    	}
    	else if((strcmp(buf, "\n") == 0)){ //Enter Key command
      		(free(pathlist->element);
      		listFree(pathlist);
      		free(buf);
      		continue;
    		}
    	else{	*/
		if(buf[strlen(buf)-1]=='\n'){
                        buf[strlen(buf)-1]=0;
                }
		
                strcpy(commandline, buf);
                char *arr[6];
                int i=0;
                arr[i] = strtok(commandline, " ");
                int arrctr=0;	
		while(arr[i]!=NULL){
                        arr[++i]=strtok(NULL," ");
			arrctr++;
                }
		/*
      		arg[(strlen(arg))-1]=0;
      		args = stringToArray(arg);
      		i=0;
      		int argsctr=0;
      		//char *tmp;
      		//tmp = &args[0][0];
      		while(args[i]!=NULL){
        		argsctr++;
        		i++;
      		}*/


        /*if(buf) == NULL){
                continue;
        }*/


        /* check for each built in command and implement */
        if (strcmp(arr[0], "pwd") == 0) {   /* built-in command pwd */
              	printf("check");
		char *ptr = getcwd(NULL, 0);
               printf("[%s]\n", ptr);
               free(ptr);
             }
        else if (strcmp(arr[0], "exit")==0) {   /* built-in command pwd */
               	printf("EXITING PROGRAM");
               	go=0;
             }
	else if (strcmp(commandline, "prompt")==0) {
		if(arrctr >= 3){
			printf("Too many arguments given\n");
			} 
		else if(arr[1] == NULL){
			printf("input prompt prefix: ");
			if(!fgets(prompt + 1, MAXARGS, stdin)){
				printf("input error\n");
			}
			else if(prompt[strlen(prompt)-1] == '\n'){
				prompt[strlen(prompt)-1] = 0;
			}	
		}
		else{
			sprintf(prompt, " %s", arr[1]); 
		}
	}
		
	else if (strcmp(arr[0], "which") == 0){
          if (arrctr == 1){
            fprintf(stderr, "Not enough args\n");
          }
          else{
            int i = 1;
            while (i < arrctr+1 && i < MAXARGS){
              char *cmd = which(arr[i], pathlist);
              printf("%s", cmd);
              i++;
              free(cmd);
            }
          }
        }

	else if(strcmp(arr[0], "list") ==0)
	{
		if(arrctr==1){
			listPrint(pwd);
		}
		else{
			int counter=1; 	//starts at 1 since first arr[0] is list command
			while(counter<arrctr && counter<5) //capping amount of directories that can be listed at 5
				listPrint(arr[counter]);
 				printf("\n");
				counter++;
		}
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
   char *cmd = malloc(64);
  int found = 0; 

  while (pathlist) {
    sprintf(cmd, "%s/%s", pathlist->element, command);
    if (access(cmd, X_OK) == 0) {
      sprintf(cmd, "%s/%s\n", pathlist->element, command);
      found = 1;
      break;
    }
    pathlist = pathlist->next;
  }

  if (found == 0){
    sprintf(cmd, "%s: not found.\n", command);
    return cmd;
  }
  return cmd;

} /* which() */

char *where(char *command, struct pathelement *pathlist )
{
  /* similarly loop through finding all locations of command */
} /* where() */

void listPrint(char *d)
{
	DIR *curdir;
	struct dirent *f;
	if((curdir=opendir(d))==NULL){
		printf("%s does not exist", d); 
	}
	else{
		printf("%s", d);
		while((f = readdir(curdir))!=NULL){
			printf("%s\n", f->d_name);
		}
		printf("\n");
		free(f);
	}
	free(curdir);
}
/*void listFree(struct pathelement *head){
	struct pathelement* tmp = NULL;
	while(head!=NULL){
		tmp=head;
		head=head->next;
		free(tmp);
}
}*/
