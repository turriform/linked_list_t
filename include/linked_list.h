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
    // linked_list_t *(*map)(linked_list_t *self, void (*action)(node_t *));
};
void linked_list_free(linked_list_t *self);
linked_list_t *linked_list_set_head(linked_list_t *self, node_t *head);

linked_list_t *linked_list_filter(linked_list_t *self, bool (*condition)(node_t *));

linked_list_t *linked_list_delete_by_data(linked_list_t *self, datatype_t datatype, data_t data, size_t data_sz)
{
    if (NULL == self->head)
    {
        return self;
    }
    node_t *head_tmp = self->head;
    node_t *new_head = head_tmp->delete_by_data(head_tmp, datatype, data, data_sz);
    if (NULL == new_head)
    {
        self->head = NULL;
        self->nmem = 0;
        return self;
    }
    self->head = new_head;
    self->nmem = self->head->chain_length(self->head);

    return self;
}

node_t *linked_list_push(linked_list_t *self, node_t *node)
{
    /*
        pushes new node to the chain
        recalculates new chain length
        returns pushed node
    */

    if (self->head == NULL)
    {
        self->head = node;
        self->nmem = self->head->chain_length(self->head);
        return self->head;
    }

    node_t *tail = self->head->get_tail(self->head);

    if (tail)
    {
        tail->add_next(tail, node);
        self->nmem = self->head->chain_length(self->head);
        return tail->next;
    }
    return NULL;
}

void linked_list_pop(linked_list_t *self)
{
    /*
        removes last node
     */
    if (self->head == NULL)
        return;

    if (self->head->next == NULL)
    {
        self->head->free(self->head);
        self->head = NULL;
        self->nmem = 0;
        return;
    }

    node_t *prev = self->head, *last = self->head->next;
    while (last->next)
    {
        prev = last;
        last = prev->next;
    }
    last->chain_free(last);

    prev->next = NULL;

    self->nmem -= 1;
}

linked_list_t *linked_list_create()
{
    /*
    Initializes empty list
    */

    linked_list_t *ll = (linked_list_t *)malloc(sizeof(linked_list_t));
    if (NULL == ll)
        return NULL;
    ll->nmem = 0;
    ll->head = NULL;

    ll->set_head = linked_list_set_head;
    ll->free = linked_list_free;

    ll->push = linked_list_push;
    ll->pop = linked_list_pop;

    ll->delete_by_data = linked_list_delete_by_data;

    ll->filter = linked_list_filter;
    return ll;
}

linked_list_t *linked_list_set_head(linked_list_t *self, node_t *head)
{
    /*
        Frees old chain, setting new head
        recalculates length
        returns linked_list_t
    */
    if (self->head != NULL)
        self->head->chain_free(self->head);
    self->head = head;
    self->nmem = head->chain_length(head);
    return self;
}

void linked_list_free(linked_list_t *self)
{
    if (NULL != self)
    {
        if (NULL != self->head)
        {
            self->head->chain_free(self->head);
        }
        free(self);
    }
}

static node_t *linked_list_filter_new_head(node_t *head, bool (*condition)(node_t *))
{

    node_t *new_head = head, *node_tmp = NULL;
    while (new_head && condition(new_head))
    {
        node_tmp = new_head;
        new_head = new_head->next;
        node_tmp->free(node_tmp);
    }

    return new_head;
}

linked_list_t *linked_list_filter(linked_list_t *self, bool (*condition)(node_t *))
{
    node_t *new_head = linked_list_filter_new_head(self->head, condition);
    self->head = new_head;

    if (NULL == new_head)
    {
        self->nmem = 0;
        return self;
    }
    self->nmem = self->head->chain_length(self->head);

    if (new_head)
    {
        node_t *prev = new_head, *curr = NULL;

        // case 1: head is last
        if (new_head->next == NULL)
        {
            return self;
        }
        // case 2:
        else
        {
            curr = prev->next;
            while (curr)
            {
                if (condition(curr))
                {
                    self->nmem -= 1;
                    if (curr->next)
                    {
                        prev->next = curr->next;
                        curr->free(curr);
                        curr = prev;
                    }
                    else
                    {
                        curr->free(curr);
                        prev->next = NULL;
                        return self;
                    }
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }
    return self;
}

#endif // L_LINKED_LIST_T
