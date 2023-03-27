/** @file list.c
 *  @brief Implementation of a linked list.
 *
 * Based on the implementation approach described in "The Practice
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 *
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"

/*
Function:   Takes in a list via a head pointer (which points to the head node) and
            a new node to be inserted in the list. 
            order_sort() starts by checking if field1 from cur and new are matching,
            if so, increment the counter, remove and set cur as new, and re-insert node
            into the list. If no match, simply insert node into the list.
Parameters: node_t * head - the node that defines the head of the list.
            node_t * new - the new node to be inserted into the ordered list. 
return:     node_t * - returns a node_t pointer to the node at the head of the list.
PreConditions: NA
*/
node_t * order_sort(node_t* head, node_t* new, int sort_type)
{
    if (head == NULL) {
        new->next = NULL;
        return new;
    }

	if (sort_type == 0) return rev_order(head, new);

    node_t * cur;
    node_t * prev = NULL;
    int match = 0;
    for (cur = head; cur != NULL; cur = cur->next)
    {
		//printf("new: %s | cur: %s\n",new->field1, cur->field1);
		// if item is already in list
        if (strcmp(new->field1,cur->field1) == 0 && match == 0)
        {
			//printf("match! %s | %s\n",new->field1,cur->field1);
            cur->statistic++;
            match = 1;
        
            // remove cur element from list to be re-sorted
            if (prev != NULL) prev->next = cur->next;
            else return cur; // already at head of list, just return
			
            new = cur;
            cur = head;
			prev = NULL;
        }

        // sort order largest to smallest in alphabetical order
        if (new->statistic < cur->statistic) {
            prev = cur;
        } else if (new->statistic == cur->statistic) {
            if (strcmp(new->field1, cur->field1) > 0) {
                prev = cur;
            } else break;
        } else break;
    }

    // set new node to point to the next
    new->next = cur;

    if (prev == NULL) {
        // if the new node is the head of the list
        return new;
    } else {
        // if new node is in middle/end of list
        prev->next = new;
        return head;
    }
}

node_t * rev_order(node_t* head, node_t* new)
{
    node_t * cur;
    node_t * prev = NULL;
    for (cur = head; cur != NULL; cur = cur->next)
    {
		//printf("checking node: %s | %s\n", new->field1,cur->field1);
        if (strcmp(new->field1,cur->field1) == 0) {
            cur->statistic++;
            
            if (prev == NULL) head = cur->next;
            else prev->next = cur->next;
 
            new = cur;
            cur = head;
			prev = NULL;  
            break;        
        }
		prev = cur;
    }


    for (cur = head; cur != NULL; cur = cur->next)
    {
        if (new->statistic > cur->statistic) {
                prev = cur;
        } else if (new->statistic == cur->statistic) {
                if (strcmp(new->field1, cur->field1) > 0) {
                    prev = cur;
                } else break;
        } else break;
    }

    // set new node to point to the next
    new->next = cur;

    if (prev == NULL) {
        // if the new node is the head of the list
        return new;
    } else {
        // if new node is in middle/end of list
        prev->next = new;
        return head;
    }
}

/**
 * Function:  new_node
 * -------------------
 * @brief  Allows to dynamically allocate memory for a new node to be added to the linked list.
 *
 * This function should confirm that the argument being passed is not NULL (i.e., using the assert library). Then,
 * It dynamically allocates memory for the new node using emalloc(), and assign values to attributes associated with the node (i.e., val and next).
 *
 * @param val The value to be associated with the node.
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *new_node(char *val)
{
    assert(val != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));

    temp->subject = strdup(val);
    temp->next = NULL;

    return temp;
}

/**
 * Function:  add_front
 * --------------------
 * @brief  Allows to add a node at the front of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the new head of the list.
 *
 */
node_t *add_front(node_t *list, node_t *new)
{
    new->next = list;
    return new;
}

/**
 * Function:  add_end
 * ------------------
 * @brief  Allows to add a node at the end of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *add_end(node_t *list, node_t *new)
{
    node_t *curr;

    if (list == NULL)
    {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next)
        ;
    curr->next = new;
    new->next = NULL;
    return list;
}

/**
 * Function:  add_inorder
 * ----------------------
 * @brief  Allows to add a new node to the list respecting an order.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *add_inorder(node_t *list, node_t *new)
{
    node_t *prev = NULL;
    node_t *curr = NULL;

    if (list == NULL)
    {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next)
    {
        if (strcmp(new->subject, curr->subject) > 0)
        {
            prev = curr;
        }
        else
        {
            break;
        }
    }

    new->next = curr;

    if (prev == NULL)
    {
        return (new);
    }
    else
    {
        prev->next = new;
        return list;
    }
}

/**
 * Function:  peek_front
 * ---------------------
 * @brief  Allows to get the head node of the list.
 *
 * @param list The list to get the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *peek_front(node_t *list)
{
    return list;
}

/**
 * Function:  remove_front
 * -----------------------
 * @brief  Allows removing the head node of the list.
 *
 * @param list The list to remove the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *remove_front(node_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    return list->next;
}

/**
 * Function: apply
 * --------------
 * @brief  Allows to apply a function to the list.
 *
 * @param list The list (i.e., pointer to head node) where the function will be applied.
 * @param fn The pointer of the function to be applied.
 * @param arg The arguments to be applied.
 *
 */
void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for (; list != NULL; list = list->next)
    {
        (*fn)(list, arg);
    }
}
