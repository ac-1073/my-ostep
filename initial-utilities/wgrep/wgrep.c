#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

    if(argc == 1){
        printf("wgrep: searchterm [file...]\n");
        exit(1);
    }

    if(argc == 2){
        char buffer[100];
        fgets(buffer, 100, stdin);
    }

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i;
    int cmp_len = 0;

    char* term = *(++argv);
    int term_len = 0;
    char* tp = (char*)term;
    while(*tp != '\0'){
        term_len++;
        tp++;
    }
    argv++;

    for(i = 2; i < argc; i++, argv++){
        fp = fopen(*argv, "r");
        if (fp == NULL){
            printf("wgrep: cannot open file\n");
            exit(1);
        }

        while((read = getline(&line, &len, fp)) != -1){
            char* p1 = (char*)line;
            char* p2 = (char*)term;
            cmp_len = 0;

            while(*p1 != '\n'){

                if(*p1 == *p2){
                    while(*p2 != '\0' && *p1 == *p2){
                        cmp_len++;
                        p2++;
                        p1++;
                    }
                    if(cmp_len == term_len){
                        printf("%s", line);
                        break;
                    }
                    cmp_len = 0;
                    p2 = (char*)term;
                }
                p1++;
            }
        }
        fclose(fp);
    }
    free(line);
    exit(0);
}