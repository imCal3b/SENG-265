/** @file route_manager.c
 *  @brief A small program to analyze airline routes data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author Brayden Shkwarok V00866278
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void inccounter(node_t *p, void *arg);
void print_node(node_t *p, void *arg);
void analysis(node_t *l);

// TODO: Make sure to adjust this based on the input files given
#define MAX_LINE_LEN 80

/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    input * inputs = (input*)emalloc(sizeof(input));
    inputs = read_arguments(argc, argv, 1, inputs);

    printf("DATA: %s \n Q: %s \n N: %d \n",
        inputs->data_file,
        inputs->data_file,
        inputs->num_outputs);
}

/*
Function:   looks through the arguments specified when running the program.
Parameters: int argc - the number of arguments.
            char **argv - a pointer to the array of pointers pointing to the
            specified arguments.
            int arg_index - keeps track of the index in argv to read from.
            struct input cur_arg[] - pass through inputs[] to store field
            and argument parameters.
return: NA
PreConditions: must be at least one argument specified at program call.
*/
input *read_arguments(int argc, char **argv, int arg_index, input * arguments) 
{
    if (arg_index == argc || arg_index > 3) {
        return;

    } else {
        char field[10];
        char value[32];
        int index_os = arg_index - 1;
        for (int i=0;i<3;i++)
        {
            sscanf(*(argv+arg_index),"--%[A-Z]=%[^\t\n]",
                field,
                value);

            if (strcmp(field,"DATA") == 0) arguments->data_file = strdup(value);
            else if (strcmp(field,"QUESTION") == 0) arguments->question = strdup(value);
            else if (strcmp(field,"N") == 0) arguments->num_outputs = atoi(value);
        }
    }
}

// ------------------- GIVEN LIST FUNCTIONS ----------------------
/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->word);
}

/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 *
 */
void analysis(node_t *l)
{
    int len = 0;

    apply(l, inccounter, &len);
    printf("Number of words: %d\n", len);

    apply(l, print_node, "%s\n");
}


// // Initial dummy code
//     char *line = NULL;
//     char *t;
//     int num = 0;
//     node_t *list = NULL;
//     line = (char *)malloc(sizeof(char) * MAX_LINE_LEN);
//     strcpy(line, "this is the starting point for A3.");

//     // Creating the nodes for the ordered list
//     t = strtok(line, " ");
//     while (t)
//     {
//         num++;
//         list = add_inorder(list, new_node(t));
//         t = strtok(NULL, " ");
//     }

//     // Printing out the content of the sorted list
//     analysis(list);

//     // Releasing the space allocated for the list and other emalloc'ed elements
//     node_t *temp_n = NULL;
//     for (; list != NULL; list = temp_n)
//     {
//         temp_n = list->next;
//         free(list->word);
//         free(list);
//     }
//     free(line);

//     exit(0);