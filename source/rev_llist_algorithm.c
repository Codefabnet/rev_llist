#include "rev_llist.h"

//
// Swinging gate, linked list reversal algorithm
// Moving node (gate), initialized to list_head.
// Anchor node (post), initialed to list_head->next.
//
// | 1 | 2 | 3 | 4 | 5 | 6 |
// | M | A |   | 3 | 4 | 5 | 6 |
//   ^       ^
//   |_______|   Insert the movable sublist past the anchor -------------------*
//                                                                             |
// | 2 | 1 | 3 | 4 | 5 | 6 |                                                   |
// | A | M |   |   |   |   |<--------------------------------------------------*
//
//
//   M = A, A = end->next
//   The movable sublist starts at the previous anchor,
//   grows by 1, because the new anchor is 1 past the old sublist.
//
// | 2 | 1 | 3 | 4 | 5 | 6 |
// | M | - | A |   |   | 4 | 5 | 6 |
//   ^   ^       ^   ^
//   |___|_______|___|  Insert the movable sublist past the anchor ------------*
//                                                                             |
// | 3 | 2 | 1 | 4 | 5 | 6 |                                                   |
// | A | M | - |   |   |   |<--------------------------------------------------*
//
//
//   M = A, A = end->next
//   The movable sublist starts at the previous anchor,
//   grows by 1, because the new anchor is 1 past the old sublist.
//
// | 3 | 2 | 1 | 4 | 5 | 6 |
// | M | - | - | A |   |   |   | 5 | 6 |
//   ^   ^   ^       ^   ^   ^
//   |___|___|_______|___|___| Insert the movable sublist past the anchor -----*
//                                                                             |
// | 4 | 3 | 2 | 1 | 5 | 6 |                                                   |
// | A | M | - | - |   |   |<--------------------------------------------------*
//
//
//   M = A, A = end->next
//   The movable sublist starts at the previous anchor,
//   grows by 1, because the new anchor is 1 past the old sublist.
//
// | 4 | 3 | 2 | 1 | 5 | 6 |
// | M | - | - | - | A |   |   |   |   | 6 |
//   ^   ^   ^   ^       ^   ^   ^   ^
//   |___|___|___|_______|___|___|___| Insert the sublist past the anchor -----*
//                                                                             |
// | 5 | 4 | 3 | 2 | 1 | 6 |                                                   |
// | A | M | - | - | - |   |<--------------------------------------------------*
//
//
//   M = A, A = end->next
//   The movable sublist starts at the previous anchor,
//   grows by 1, because the new anchor is 1 past the old sublist.
//
// | 5 | 4 | 3 | 2 | 1 | 6 |
// | M | - | - | - | - | A |   |   |   |   |   |
//   ^   ^   ^   ^   ^       ^   ^   ^   ^   ^
//   |___|___|___|___|_______|___|___|___|___| Insert the sublist -------------*
//                                                                             |
// | 6 | 5 | 4 | 3 | 2 | 1 |                                                   |
// | A | M | - | - | - | - |<--------------------------------------------------*
//


//*****************************************************************************
// Function: insert_list
//
// Description: Insert a list of nodes into another list at the given node.
//
// Parameters: list_start - The head of the list to insert.
//             list_end   - The tail of the list to insert.
//             insert_at_node - The position in the list to insert the new
//                              list.
//
// Return: void
//
//*****************************************************************************
void insert_list(struct list_node *list_start,
                 struct list_node *list_end,
                 struct list_node *insert_at_node)
{

    struct list_node *next_node;

    if (NULL == list_start ||
        NULL == list_end   ||
        NULL == insert_at_node) {
        // TODO add check that list_end is linked to list_start.
        return;
    }
    next_node = insert_at_node->next;
    insert_at_node->next = list_start;
    list_end->next = next_node;
}

//*****************************************************************************
// Function: swap_nodes
//
// Description: Exchanges postion between a sublist of one or more nodes and the
//              the given anchor node. The sublist is defined by the moving_node
//              as the head and the last node for which next is the anchor_node.
//
// Parameters: anchor_node - The node immediately following the sublist to move.
//      
//             moving_node - The head of the sublist to move.
//
// Return: Pointer to the new anchor node or NULL if end of list is reached.
//
//*****************************************************************************
struct list_node *swap_nodes(struct list_node *anchor_node,
                             struct list_node *moving_node)
{
    struct list_node *end_node;

    if (NULL == anchor_node ||
        NULL == moving_node) {
        return NULL;
    }

    // Start at the head of the list and search for the end.
    end_node = moving_node;

    // Increment end_node until next points to the anchor.
    while (NULL != end_node->next &&
           end_node->next != anchor_node) {
        end_node = end_node->next;
    }

    // the list defined by moving and end nodes is inesrted
    // between the anchor node and it's next node.
    insert_list(moving_node, end_node, anchor_node);
    
    // After the list insert, end_node exchanges position with
    // the anchor node, and next points to the next undisturbed
    // list node, used as the new anchor_node.
    return end_node->next;
}

//*****************************************************************************
// Function: reverse_list
//
// Description: Reverses a  linked list of nodes.
//
// Parameters: list - The list of singularly linked nodes
//
// Return: The new list head of the reversed linked list.
//
//*****************************************************************************
struct list_node *reverse_list(struct list_node *list)
{
    struct list_node *anchor_node;
    struct list_node *moving_node;
    struct list_node *temp_node;

    printf("%s: %p\n", __FUNCTION__, list);

    if (NULL == list ||
        NULL == list->next) {
        return list;
    }

    // First swap begins with a single node moving sublist,
    // at the original list head, and the anchor at the head
    // next position.
    anchor_node = list->next;
    moving_node = list;

    print_list(moving_node);
    while (anchor_node) {
        // anchor is saved to be used as the moving node
        // in the next iteration.
        temp_node = anchor_node;

        // anchor returned from the swap funtion is acually 
        // the next member of the previous anchor.
        anchor_node = swap_nodes(anchor_node, moving_node);

        // New moving node is previous anchor.
        moving_node = temp_node;
        print_list(moving_node);
    }
    return moving_node;
}
