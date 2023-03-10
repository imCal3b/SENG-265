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
#include <unistd.h>

void read_arguments();
void read_file();
void allocate_data();
int compare();
void write_file();
void output_write_header();
void output_write_contents();
int argument_output_specifier();
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
    struct input inputs[13];
    read_arguments(argc,argv,1,inputs);

    FILE * data_file = fopen(inputs[0].argument,"r");
    read_file(data_file,inputs,argc-1);

    fclose(data_file);
    exit(0);
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
void read_arguments(int argc, char ** argv, int arg_index, struct input cur_arg[]) 
{
    if (arg_index == argc || arg_index == 13) {
        return;

    } else {
        int index_os = arg_index - 1;
        sscanf(*(argv+arg_index),"--%[A-Z_]=%[^\t\n]",
            cur_arg[index_os].data_field,
            cur_arg[index_os].argument);

        return read_arguments(argc,argv,++arg_index,cur_arg);
    }
}

/*
Function:   read the input file and compare input arguments with each file row.
Parameters: file * stream - the file item we want to read using the function.
            struct input inputs[] - the input fields/arguments we want to use
            to search the file.
            int num_arg - the number of arguments from the program call.
return: NA
PreConditions: must have a file to input into the function.
*/
void read_file(FILE * stream, struct input inputs[], int num_arg)
{
    struct file_line data;
    FILE * result_file;

    if (access("output.txt",0) == 0) remove("output.txt");
    
    char line[1024];
    int match = 0;
    
    int option = argument_output_specifier(inputs,num_arg);
    if (option == 100000) return; // no arguments specified at program call

    fgets(line,1024,stream); // bypass header line in .csv file
    while (fgets(line,1024,stream)) 
    {
        // parse line item into respective fields
        allocate_data(line,&data);

        // look for line item with fields matching input arguments
        if (compare(data,inputs,num_arg,0) == 1) 
        {
            // if first match: print header line
            if (match == 0) output_write_header(data,result_file,option);

            write_file(data,result_file,1,option);
            ++match;
        } 
    }
    // if no matches found
    if (match == 0) write_file(data,result_file,0,option);
}

/*
Function:   used to parse the line item from the data file into the
            respective data fields.
Parameters: char * token - pointer to the first token value from strtok_single().
            struct file_line * data_ptr - pointer to the file_line struct so we
            can access and store tokens to the apporopriate data field variable.
Return: NA
PreConditions: NA
*/
void allocate_data(char line[], struct file_line * data_ptr)
{
    char * token = strtok_single(line,",");
    strncpy(data_ptr->airline_name,token,sizeof(data_ptr->airline_name));

    token = strtok_single(NULL, ",");
    strncpy(data_ptr->airline_icao_code,token,sizeof(data_ptr->airline_icao_code));

    token = strtok_single(NULL, ",");
    strncpy(data_ptr->airline_country,token,sizeof(data_ptr->airline_country));

    token = strtok_single(NULL, ",");
    strncpy(data_ptr->from_airport_name,token,sizeof(data_ptr->from_airport_name));

    token = strtok_single(NULL, ",");
    strncpy(data_ptr->from_airport_city,token,sizeof(data_ptr->from_airport_city));

    token = strtok_single(NULL, ",");
    strncpy(data_ptr->from_airport_country,token,sizeof(data_ptr->from_airport_country));

    token = strtok_single(NULL, ",");
    strncpy(data_ptr->from_airport_icao_code,token,sizeof(data_ptr->from_airport_icao_code));

    token = strtok_single(NULL, ",");
    data_ptr->from_airport_altitude = atoi(token);

    token = strtok_single(NULL, ",");
    strncpy(data_ptr->to_airport_name,token,sizeof(data_ptr->to_airport_name));

    token = strtok_single(NULL, ",");
    strncpy(data_ptr->to_airport_city,token,sizeof(data_ptr->to_airport_city));

    token = strtok_single(NULL, ",");
    strncpy(data_ptr->to_airport_country,token,sizeof(data_ptr->to_airport_country));

    token = strtok_single(NULL, ",");
    strncpy(data_ptr->to_airport_icao_code,token,sizeof(data_ptr->to_airport_icao_code));

    token = strtok_single(NULL, ",");
    data_ptr->to_airport_altitude = atoi(token);
}

/*
Function:   compares the elements of the input file against the specified input arguments.
Parameters: struct file_line data - passes through the parsed data from the line segment.
            struct input inputs[] - passes through the input arguments for comparing with data.
            int num_arg - identifier for the number of iterations required to compare
            all arguments passed to the program.
            int arg_cnt - counter to keep track of which input argument is being compared.
Return: int - returns a boolean value 1 (1==true ; 0==false) when all arguments passed to the
        program match with the corresponding data value from the parsed line.
PreConditions:  must have line items and an input argument to compare against. If no arguments
                are passed to the program there is nothing to compare.
*/
int compare(struct file_line data, struct input inputs[], int num_arg, int arg_cnt)
{
    // bypass the 'DATA' argument
    if (strcmp(inputs[arg_cnt].data_field, "DATA") == 0) return compare(data,inputs,num_arg,++arg_cnt);
    
    // no arguments given
    if (arg_cnt+1 == num_arg && strcmp(inputs[arg_cnt].data_field, "DATA") == 0) return 0;

    // base case: all arguments read
    if (arg_cnt == num_arg) return 1;
    
    // check which data fields were input at program call
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
        if (strcmp(inputs[arg_cnt].argument,data.to_airport_country) == 0)
        {
            return compare(data,inputs,num_arg,++arg_cnt);
        }
        return 0;
    }
    else
    {return 0;} // NOT AN ALLOWED FIELD

}

/*
Function:   write the results of the search to the output file.
Parameters: struct file_line data - passing through the parsed data to be used for
            printing outputs to the output file.
            FILE * result - a pointer to the output file.
            int bool - a value used to define a matching state (val=0), or, no match found state (val=1).
            int option - the specifier for which output format should be used in the output file.
Return: NA
PreConditions: NA
*/
void write_file(struct file_line data, FILE * result, int bool,int option)
{
    if (bool == 0)
    {
        // no matches found
        result = fopen("output.txt","w");
        fputs("NO RESULTS FOUND.\n",result);
        fclose(result);
        return;
    }

    result = fopen("output.txt","a");
    output_write_contents(data,result,option);
    fclose(result);
}

/*
Function:   writes the header for the results.txt file based on the arguments specified.
Parameters: struct file_line data - pass through the data fields to be used in header.
            FILE * result - pointer to the output file so we can access and write to it.
            int option - identifier for which output format should be used.
Return: NA
PreConditions: Runs when the first matching case is encountered. Otherwise does not run.
*/
void output_write_header(struct file_line data, FILE * result, int option)
{
    result = fopen("output.txt","a");
    char print_hdr[250];
    switch (option)
    {      
        case 110001:
            //AIRLINE DEST_COUNTRY
            snprintf(print_hdr,sizeof(print_hdr),"FLIGHTS TO %s BY %s (%s):\n",
                data.to_airport_country,
                data.airline_name,
                data.airline_icao_code);

            fputs(print_hdr,result);
            break;

        case 111100:
            //SRC_COUNTRY DEST_CITY DEST_COUNTRY
            snprintf(print_hdr,sizeof(print_hdr),"FLIGHTS FROM %s TO %s, %s:\n",
                data.from_airport_country,
                data.to_airport_city,
                data.to_airport_country);

            fputs(print_hdr,result);
            break;

        case 111110:
            //SRC_CITY SRC_COUNTRY DEST_CITY DEST_COUNTRY
            snprintf(print_hdr,sizeof(print_hdr),"FLIGHTS FROM %s, %s TO %s, %s:\n",
                data.from_airport_city,
                data.from_airport_country,
                data.to_airport_city,
                data.to_airport_country);

            fputs(print_hdr,result);
            break;
        
        default:
            // NONE-INVALID PARAMETER INPUT
            break;
    }
    
    fclose(result);
}

/*
Function: writes the output line data in results.txt when a matching item is found.
Parameters: struct file_line data - pass through the data fields to be in line contents.
            FILE * result - pointer to the output file so we can access and write to it.
            int option - identifier for output format of the output file.
Return: NA
PreConditions: Runs when a matching case is found.
*/
void output_write_contents(struct file_line data, FILE * result, int option)
{
    result = fopen("output.txt","a");
    char print_ctnt[250];

    if (option == 110001)
    {
        //AIRLINE DEST_COUNTRY
        snprintf(print_ctnt,sizeof(print_ctnt),"FROM: %s, %s, %s TO: %s (%s), %s\n",
            data.from_airport_icao_code,
            data.from_airport_city,
            data.from_airport_country,
            data.to_airport_name,
            data.to_airport_icao_code,
            data.to_airport_city);
    
        fputs(print_ctnt,result);
    }
    else if (option == 111100)
    {
        //SRC_COUNTRY DEST_CITY DEST_COUNTRY
        snprintf(print_ctnt,sizeof(print_ctnt),"AIRLINE: %s (%s) ORIGIN: %s (%s), %s\n",
            data.airline_name,
            data.airline_icao_code,
            data.from_airport_name,
            data.from_airport_icao_code,
            data.from_airport_city);

        fputs(print_ctnt,result);
    }
    else if (option == 111110)
    {
        //SRC_CITY SRC_COUNTRY DEST_CITY DEST_COUNTRY
        snprintf(print_ctnt,sizeof(print_ctnt),"AIRLINE: %s (%s) ROUTE: %s-%s\n",
            data.airline_name,
            data.airline_icao_code,
            data.from_airport_icao_code,
            data.to_airport_icao_code);

        fputs(print_ctnt,result);
    }
    else {/*INVALID OPTION*/}
 
    fclose(result);
}

/*
Function:   outputs a unique integer based on the arguments given at program call.
Parameters: struct input inputs[] - input arguments.
            int num_arg - the number of arguments given.
Return: int - the unique identifier for type of output required.
PreConditions: arguments were given at program call.
*/
int argument_output_specifier(struct input inputs[], int num_arg)
{
    int option = 100000;
    for (int i=0;i<num_arg;++i)
    {
        if (strcmp(inputs[i].data_field,"AIRLINE") == 0) {option += 1;}
        else if (strcmp(inputs[i].data_field,"SRC_CITY") == 0) {option += 10;}
        else if (strcmp(inputs[i].data_field,"SRC_COUNTRY") == 0) {option += 100;}
        else if (strcmp(inputs[i].data_field,"DEST_CITY") == 0) {option += 1000;}
        else if (strcmp(inputs[i].data_field,"DEST_COUNTRY") == 0) {option += 10000;}
        else{}
    }

    return option;
}

/*
Function:   modification on strtok so that empty data fields are read as NULL.
Parameters: char * str - pointer to the string to be tokenized.
            char const * delims - identifies the deliminating character(s).
Return: char * - pointer to the token element.
PreConditions: NA
NOTES: strtok_single() implementation borrowed from user 'Filip Roseen' in response to stack overflow question from the link below. The following function was borrowed for the purpose of handling the empty data fields in the csv, allowing data to be appropriately parsed into the struct elements.
https://stackoverflow.com/questions/8705844/need-to-know-when-no-data-appears-between-two-token-separators-using-strtok 
*/
char * strtok_single (char * line, char const * delims)
{
  static char * src = NULL;
  char * p, * ret_token = 0;

  if (line != NULL) src = line;

  if (src == NULL) return NULL;

  if ((p = strpbrk (src, delims)) != NULL) 
  {
    *p  = 0;
    ret_token = src;
    src = ++p;

  } else if (*src) 
  {
    ret_token = src;
    src = NULL;
  }

  return ret_token;
}
