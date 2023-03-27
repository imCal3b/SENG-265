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

input* read_arguments(int argc, char **argv, input * arguments); 
void init_q_options(q_ref q_opt[]);
node_t* yaml_to_node(node_t * list_head, q_ref opt[], input * args);
node_t* result_list_slice(node_t * head, int num_el);
void free_mem(node_t * cur);

// TODO: Make sure to adjust this based on the input files given
#define MAX_LINE_LEN 150

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
	printf("\n-----------------------\n");
	printf("----- PROG START ------\n");
	printf("-----------------------\n");
    // Initializing Question options
    //------------------------------
	q_ref q_opt[3];
	init_q_options(q_opt);

    // Reading the input arguments from the command line
    //--------------------------------------------------
    input * inputs = (input*)malloc(sizeof(input));
    inputs = read_arguments(argc, argv, inputs);

    printf("DATA: %s \nQUESTION: %d \nN: %d \n",
        inputs->data_file,
        inputs->question,
        inputs->num_outputs);

	printf("Fields: %s|%s|%s|%s \n\n",
					q_opt[inputs->question-1].field1,
					q_opt[inputs->question-1].field2,
					q_opt[inputs->question-1].field3,
					q_opt[inputs->question-1].field4);

    // Read yaml file and make node elements for each route
    //-----------------------------------------------------
    node_t * result_list = NULL;
    result_list = yaml_to_node(result_list,q_opt,inputs);

	//TODO: function to take in result_list and return new list with 'N' elements
	result_list = result_list_slice(result_list, inputs->num_outputs);

	analysis(result_list);

}

// *********************************************************************
// ************************ END OF MAIN ********************************
// *********************************************************************

/*
Function:   looks through the arguments specified when running the program.
Parameters: int argc - the number of arguments.
            char **argv - a pointer to the array of pointers pointing to the
            specified arguments.
            input * arguments - the input arguments struct element.
return: NA
PreConditions: Must call the 3 specified command line arguments from tester.
*/
input* read_arguments(int argc, char **argv, input * arguments) 
{
    if (argc == 1 || argc > 4) {
		printf("incorrect number of arguments!\n");
        exit(0);

    } else {
        char field[10];
        for (int i=1;i<4;i++)
        {
			char * value = (char*)malloc(sizeof(char) * 32);
			if (value == NULL) exit(EXIT_FAILURE); // malloc safety

            sscanf(*(argv+i),"--%[A-Z]=%[^\t\n]",
                field,
                value);
			
			printf("Field: %s Value: %s \n",
							field,
							value);

            if (strcmp(field,"DATA") == 0) arguments->data_file = strdup(value);
			else if (strcmp(field,"QUESTION") == 0) arguments->question = atoi(value);
			else if (strcmp(field,"N") == 0) arguments->num_outputs = atoi(value);
     
		}
		printf("\n");
		return arguments;
    }
}

/*
Function:   Reads the line items of the yaml file and puts the route data required
            by the question specified, into a node element. The node element is then
            added to a list and sorted.
Parameters: node_t * list_head - the node that defines the head of the list.
            q_ref opt[] - the required data fields relative to the question requested.
            input * args - the input arguments from program call.
return:     node_t * - returns a node_t pointer to the node at the head of the list.
PreConditions: NA
*/
node_t* yaml_to_node(node_t * list_head, q_ref opt[], input * args)
{
    FILE * data_file = fopen(args->data_file,"r");
    char line[MAX_LINE_LEN];
	
	int q = args->question - 1;
    int count = 1; //27
    node_t * cur;
    fgets(line,MAX_LINE_LEN,data_file);
    while (fgets(line,MAX_LINE_LEN,data_file))
    {		
        char arg_buff[35];
		char val_buff[35];
        
     
	 	if (strncmp(line,"-",1) == 0 && count == 1) {
            cur = (node_t*)malloc(sizeof(node_t));
			if (cur == NULL) exit(EXIT_FAILURE); // malloc safety
			cur->statistic = 1;
			cur->next = NULL;
        }

		// printf("line: %s",line);
        sscanf(line,"%*c %[a-z_]: %[^\t\n]",arg_buff,val_buff);

		if (strcmp(opt[q].field1,arg_buff) == 0) cur->field1 = strdup(val_buff);
		else if (strcmp(opt[q].field2, arg_buff) == 0) cur->field2 = strdup(val_buff);
		else if (strcmp(opt[q].field3, arg_buff) == 0) cur->field3 = strdup(val_buff);
		else if (strcmp(opt[q].field4, arg_buff) == 0) cur->field4 = strdup(val_buff);


        if (count%13 == 0) {
			if ((args->question == 1 && strcmp(cur->field3,"Canada") == 0) || args->question != 1) {	
				// insert new node into the list
				// TODO: add sort type switch case to order sort function and add parameter
				list_head = order_sort(list_head, cur, opt[q].sort_type);

			} else free(cur);

			cur = (node_t*)malloc(sizeof(node_t));
			if (cur == NULL) exit(EXIT_FAILURE); // malloc safety
			cur->statistic = 1;
			cur->next = NULL;
		}

		count++;
    }
	
    fclose(data_file);
	return list_head;
}

/*
Function:   Takes the sorted list as input and returns the head pointer of a new list 
			containing the specified number of elements.
Parameters: node_t * head - The node pointing to the head of the list.
			int num_el - The specified size of the return list.
return:     node_t * - returns a node_t pointer to the node at the head of the list.
PreConditions: NA
*/
node_t* result_list_slice(node_t * head, int num_el)
{
	if (num_el == 0) return NULL;

	node_t * cur = head;
	for (int i=1; i < num_el; i++) {cur = cur->next;}

	node_t * free_cur = cur->next;
	free_mem(free_cur);

	cur->next = NULL;

	return head;
}

/*
Function:   frees the memory of the unused elements in the sorted list.
Parameters: node_t * cur - Pointer to the first unused node in the sorted list.
return:     NA
PreConditions: NA
*/
void free_mem(node_t * cur)
{
	node_t * temp = NULL;
	while (cur != NULL)
	{
		temp = cur->next;
		free(cur->field1);
		free(cur->field2);
		free(cur->field3);
		free(cur->field4);
		free(cur->subject);
		free(cur);

		cur = temp;
	}
}

/*
Function:   initializes a struct array element with the required output data
            fields associated to the question. Each index is initialized to
            the requirements of a specific question.
Parameters: q_opt[] - The array of q_ref elements holding the field data.
return: NA
PreConditions: NA
*/
void init_q_options(q_ref q_opt[])
{
	q_opt[0].sort_type = 1;
	strncpy(q_opt[0].field1,"airline_name\0",sizeof(char)*30);
	strncpy(q_opt[0].field2,"airline_icao_unique_code\0",sizeof(char)*30);
	strncpy(q_opt[0].field3,"to_airport_country\0",sizeof(char)*30);
	strncpy(q_opt[0].field4,"\0",sizeof(char)*30);

	q_opt[1].sort_type = 0;
	strncpy(q_opt[1].field1,"to_airport_country\0",sizeof(char)*30);
	strncpy(q_opt[1].field2,"\0",sizeof(char)*30);
	strncpy(q_opt[1].field3,"\0",sizeof(char)*30);
	strncpy(q_opt[1].field4,"\0",sizeof(char)*30);

	q_opt[2].sort_type = 1;
	strncpy(q_opt[2].field1,"to_airport_name\0",sizeof(char)*30);
	strncpy(q_opt[2].field2, "to_airport_icao_unique_code\0",sizeof(char)*30);
	strncpy(q_opt[2].field3,"to_airport_city\0",sizeof(char)*30);
	strncpy(q_opt[2].field4,"to_airport_country\0",sizeof(char)*30);
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
    //printf(fmt, p->field2);
	printf("%s | %d\n",p->field1,p->statistic);
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
