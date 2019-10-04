#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h> 

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char *token;

int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];

    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    
    while (true) {
        // Print the shell prompt.
        printf("%s", prompt);
        fflush(stdout);
        
        // Read input from stdin and store it in command_line. If there's an
        // error, exit immediately. (If you want to learn more about this line,
        // you can Google "man fgets")
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
        
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

       //Tokenize the command line input (split it on whitespace)
        
        int i = 0;
        token = strtok(command_line, delimiters);
        while (token != NULL)
        {
           arguments[i] = token;
           token = strtok(NULL, delimiters);
        }
      
        //Create a child process which will execute the command line input 
        //and the parent process should wait for the child to complete.
        
        pid_t pid = fork();  //fork a child process
      
        //checking for error
        if (pid < 0) {
              printf("*** ERROR: forking child process failed\n");
              return 1;
         }
        
        else if (pid == 0) {    //child process          
           if (execve(arguments[0], arguments, NULL) < 0) {     
             printf("*** ERROR: exec failed\n");
             fflush(stdout);
             exit(0);
            }
         }
      
        else { //parent process   
           wait(NULL);
         }    
      
//         TODO:
//         1. Tokenize the command line input (split it on whitespace)
//         2. Create a child process which will execute the command line input
//         3. The parent process should wait for the child to plete
//         Hints (put these into Google):
//         man fork
//         man execve
//         man wait
//         man strtok

    }
    
    // This should never be reached.
    return -1;
}
