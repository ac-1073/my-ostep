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

void insert_Node(char** read_line, size_t read_len) {

    struct Node* new = NULL;
    new = malloc(sizeof(*new));
    new->line = malloc(read_len);
    strncpy(new->line, *read_line, read_len);

    if  (head == NULL)    {
        head = new;
        new->prev = NULL;
    } else  {
        tail->next = new;
        new->prev = tail;
    }
    tail = new;
    new->next = NULL;

}

void open_File(FILE** fptr, char* file, const char* mode){

    *fptr = fopen(file, mode);
    if (*fptr == NULL){
        fprintf(stderr, "reverse: cannot open file '%s'\n", file);
        exit(1);
    }

}

int main(int argc, char** argv) {

    FILE *input, *output;
    char* read_line = NULL;
    size_t len = 0;
    __ssize_t read;
    struct Node* tmp;

    switch (argc)
    {
    case 1:
        input = stdin;
        output = stdout;
        break;
    case 2:
        open_File(&input, argv[1], "r");
        output = stdout;
        break;
    case 3:
        open_File(&input, argv[1], "r");
        open_File(&output, argv[2], "w");
        if (strcmp(argv[1], argv[2]) == 0 || input == output){
            fprintf(stderr, "reverse: input and output file must differ\n");
            fclose(input);
            fclose(output);
            exit(1);
        }
        break;
    default:
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    while((read = getline(&read_line, &len, input)) != -1)    {
        insert_Node(&read_line, read + 1);
    }

    fclose(input);
    
    while (tail != NULL)    {
        fprintf(output, tail->line);
        free(tail->line);
        tmp = tail;
        tail = tail->prev;
        free(tmp);
    }
    
    fclose(output);
    free(read_line);

exit(0);
}