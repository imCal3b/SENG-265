/** @file route_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process airline routes.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author BRAYDEN SHKWAROK V00866278
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read_arguments();

struct input {
    char data_field[20];
    char argument[40];

    struct input *next;
};

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    // TODO: your code.
    struct input head;
    struct input *cur_ptr;
    cur_ptr = &head;
    printf("initializing input storage...\n\n");
    for (int i=0;i<argc-1;++i) {
        struct input next_input;       // create new pointer
        cur_ptr->next = &next_input;    // assign new pointers address to cur.next
        cur_ptr = cur_ptr->next;        // set cur to point to next
        cur_ptr->next = NULL;
    }

    printf("head addr: %p\n",&head);
    printf("h_df addr: %p\n",&(head.data_field));
    printf("h_ag addr: %p\n",&(head.argument));
    printf("h_ag addr: %p\n\n",head.next);

    read_arguments(argc,argv,1,&head);

    cur_ptr = &head;
    int count = 0;
    while (cur_ptr->next != NULL || count < 5) {
        printf("field: %s arg: %s\n",cur_ptr->data_field,cur_ptr->argument);
        ++count;
        cur_ptr = cur_ptr->next;
    }

    exit(0);
}

/*
Function: looks through the arguments specified when running the program
Parameters: int argc - the number of arguments
            char **argv - a pointer to the array of pointers pointing to the
            specified arguments
return: NA
PreConditions: must be at least one argument specified at program call
*/
void read_arguments(int argc, char **argv, int count, struct input *cur_ptr) 
{
    if (argc == 1) {
        printf("no arguments given\n");
        return;

    } else if (count == argc || count > 13) {
        printf("\nall arguments read: %d arguments\n\n",--count);
        return;

    } else {
        printf("reading fields\n\n");
        sscanf(*(argv+count),"--%[A-Z]=%[^\t\n]",cur_ptr->data_field,cur_ptr->argument);

        printf("curr addr: %p\n",cur_ptr);
        printf("c_df addr: %p\n",&(cur_ptr->data_field));
        printf("c_ag addr: %p\n",&(cur_ptr->argument));
        printf("c_ag addr: %p\n",cur_ptr->next);

        cur_ptr = cur_ptr->next;
        return read_arguments(argc,argv,++count,cur_ptr);
    }
}