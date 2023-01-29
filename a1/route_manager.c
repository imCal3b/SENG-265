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
    char *data_fields[13], *arguments[13];
    char **inputs[2] = {data_fields, arguments};

    for (int i=0;i < 13;i++) {
        char f_val[20] = "test f", a_val[40] = "test a";
        data_fields[i] = f_val;
        arguments[i] = a_val;
    }

    printf("string test: %s\n",inputs[0][0]);

    printf("fld_add: %p arg_add: %p \n\n",&inputs[0],&inputs[1]);
    
    
    for (int i=0;i<2;i++) {
        printf("f_add: %p a_add: %p \n",&data_fields[i],&arguments[i]);
    }

    printf("argc: %d\n\n",argc);
    read_arguments(argc,argv,1,inputs);

    for (int i=0;i<argc-1;i++) {

        printf("f:%s | a: %s \n",data_fields[i],arguments[i]);
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
void read_arguments(int argc, char **argv, int count, char **inputs_ptr)
{
    if (argc == 1) {
        printf("no arguments given\n");
        return;

    } else if (count == argc || count > 13) {
        printf("all arguments read: %d arguments\n\n",--count);
        return;

    } else {
        printf("reading fields\n");
        char *fields_ptr = inputs_ptr[0];
        char *arguments_ptr = inputs_ptr[1];

        char field[20], argument[40]; 
        int arr_pos_os =(count - 1);
        // printf("array offset: %d\n",arr_pos_os);

        sscanf(*(argv+count),"--%[A-Z]=%[^\t\n]",field,argument);
        printf("field: %s argument: %s\n",field,argument);

        // fields_ptr += arr_pos_os;
        (*fields_ptr) = *field;
        
        // arguments_ptr += arr_pos_os;
        *arguments_ptr = *argument;
        
        printf("f_add: %p a_add: %p\n\n",fields_ptr,arguments_ptr);
        //printf("from ptr: %s\n\n", *fields_ptr);


        return read_arguments(argc,argv,++count,inputs_ptr);
    }
}

// printf("in0_add: %p in1_add: %p\n",&*inputs_ptr[0],&*inputs_ptr[1]);

