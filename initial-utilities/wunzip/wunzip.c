#include <stdio.h>
#include <stdlib.h>

#define SIZE sizeof(char) + sizeof(int)

int main (int argc, char** argv)    {

    FILE* fp;
    int i, j, count;
    size_t read;
    char* ptr = malloc(SIZE);

    if  (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (i = 1; i < argc; i++)  {

        fp = fopen(argv[i], "r");

        if  (fp == NULL)    {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        while ((read = fread(ptr, sizeof(char), SIZE, fp)) == SIZE)  {

            count = *(int*)ptr;

            for (j = 0; j < count; j++) {
                printf("%c", *(ptr + sizeof(int)));
            }

        }

    }
    
    fclose(fp);
    free(ptr);
    exit(0);
}