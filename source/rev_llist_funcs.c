#include "rev_llist.h"


// Functions to associate with each string node.
static
inline void func1(void) {
    printf("In %s\n", __FUNCTION__);
}

static
inline void func2(void) {
    printf("In %s\n", __FUNCTION__);
}

static
inline void func3(void) {
    printf("In %s\n", __FUNCTION__);
}

static
inline void func4(void) {
    printf("In %s\n", __FUNCTION__);
}

// string node data source arrays.
node_func_ptr node_funcs[] = {
      func1,
      func2,
      func3,
      func4,
};

char *node_strings[] = {
    "NODE_ONE",
    "NODE_TWO",
    "NODE_THREE",
    "NODE_FOUR"
};

// The list head pointer, a valid member of the list.
struct list_node *glist_head = NULL;

//*****************************************************************************
// Function: print_list
//
// Description: Print a graphical representation of each list nodes val1
//              member in list order.
//
// Parameters:  pointer to the list head for the list to print.
//
// Return: void
//
//*****************************************************************************

void print_list( struct list_node *list_head)
{

    struct list_node *list_iter = list_head;

    // Walk the list and print the int.
    while (NULL != list_iter) {
        printf("| %d ", ((struct string_node *)list_iter)->val1);
        list_iter = list_iter->next;
    }
    printf("|\n");

}

//*****************************************************************************
// Function: print_node
//
// Description: Prints the int, string and next pointer for the given list_node
//
// Parameters: list_node - Subject of the node data dump.
//
// Return: void
//
//*****************************************************************************
void print_node(const struct list_node *const list_node)
{

    if (list_node == NULL) {
        printf("%s: list_node is NULL\n", __FUNCTION__);
        return;
    }

    // Print the int and string members of the node.
    printf("%s: val1 = %d, node_string = %s\n",
           __FUNCTION__,
           ((struct string_node *)list_node)->val1,
           ((struct string_node *)list_node)->node_string);

    // Print the address of the current node and next node if not NULL.
    printf("%s: node = %p\n", __FUNCTION__, list_node);

    if (list_node->next == NULL) {
        printf("%s: list_node->next is NULL\n", __FUNCTION__);
    }
    else {
        printf("%s: next = %p\n", __FUNCTION__, list_node->next);
    }
}

//*****************************************************************************
// Function: list_node
//
// Description: Find the string node by the first occurance of the node_string
//              member.
//
// Parameters: string_to_find - Search string.
//
// Return: pointer to the first node found with the given string.
//
//*****************************************************************************
struct list_node *find_node_by_string(const char *const string_to_find)
{

    size_t string1_size = strlen(string_to_find);
    size_t string2_size;
    struct list_node *list_iter = glist_head;

    while (list_iter) {
        char *node_string = ((struct string_node *)list_iter)->node_string;
        string2_size = strlen(node_string);
        size_t min_string_size =
            string1_size > string2_size ? string2_size : string1_size;

        if (strncmp(string_to_find,
                    (const char *)node_string,
                    min_string_size) == 0) {

            print_node(list_iter);
            break;
        }
        list_iter = list_iter->next;
    }
    return list_iter;
}


//*****************************************************************************
// Function: find_node_by_val1
//
// Description: Find the string node by the first occurance of the val1 member.
//
// Parameters: val1_to_find - The search int.
//
// Return: pointer to the first node found with the given int.
//
//*****************************************************************************
struct list_node *find_node_by_val1(const int val1_to_find)
{

    struct list_node *list_iter = glist_head;

    while (list_iter) {
        if (val1_to_find == ((struct string_node *)list_iter)->val1) {
            print_node(list_iter);
            break;
        }
        list_iter = list_iter->next;
    }
    return list_iter;
}


//*****************************************************************************
// Function: append_node
//
// Description: append a node to the given list.
//
// Parameters: list - Element of the list to append to.
//             node_to_append - node to append.
//
// Return: void
//
//*****************************************************************************
void append_node(struct list_node **const list,
        struct list_node *const node_to_append)
{
    struct list_node **list_iter;

    // Return if the node to append is NULL.`
    if (NULL == node_to_append) {
        return;
    }

    // The node to append will be the new tail
    // so it's next pointer has to be NULL.
    node_to_append->next = NULL;

    // Set the list head if it's NULL
    if (*list == NULL) {
        *list = node_to_append;
        return;
    }

    // Find the first NULL next pointer on the list
    list_iter = &(*list)->next;
    while ((*list_iter) != NULL) {
        list_iter = &(*list_iter)->next;
    }

    // Append the node to the trail.
    *list_iter = node_to_append;
}

//*****************************************************************************
// Function: create_list_from_array
//
// Description: Create a linked list from an array of nodes. 
//
// Parameters: list_head - The pointer to the head of the new list.
//             list_array - The array containing the nodes used to create the
//                          new list.
//             start_index - Array index for the first node to use in the list.
//             num_elements - Number of array element to add to the list.
//
// Return: pointer to the list head.
//
//*****************************************************************************

struct list_node *create_list_from_array(struct list_node **list_head,
                                         struct string_node *list_array,
                                         uint32_t start_index,
                                         uint32_t num_elements)
{

    uint32_t node_index;

    // Index through the array, beginning at the given starting position,
    // and append the number of elements specified.
    for (node_index = start_index;
         node_index < (start_index + num_elements);
         node_index++) {
         append_node(list_head, (struct list_node *)&list_array[node_index]);
    }

    return *list_head;
}

