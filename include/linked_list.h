#if !defined(L_LINKED_LIST_T)
#define L_LINKED_LIST_T
#include "framework.h"
#include "node.h"
struct LinkedList
{
    size_t nmem;
    node_t *head;

    linked_list_t *(*set_head)(linked_list_t *self, node_t *head);
    void (*free)(linked_list_t *self);

    node_t *(*push)(linked_list_t *self, node_t *node);
    void (*pop)(linked_list_t *self);

    linked_list_t *(*delete_by_data)(linked_list_t *self, datatype_t datatype, data_t data, size_t data_sz);

    linked_list_t *(*filter)(linked_list_t *self, bool (*condition)(node_t *));
};

linked_list_t *linked_list_create();


#endif // L_LINKED_LIST_T
