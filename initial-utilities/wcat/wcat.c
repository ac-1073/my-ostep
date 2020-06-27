#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv){

    if(argc == 0){
        exit(0);
    }

    int count = 1;
    char buffer[100];
    argv++;

    while(count < argc){

        FILE* fp = fopen(*argv, "r");
        if (fp == NULL){
            printf("wcat: cannot open file\n");
            exit(1);
        }
        while(fgets(buffer, 100, fp) != NULL){
            printf("%s", buffer);
        }
        fclose(fp);
        count++;
        argv++;
    }
    exit(0);
}