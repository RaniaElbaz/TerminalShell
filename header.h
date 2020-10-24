#ifndef _HEADER_H_
#define _HEADER_H_

#define RL_BUFFSIZE 1024 //MAX SIZE OF INPUT

/*
	Description: to clear screen on every new line to take command
				 move the cursor to the upper left
				 print the current directory
*/
void prompt(void);

/*
	Description: to get the input from user
				 store it in buffer till it reaches a new line 
				 if the commands (input) exceed the maximum size (1024), buffer increases dynamically +1024

	Outputs:	buffer : array of charatcers pointers, store the input
*/
char *rl_readline(void);

/*
	Description: to parse the input taken from the user into command and its arguments
				 seperating input by spaces and stores it till the end of string (NULL)
				 then ends the array by setting last position to NULL.
				 if the input is NULL -> parsing fails.
		
	Input:  input: array of character pointers, holds the input taken from user

	Output: cmd : pointer to pointer array of characters, holds the parsed command
*/
char **parseInput(char *input);

/*
	Description: signal handler recieves a signal SIGCHLD when a child process is terminated
		         if SIGCHLD = "signum" means child process terminated normally then a log file is created
		         in its defined path and prints "CHILD PROCESS WAS TERMINATED".
	
	Input: 		signum: intger , number of the signal being controlled
	
*/
void childSignalHandler(int signum);

#endif /*_HEADER_H_*/