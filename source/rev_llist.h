#if !defined(__REV_LLIST_H__)
#define __REV_LLIST_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>


//--------------------------------------------------
// Use list_node to manipulate the lists.
// Cast to string_node to access the string list data.
//--------------------------------------------------

struct list_node {
    struct list_node *next;
};

extern struct list_node *glist_head;

typedef void(*node_func_ptr)(void);

// String list data consists of an int, a string
// and a function pointer for a given string node.
struct string_node {
    struct list_node *node;
    int val1;
    char *node_string;
    node_func_ptr node_func;
};

// Enum to index array of string nodes,
// separate from the linked list.
enum {
    FIRST_NODE_STRING = 0,
    NODE_ONE = FIRST_NODE_STRING,
    NODE_TWO,
    NODE_THREE,
    NODE_FOUR,
    NUM_NODE_STRINGS,
    LAST_NODE_STRING = NUM_NODE_STRINGS - 1
};

// Keeps the screen from scrolling for the given delay.
static inline void pause_display_output(int delay)
{
    for (int i = 0; i < delay; i++) {
        putchar('.');
        fflush(stdout);
        sleep(1);
    }
}

// string node data source arrays.
extern node_func_ptr node_funcs[];
extern char *node_strings[];

void print_list(struct list_node *list_head);
void print_node(const struct list_node *const list_node);
struct list_node *find_node_by_string(const char *const string_to_find);
void append_node(struct list_node **const list,
                 struct list_node *const node_to_append);

struct list_node *find_node_by_val1(const int val1_to_find);

struct list_node *create_list_from_array(struct list_node **list_head,
                                 struct string_node *list_array,
                                 uint32_t start_index,
                                 uint32_t num_elements);
#endif // !defined(__REV_LLIST_H__)
