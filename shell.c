#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h> 
#include <sys/types.h>
#include<sys/wait.h> 

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char *token;
char **environ;

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

       // 1. Tokenize the command line input (split it on whitespace)
        int isVariable = 1, i = 0;
        token = strtok(command_line, delimiters);
        while (token != NULL)
        {
           if (isVariable) 
              printf("%s\n", token); //WHY THE SAME???????????????????????????
           else{
              printf("%s\n", token); //WHY THE SAME????????????????????????
           }
           isVariable = isVariable ? 0 : 1;
           token = strtok(NULL, delimiters);
          
          arguments[i] = token;
          i++;
          
        // 2. Create a child process which will execute the command line input
         //fork a child process
         pid_t pid = fork();
       
         //checking for error
         if (pid < 0) { /* an error has occurred*/
              printf("*** ERROR: forking child process failed\n");
              return 1;
         }
         else if (pid == 0) { //child process          
//               if (execve(arguments, environ, NULL) < 0) {     
//                    printf("*** ERROR: exec failed\n");
//                    return 1;
//               }
               execlp("/bash/ls", "ls", NULL);
         }
    
       // 3. The parent process should wait for the child to complete
         else { //parent process   
           //the parent process will wait for the child process to finish
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

        return 0;

    }
    
    // This should never be reached.
    return -1;
}
