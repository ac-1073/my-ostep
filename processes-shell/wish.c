#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LEN 120 // Buffer size for all arrays and strings

char error_message[30] = "An error has occurred\n";

int wish_path (char* args, char paths[]){
        if (args != NULL){
                memset(paths, 0, MAX_LEN);
                strncpy(paths, args, strlen(args));
        } else {
                write(STDERR_FILENO, error_message, strlen(error_message));
        }
        return 1;
}

int wish_cd (char* args, char paths[]){

        if (args == NULL) {
                write(STDERR_FILENO, error_message, strlen(error_message));
        }
        chdir("..");
        return 1;
}

/* Removes leading & trailing whitespace from strings */
char* clear_Whitespace (char* line)
{
        char* end;

        /* Advance pointer through whitespace */
        while (isspace((unsigned char)*line))
                line++;
        
        /* Return if all whitespace */
        if (*line == 0)
                return line;

        /* Remove trailing whitespace */
        end = line + strlen(line) - 1;

        while (end > line && isspace((unsigned char)*end))
                end--;
        
        /* Set new null terminator */
        end[1] = '\0';

        return line;
}

/* 
 * Tokenize strings by given delimiter.
 * Removes leading/trailing whitespace
 * from each new token.
 * 
 * input : string from user input e.g. "path /bin/usr & ls /test/"
 * delim : split string by given character(s) e.g. "&"
 * 
 * returns: 2d array of tokens e.g. {"path /bin/usr", "ls /test/",..., NULL}
 * 
*/
char** tokenize (char* input, const char* delim)
{
        char** new = malloc(sizeof(char*) * MAX_LEN);
        int i = 0;

        if (new == NULL) {
                write(STDERR_FILENO, error_message, strlen(error_message));
        }
        else {
                char *tok, *end = input;

                while ((tok = strsep(&end, delim)) != NULL) {
                        if(*clear_Whitespace(tok) != 0){
                                new[i] = clear_Whitespace(tok);
                                i++;
                        }
                }
                /* Set first unused index to NULL */
                new[i] = NULL;
        }

        /* free and return NULL if no valid input */
        if (new[0] == NULL){ 
                free(new);
                return NULL;
        }
       
        return new;
}

/* 
 * Evaluate user input and run built-in commands
 * or processes as specified.
*/
int eval (char* line, char path[])
{
        char** cmds;
        cmds = tokenize(line, "&");

        // Return if malloc fail or no valid commands
        if (cmds == NULL){
                return 1;
        }

        /* Run built in commands */
        if (cmds[1] == NULL){

                char* cmd_func = cmds[0];
                char* cmd_args = cmds[0];
                free(cmds);
                cmd_func = strsep(&cmd_args, " \t\n");

                if (strncmp(cmd_func, "exit", sizeof(char) * 4) == 0)
                        return 0;

                if (strncmp(cmd_func, "path", sizeof(char) * 4) == 0)
                        return wish_path(cmd_args, path);

                if (strncmp(cmd_func, "cd", sizeof(char) * 2) == 0)
                        return wish_path(cmd_args, path);
        } else {
                /* TODO */
                //run_procs(cmds);
        }

        return 1;
}


/* TODO: finish */
/* runs processes for n commands */
/*
void run_procs (char* line)
{
       pid_t pids;
       int n = 4; // No. of commands (test val)
       int i = 0;
       char *cmd_tok = line, *cmd_end = line;

       while (i < n) {
                if ((pids = fork()) < 0) {
                        perror("fork");
                        abort();
                } else if (pids == 0) {
                        printf("[child] pid %d from [parent] pid %d\n", getpid(), getppid());
                        exit(0);
                }
                i++;
       }

       int status;
       pid_t pid;

       while (n > 0) {
               pid = wait(&status);
               printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
               n--;
       }
}*/


int main (int argc, char** argv)
{
        char path[MAX_LEN];  // Shell search path. Set to '/bin' on startup.
        strncpy(path, "/bin", 5);

        char* line = NULL;
        size_t len = 0;
        __ssize_t read;

        printf("wish> ");
        while ((read = getline(&line, &len, stdin)) != -1 && eval(line, path) == 1)
                printf("wish> ");

        free(line);
        exit(0);
}