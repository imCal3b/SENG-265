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
    read_arguments(argc,argv);

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
void read_arguments(int argc, char **argv)
{
    char *data_field[13], *argument[13];

    if (argc > 0) {
        for (int i=0;i<argc;i++) {
            printf("%s \n",*(argv + i));
        }
    }
}

