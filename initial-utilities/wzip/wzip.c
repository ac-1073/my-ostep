#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

    FILE* fp;
    int j;
    int count = 0;
    int curr = 0;
    int prev = -1;

    if  (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (j = 1; j < argc; j++)  {

        fp = fopen(*(++argv), "r");

        if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }

        while   ((curr = fgetc(fp)) != EOF) {

            if  ( prev == -1)   {
                prev = curr;
                count++;
            }
            else if (curr != prev)  {
                fwrite(&count, sizeof(int), 1, stdout);
                fputc(prev, stdout);
                count = 1;
            }
            else    {
                count++;
            }
            prev = curr;

        }

        fclose(fp);

    }

    if  (count > 0) {
        fwrite(&count, 4, 1, stdout);
        fputc(prev, stdout);
    }

exit(0);

}