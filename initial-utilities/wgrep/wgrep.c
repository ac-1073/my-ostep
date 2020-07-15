#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

    if(argc == 1){
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    size_t i;
    char* term = *(++argv);
    size_t term_len = strlen(term);

    if(argc == 2){

        char buffer[250];
        char* ptr = NULL;

        while(fgets(buffer, sizeof(buffer), stdin) != NULL){

            for(i = 0; i < strlen(buffer); i++){

                ptr = &buffer[i]; 

                if(*ptr == *term && strncmp(&buffer[i], term, term_len) == 0){
                    printf("%s", buffer);
                    break;       
                }
            }
        }
    exit(0);
    }

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int j;
    argv++;

    for(j = 2; j < argc; j++, argv++){
        fp = fopen(*argv, "r");
        if (fp == NULL){
            printf("wgrep: cannot open file\n");
            exit(1);
        }

        while((read = getline(&line, &len, fp)) != -1){
            char* ptr = (char*)line;

            for(i = 0; i < len && *ptr != '\n' ; i++, ptr++){

                if(*ptr == *term && strncmp(ptr, term, term_len) == 0){
                    printf("%s", line);
                    break;
                }

            }
        }
        fclose(fp);
    }
    free(line);
    exit(0);
}
