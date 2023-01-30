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
void read_file();
void allocate_data();
int compare();
char * strtok_single();

struct input {
    char data_field[20];
    char argument[40];
};

struct file_line {
    char airline_name[35];
    char airline_icao_code[4];
    char airline_country[35];

    char from_airport_name[50];
    char from_airport_city[35];
    char from_airport_country[35];
    char from_airport_icao_code[5];
    int from_airport_altitude;

    char to_airport_name[50];
    char to_airport_city[35];
    char to_airport_country[35];
    char to_airport_icao_code[5];
    int to_airport_altitude;
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
int main(int argc, char * argv[])
{
    // TODO: your code.
    struct input inputs[13];

    read_arguments(argc,argv,1,inputs);

    FILE * data_file = fopen(inputs[0].argument,"r");

    read_file(data_file,inputs,argc-1);

    exit(0);
}

/*
Function:   looks through the arguments specified when running the program.
Parameters: int argc - the number of arguments.
            char **argv - a pointer to the array of pointers pointing to the
            specified arguments.
            int arg_index - keeps track of the index in argv to read from.
            struct input cur_ptr[] - pass through inputs[] to store field
            and argument parameters.
return: NA
PreConditions: must be at least one argument specified at program call.
*/
void read_arguments(int argc, char ** argv, int arg_index, struct input cur_ptr[]) 
{
    if (argc == 1) {
        printf("no arguments given\n");
        return;

    } else if (arg_index == argc || arg_index > 13) {
        printf("\nall arguments read: %d arguments\n\n",--arg_index);
        return;

    } else {
        printf("reading fields\n");
        int index_os = arg_index - 1;
        sscanf(*(argv+arg_index),"--%[A-Z_]=%[^\t\n]",cur_ptr[index_os].data_field,cur_ptr[index_os].argument);

        return read_arguments(argc,argv,++arg_index,cur_ptr);
    }
}

/*
Function:   read the input file and compare input arguments with each file row
Parameters: 
*/
void read_file(FILE * stream, struct input inputs[], int num_arg)
{
    printf("\nreading file...\n");
    int count = 1;
    struct file_line data;
    char line[1024];
    fgets(line,1024,stream); // used to bypass header-
    while (count < 10) 
    {
        printf("reading line: %d\n",count);
        fgets(line,1024,stream);
        char * token = strtok_single(line,",");
        allocate_data(token,&data);

        if (compare(data,inputs,num_arg,0) == 1) 
        {
            printf("- MATHCING LINE -");
        } 
        else 
        {}
        printf("\n");
        ++count;
    }
}

void allocate_data(char * token, struct file_line * data_ptr)
{
    printf("inside allocate_data...\n");

    strcpy(data_ptr->airline_name,token);
    printf("check 1\n");

    token = strtok_single(NULL, ",");
    strcpy(data_ptr->airline_icao_code,token);

    token = strtok_single(NULL, ",");
    strcpy(data_ptr->airline_country,token);

    token = strtok_single(NULL, ",");
    strcpy(data_ptr->from_airport_name,token);

    token = strtok_single(NULL, ",");
    strcpy(data_ptr->from_airport_city,token);

    token = strtok_single(NULL, ",");
    strcpy(data_ptr->from_airport_country,token);

    token = strtok_single(NULL, ",");
    strcpy(data_ptr->from_airport_icao_code,token);
    printf("check 2\n");

    token = strtok_single(NULL, ",");
    data_ptr->from_airport_altitude = atoi(token);
    printf("check 3 - integer store\n");

    token = strtok_single(NULL, ",");
    strcpy(data_ptr->to_airport_name,token);
    printf("check 4\n");

    token = strtok_single(NULL, ",");
    strcpy(data_ptr->to_airport_city,token);
    printf("check 5\n");

    token = strtok_single(NULL, ",");
    strcpy(data_ptr->to_airport_country,token);
    printf("check 6\n");

    token = strtok_single(NULL, ",");
    strcpy(data_ptr->to_airport_icao_code,token);
    printf("check 7\n");

    token = strtok_single(NULL, ",");
    data_ptr->to_airport_altitude = atoi(token);
    printf("check 8\n");

    printf("%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%d\n\n",
        data_ptr->airline_name,
        data_ptr->airline_icao_code,
        data_ptr->airline_country,
        data_ptr->from_airport_name,
        data_ptr->from_airport_city,
        data_ptr->from_airport_country,
        data_ptr->from_airport_icao_code,
        data_ptr->from_airport_altitude,
        data_ptr->to_airport_name,
        data_ptr->to_airport_city,
        data_ptr->to_airport_country,
        data_ptr->to_airport_icao_code,
        data_ptr->to_airport_altitude
        );
}

/*
Function:   compares the elements of the input file against the specified input arguments.
Parameters: struct file_line data - passes through the parsed data from the line segment.
            struct input inputs[] - passes through the input arguments for comparing with data.
            int num_arg - identifier for the number of iterations required to compare
            all arguments passed to the program.
            int i - counter variable.
Return: int - returns a boolean value 1 (1==true ; 0==false) when all arguments passed to the
        program match with the corresponding data value from the parsed line.
PreConditions:  must have line items and an input argument to compare against. If no arguments
                are passed to the program there is nothing to compare.
*/
int compare(struct file_line data, struct input inputs[], int num_arg, int arg_cnt)
{
    printf("comparing %s...\n",inputs[arg_cnt].data_field);
    if (arg_cnt+1 == num_arg && strcmp(inputs[arg_cnt].data_field, "DATA") == 0)
    {
        printf("no arguments!\n");
        return 0;
    } 
    if (arg_cnt == num_arg) 
    {
        printf("MATCH!\n");
        return 1;
    }

    if (strcmp(inputs[arg_cnt].data_field, "AIRLINE") == 0)
    {
        if (strcmp(inputs[arg_cnt].argument, data.airline_icao_code) == 0 || 
            strcmp(inputs[arg_cnt].argument, data.airline_name) == 0)
        {
            return compare(data,inputs,num_arg,++arg_cnt);
        }
        return 0;
    }
    else if (strcmp(inputs[arg_cnt].data_field, "SRC_CITY") == 0)
    {
        if (strcmp(inputs[arg_cnt].argument,data.from_airport_city) == 0)
        {
            return compare(data,inputs,num_arg,++arg_cnt);
        }
        return 0;
    }
    else if (strcmp(inputs[arg_cnt].data_field, "SRC_COUNTRY") == 0)
    {
        if (strcmp(inputs[arg_cnt].argument,data.from_airport_country) == 0)
        {
            return compare(data,inputs,num_arg,++arg_cnt);
        }
        return 0;
    }
    else if (strcmp(inputs[arg_cnt].data_field, "DEST_CITY") == 0)
    {
        if (strcmp(inputs[arg_cnt].argument,data.to_airport_city) == 0)
        {
            return compare(data,inputs,num_arg,++arg_cnt);
        }
        return 0;
    }
    else if (strcmp(inputs[arg_cnt].data_field, "DEST_COUNTRY") == 0)
    {
        if (strcmp(inputs[arg_cnt].argument,data.from_airport_country) == 0)
        {
            return compare(data,inputs,num_arg,++arg_cnt);
        }
        return 0;
    }
    else if (strcmp(inputs[arg_cnt].data_field, "DATA") == 0)
    {
        return compare(data,inputs,num_arg,++arg_cnt);
    }
    else
    {
        printf("not a field!\n"); 
        return 0;
    }

}

/*
Function: modification on strtok so that empty data fields are read as NULL
*/
char * strtok_single (char * str, char const * delims)
{
  static char  * src = NULL;
  char  *  p,  * ret = 0;

  if (str != NULL)
    src = str;

  if (src == NULL)
    return NULL;

  if ((p = strpbrk (src, delims)) != NULL) {
    *p  = 0;
    ret = src;
    src = ++p;

  } else if (*src) {
    ret = src;
    src = NULL;
  }

  return ret;
}