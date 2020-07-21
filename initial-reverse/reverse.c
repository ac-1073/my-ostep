#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
        char* line;
        struct Node* prev;
        struct Node* next;
};

static struct Node *head, *tail = NULL;

void insert_Node (char** read_line, size_t read_len)
{
        struct Node* new = NULL;
        new = malloc(sizeof(*new));
        new->line = malloc(read_len);
        strncpy(new->line, *read_line, read_len);

        if (head == NULL)       {
                head = new;
                new->prev = NULL;
        } else  {
                tail->next = new;
                new->prev = tail;
        }
        tail = new;
        new->next = NULL;
}

void open_File (FILE** fptr, char* file, const char* mode)
{
        *fptr = fopen(file, mode);
        if (*fptr == NULL) {
                fprintf(stderr, "reverse: cannot open file '%s'\n", file);
                exit(1);
        }
}

void print_List (FILE** out)
{
        struct Node* tmp;
        while (tail != NULL) {
                fprintf(*out, tail->line);
                free(tail->line);
                tmp = tail;
                tail = tail->prev;
                free(tmp);
        }
}

void check_Filenames (char* arg1, char* arg2)
{
        if (strcmp(arg1, arg2) == 0){
                fprintf(stderr, "reverse: input and output file must differ\n");
                exit(1);
        }
}

int get_Filesize (FILE* file)
{
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);
        return size;
}

void check_Filesizes (FILE* f1, FILE* f2)
{
        if (get_Filesize(f1) == get_Filesize(f2)) {
                fprintf(stderr, "reverse: input and output file must differ\n");
                exit(1);
        }
}

int main (int argc, char** argv)
{
        FILE *input, *output;
        char* read_line = NULL;
        size_t len = 0;
        __ssize_t read;

        switch (argc)
        {
                case 1: input = stdin;
                        output = stdout;
                        break;

                case 2: open_File(&input, argv[1], "r");
                        output = stdout;
                        break;

                case 3: check_Filenames(argv[1], argv[2]);
                        open_File(&input, argv[1], "r");
                        open_File(&output, argv[2], "w");
                        check_Filesizes(input, output);
                        break;
                        
                default:fprintf(stderr, "usage: reverse <input> <output>\n");
                        exit(1);
        }

        while ((read = getline(&read_line, &len, input)) != -1) {
                insert_Node(&read_line, read + 1);
        }

        print_List(&output);
        fclose(input);
        fclose(output);
        free(read_line);

        exit(0);
}