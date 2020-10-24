//clear screen
void prompt(){
    static int new_line = 1;
	char dir[RL_BUFFSIZE];

	if (new_line){
        const char *CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
        write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
        new_line = 0;
    }

    getcwd(dir, sizeof(dir)); //gets current directory
    printf("%s/", dir);
}

//read a line from user
char *rl_readline(){
	char c;
    int bufferSize = RL_BUFFSIZE;
    char *buffer = malloc(sizeof(char) * bufferSize);
    int position = 0;

    while (1){
        //read a character
        c = getchar();

        // if character is an end of line, replace it with a null and return
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }

        //increment position to access the next array element
        position++;

        // if next character will go outside current buffer size, reallocate
        if (position >= bufferSize)
        {
            bufferSize += RL_BUFFSIZE;
            buffer = realloc(buffer, bufferSize);
        }
    }
}

//parse input
char **parseInput(char *input){
    char **cmd = malloc(8 * sizeof(char *));
	int i = 0;
    char *parsed;  
  
	if(cmd == NULL){  //there is no input
        printf("Allocation failed\n"); 
        exit(1); //ERROR EXIT
    }
    parsed = strtok(input, " ");
    while (parsed != NULL){
        cmd[i] = parsed;
        i++;
        parsed = strtok(NULL, " ");
    }
    cmd[i] = NULL;
    return cmd;
}

//signal handler
void childSignalHandler(int signum){
    FILE *f;

    f = fopen("/home/user/Desktop/ChildProcess.log", "a+"); //WRITE THE PATH TO PRINT THE LOG FILE IN IT
	if (signum == SIGCHLD){
    	if (f == NULL)  printf("File couldn't be opened.");
    	fprintf(f, "CHILD PROCESS WAS TERMINATED.\n");
    	fclose(f);}
}