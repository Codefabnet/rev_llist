#include "rev_llist.h"
#include "rev_llist_algorithm.h"

int main(void)
{
    uint32_t node_index = FIRST_NODE_STRING;

    // Create an array of nodes, such that no mallocs are required
    // and the order of nodes is not changed.
    struct string_node node_array[NUM_NODE_STRINGS] = {
        {
         .val1 = NODE_ONE,
         .node_string = node_strings[NODE_ONE],
         .node_func = node_funcs[NODE_ONE]
        },
        {
         .val1 = NODE_TWO,
         .node_string = node_strings[NODE_TWO],
         .node_func = node_funcs[NODE_TWO]
        },
        {
         .val1 = NODE_THREE,
         .node_string = node_strings[NODE_THREE],
         .node_func = node_funcs[NODE_THREE]
        },
        {
         .val1 = NODE_FOUR,
         .node_string = node_strings[NODE_FOUR],
         .node_func = node_funcs[NODE_FOUR]
        }
    };

    // Build a linked list of nodes from the existing array.
    struct list_node *iter_node = NULL;
    create_list_from_array(&glist_head,
                           node_array,
                           FIRST_NODE_STRING,
                           NUM_NODE_STRINGS);

    printf("\n\n\n\n");

    printf( \
    "-------------------------------------------------------------------\n"
    "// Print the array elements in the order they appear in the array.\n"
    "// The address of each node and the corresponding next node is\n"
    "// printed, indicating the original list order.\n"
    "-------------------------------------------------------------------\n" \
    );
    for (node_index = FIRST_NODE_STRING;
         node_index <= LAST_NODE_STRING;
         node_index++) {

        printf("node %p, val1 = %d, node_string = %s\n\n",
               find_node_by_val1(node_array[node_index].val1),
               node_array[node_index].val1,
               node_array[node_index].node_string);
    }

    pause_display_output(5);

    printf("\n\n\n\n");

    // Reverse the order of nodes in the linked list.
    glist_head = reverse_list(glist_head);

    printf( \
    "-------------------------------------------------------------------\n"
    "// Print the array elements in the order they appear in the array.\n"
    "// The address of each node and the corresponding next node is\n"
    "// printed, indicating the reversed list order.\n"
    "-------------------------------------------------------------------\n" \
    );
    for (node_index = FIRST_NODE_STRING;
         node_index <= LAST_NODE_STRING;
         node_index++) {

        printf("node %p, val1 = %d, node_string = %s\n\n",
               find_node_by_val1(node_array[node_index].val1),
               node_array[node_index].val1,
               node_array[node_index].node_string);
    }

    pause_display_output(5);
    printf("\n\n\n\n");


    printf( \
    "----------------------------------------------------------------------\n"
    "// Print the linked list after it's order of nodes has been reversed.\n"
    "----------------------------------------------------------------------\n" \
    );
    iter_node = glist_head;
    while (iter_node) {
        print_node(iter_node);
        ((struct string_node *)iter_node)->node_func();
        printf("\n");
        iter_node = iter_node->next;
    }

    pause_display_output(5);
    printf("\n\n\n\n");

    printf( \
    "--------------------------------------------------------------\n"
    "// Locate by string and by val1, two arbitrary list nodes.\n"
    "--------------------------------------------------------------\n" \
    );
    printf("find string %s\n", node_strings[NODE_TWO]);
    find_node_by_string(node_strings[NODE_TWO]);
    printf("\nfind val1  NODE_THREE\n");
    find_node_by_val1(NODE_THREE);

}



