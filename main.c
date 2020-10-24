#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#include "header.h"
 
int main(){
    char **cmd;
    char *input;
    int status;
	int isBG;
	
    while (1){
		isBG = 0; 

        prompt();					//clears screen
        input = rl_readline();		//read input
        cmd = parseInput(input);	//parse commands
		
		//if input = exit -> terminate program
		if(strcmp(cmd[0], "exit") == 0){ 
			break;
		}

		//change directory
		if(strcmp(cmd[0], "cd") == 0){
			if (chdir(cmd[1]) == -1){
               perror("An error occured\n"); 
        }
			//skipfork
			continue;
    	}
		
		//check if it is a background process
		if(cmd[1] && strcmp(cmd[1], "&")==0){
       		isBG = 1; 
       		cmd[1] = NULL;
    	}		
		
    	pid_t childPID = fork(); //create child process
		signal(SIGCHLD, childSignalHandler); //if child process terminates normally->returns SIGCHLD
    	if (childPID < 0){
			perror("An Error occured\n");
        	//terminate program
			exit(1);
    	 }else if (childPID == 0){
			//execute child process
			if (execvp(cmd[0], cmd) < 0){
            	perror("An error occured\n");
            	//only terminate child
            	exit(1);}
        	} else if (!isBG){
            	if(waitpid(childPID, &status, 0) > 0){
           			if(WIFEXITED(status) && !WEXITSTATUS(status))
            	   			printf("process executed normally\n");
           			else if(WIFEXITED(status) && WEXITSTATUS(status)){
            	    		if(WEXITSTATUS(status)==127)
								printf("execv failed\n");
            	    		else printf("program terminated normally but returned non-zero status\n");
            	    }
           			else printf("program didn't terminate normally\n");
           		}
      			else printf("waitpid() failed\n");
        	}
        free(input);
        free(cmd);
    }
    return 0;
}
