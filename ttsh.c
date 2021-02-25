/******************************* *
 * CS3841 - 021
 *   Teeny Tiny Shell
 * Colton Rivard
 ********************************/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

#define INPUT_MAX 256
#define CMD_MAX 5
#define ARG_MAX 10


/* read_cmd_string()
 *     Reads a line of text from the user
 *         Parameters:  dest - target location for the input
 *         Returns: int - 0 on success or
 *                        -1 on error
*/                    \
        int read_cmd_string(char dest[INPUT_MAX]){ \
        // Read user input
    if(fgets(dest, INPUT_MAX, stdin) == NULL) {
        fprintf(stderr, "Unable to read user input\n");
        return -1;
    }
    // Remove trailing return character
    int len = strlen(dest);
    if(dest[len-1] == '\n') {
        dest[len - 1] = '\0';
    }

    return 0;}
/* parse_commands()
 *   Reads a line of text from the user
 *      Parameters:  input - string containing user input
 *                   cmd_strs - the target array for command strings
 *         Returns: int - The number of commands found or
 *                 -1 on error */
int parse_commands(char input[INPUT_MAX], char cmd_strs[CMD_MAX][INPUT_MAX])
{
    // Chop the input into command strings
    int cmd_count = 0;
    char* cmd_ptr = strtok(input, ";");
    while(cmd_ptr) {
        if(cmd_count >= CMD_MAX) {
            fprintf(stderr, "Too many commands\n");
            return -1;
        }
        strncpy(cmd_strs[cmd_count], cmd_ptr, INPUT_MAX);
        cmd_count++;
        cmd_ptr = strtok(NULL, ";");
    }
    return cmd_count;
}
int main()
{
while (1){
    char user_input[INPUT_MAX];
    char cmd_strs[CMD_MAX][INPUT_MAX];
    char quit[INPUT_MAX] = "quit";
    char *arg_strs[256];
    int argmax = 0;
   

    // TODO need to be able to get input from
    //    the user in a loop


    // Print the input prompt
    printf("$> ");


        if (read_cmd_string(user_input) == -1) {
            return 1;
        } else {

            // TODO: Figure out how to handle the 'quit' command
            if (strcmp(user_input, quit) == 0) {
                kill(getpid(), SIGINT);
            }

            // Chop the input into command strings
            int cmd_count = parse_commands(user_input, cmd_strs);
            if (cmd_count == -1) {
                return 1;
            }
            // Chop the commands into arguments and execute one at a time
            for (int i = 0; i < cmd_count; i++) {
                arg_strs[0] = strtok(cmd_strs[i], " ");
                int x = 0;
                while (arg_strs[x] != NULL) {
                if(argmax == ARG_MAX){
                fprintf(stderr, "Too many arguments\n");
           		 return -1;
                }
                    arg_strs[++x] = strtok(NULL, " ");
                    argmax++;
                }
		//creats child process
                pid_t pid = fork();
                if (pid == 0) {

                    if(execvp(arg_strs[0], arg_strs) == -1){
                    printf("failed to execute \n");
                    }

                    exit(0);
                    //child handles the program calls
               }
                if (pid > 0) {
               //parent waits for child process to finish
                    wait(NULL);
                }


            }

         
        }
}

    return 0;}
