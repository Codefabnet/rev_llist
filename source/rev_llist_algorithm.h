#include "rev_llist.h"

void insert_list(struct list_node *list_start,
            struct list_node *list_end,
            struct list_node *insert_at_node);

struct list_node *swap_nodes(struct list_node *anchor_node,
                             struct list_node *moving_node);
struct list_node *reverse_list(struct list_node *list);
