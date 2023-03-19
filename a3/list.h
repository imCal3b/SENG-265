/** @file listy.h
 *  @brief Function prototypes for the linked list.
 */
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define MAX_WORD_LEN 50

typedef struct q_ref
{
	int fields;
	char field1[30];
	char field2[30];
	char field3[30];
	char field4[30];
} q_ref;

typedef struct input
{
    char * data_file;
    int question;
    int num_outputs;
} input;

/**
 * @brief An struct that represents a node in the linked list.
 */
typedef struct node_t
{
    char *field1;
    char *field2;
    char *field3;
    char *field4;
    char *subject;
    int statistic;
    struct node_t *next;
} node_t;

/**
 * Function protypes associated with a linked list.
 */
node_t *new_node(char *val);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
node_t *add_inorder(node_t *, node_t *);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);
void apply(node_t *, void (*fn)(node_t *, void *), void *arg);

#endif
