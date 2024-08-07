#include "node.h"

node_t *node_add_next_from_data(node_t *self, datatype_t datatype, data_t data, size_t data_sz);
node_t *node_add_next(node_t *self, node_t *other);

bool node_is_equal(node_t *self, node_t *other);
bool node_is_equal_by_data(node_t *self, datatype_t datatype, data_t data, size_t data_sz);

node_t *node_find(node_t *self, node_t *other);
node_t *node_find_by_data(node_t *self, datatype_t datatype, data_t data, size_t data_sz);

node_t *node_delete(node_t *self, node_t *other);
node_t *node_delete_by_data(node_t *self, datatype_t datatype, data_t data, size_t data_sz);

node_t *node_get_tail(node_t *self);
void node_print(node_t *self)
{
    printf("Node at address: %p", (void *)self);
    self->node_data->print(self->node_data);
    printf("Has next: %s\n", self->next ? "Yes" : "No");
}

void node_chain_print(node_t *self)
{
    while (self)
    {
        self->print(self);
        self = self->next;
    }
}

size_t node_chain_length(node_t *self)
{
    size_t count = 0;
    while (self)
    {
        count += 1;
        self = self->next;
    }
    return count;
}

void node_free(node_t *self)
{
    if (self != NULL)
    {
        if (NULL != self->node_data)
            self->node_data->free(self->node_data);

        free(self);
    }
}

void node_chain_free(node_t *self)
{
    node_t *node_tmp = NULL;
    while (self)
    {
        node_tmp = self;
        self = self->next;
        node_tmp->free(node_tmp);
    }
}

node_t *node_set(node_t *self, node_data_t *data)
{
    if (self->node_data)
        self->node_data->free(self->node_data);

    self->node_data = data;

    return self;
}

node_t *node_set_from_data(node_t *self, datatype_t datatype, data_t data, size_t data_sz)
{

    node_data_t *node_data = node_data_create(datatype, data, data_sz);
    if (node_data != NULL)
        return node_set(self, node_data);

    return self;
}

node_t *node_create(node_data_t *node_data)
{

    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (NULL == node)
    {
        node_data->free(node_data);
        return NULL;
    }

    node->next = NULL;
    node->node_data = node_data;

    node->chain_free = node_chain_free;
    node->free = node_free;

    node->print = node_print;
    node->chain_print = node_chain_print;

    node->chain_length = node_chain_length;

    node->set = node_set;
    node->set_from_data = node_set_from_data;

    node->get_tail = node_get_tail;

    node->add_next = node_add_next;
    node->add_next_from_data = node_add_next_from_data;

    node->is_equal = node_is_equal;
    node->is_equal_by_data = node_is_equal_by_data;

    node->find = node_find;
    node->find_by_data = node_find_by_data;

    node->delete = node_delete;
    node->delete_by_data = node_delete_by_data;

    return node;
}

node_t *node_create_from_data(datatype_t datatype, data_t data, size_t data_sz)
{
    node_data_t *node_data = node_data_create(datatype, data, data_sz);
    if (NULL == node_data)
        return NULL;

    return node_create(node_data);
}

node_t *node_add_next(node_t *self, node_t *other)
{
    if (self->next)
    {
        self->next->chain_free(self->next);
    }
    self->next = other;
    return other;
}

node_t *node_add_next_from_data(node_t *self, datatype_t datatype, data_t data, size_t data_sz)
{

    node_t *other = node_create_from_data(datatype, data, data_sz);
    if (!other)
        return self;

    return node_add_next(self, other);
}

bool node_is_equal(node_t *self, node_t *other)
{
    return self->node_data->is_equal(self->node_data, other->node_data);
}

bool node_is_equal_by_data(node_t *self, datatype_t datatype, data_t data, size_t data_sz)
{
    node_data_t nd = *self->node_data;
    return nd.is_equal_by_data(&nd, datatype, data, data_sz);
}

node_t *node_find(node_t *self, node_t *other)
{
    while (self)
    {
        if (self->is_equal(self, other))

            return self;

        self = self->next;
    }
    return NULL;
}

node_t *node_find_by_data(node_t *self, datatype_t datatype, data_t data, size_t data_sz)
{
    while (self)
    {
        if (self->is_equal_by_data(self, datatype, data, data_sz))

            return self;

        self = self->next;
    }
    return NULL;
}

static node_t *node_find_new_head(node_t *head, node_t *other)
{
    node_t *new_head = head, *node_tmp = NULL;
    while (new_head && new_head->is_equal(new_head, other))
    {
        node_tmp = new_head;
        new_head = new_head->next;
        node_tmp->free(node_tmp);
    }

    return new_head;
}

node_t *node_delete(node_t *self, node_t *other)
{
    node_t *new_head = node_find_new_head(self, other);

    if (new_head)
    {
        node_t *prev = new_head, *curr = NULL;

        // case 1: head is last
        if (new_head->next == NULL)
        {
            return new_head;
        }
        // case 2:
        else
        {
            curr = prev->next;
            while (curr)
            {
                if (curr->is_equal(curr, other))
                {
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
                        return new_head;
                    }
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }

    return new_head;
}
node_t *node_delete_by_data(node_t *self, datatype_t datatype, data_t data, size_t data_sz)
{
    node_t *node = node_create_from_data(datatype, data, data_sz);

    node_t *new_head = node_delete(self, node);
    node->free(node);

    return new_head;
}

node_t *node_get_tail(node_t *self)
{
    while (self)
    {
        if (self->next == NULL)
            return self;
        self = self->next;
    }
    return NULL;
}