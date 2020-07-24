#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD 20 /*maximum commands to be run in shell*/
#define MAX_ARG 20 /*maximum arguments applied to a command*/

char error_message[30] = "An error has occurred\n";

/* Removes leading & trailing whitespace from strings */
char* clear_Whitespace (char* line)
{
        /* For error handling w/strsep */
        if (line == NULL)
                return NULL;

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
        char** new = malloc(sizeof(char*) * MAX_CMD);
        char *tok, *end = input;
        int i = 0;

        while ((tok = strsep(&end, delim)) != NULL) {
                /* TODO: realloc if commands exceed current size */
                new[i] = tok;
                end = clear_Whitespace(end);
                i++;
        }
        /* Set first unused index to NULL */
        new[i] = NULL;

        return new;
}

/* 
 * Evaluate user input and run built-in commands
 * or processes as specified.
*/
int eval (char* line)
{
        char** cmds;
        line = clear_Whitespace(line);
        cmds = tokenize(line, "&");
        /* TODO */
        
}

/* TODO: finish */
/* runs processes for n commands */
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
}


int main (int argc, char** argv)
{
        char* line = NULL; // User input
        size_t len = 0;
        __ssize_t read;
        char** path = NULL; // Search path(s) of shell

        printf("wish> ");

        while ((read = getline(&line, &len, stdin)) != -1) {
               
               /* 
                * TODO
               */
               printf("wish> ");
        }
        exit(0);
}