#if !defined(L_NODE_H)
#define L_NODE_H
#include "framework.h"
#include "node_data/node_data.h"

struct Node
{
    node_data_t *node_data;
    node_t *next;

    void (*free)(node_t *self);
    void (*chain_free)(node_t *self);
    void (*print)(node_t *self);
    void (*chain_print)(node_t *self);

    size_t (*chain_length)(node_t *self);

    node_t *(*set)(node_t *self, node_data_t *data);
    node_t *(*set_from_data)(node_t *self, datatype_t datatype, data_t data, size_t data_sz);

    node_t *(*get_tail)(node_t *self);

    node_t *(*add_next)(node_t *self, node_t *other);
    node_t *(*add_next_from_data)(node_t *self, datatype_t datatype, data_t data, size_t data_sz);

    bool (*is_equal)(node_t *self, node_t *other);
    bool (*is_equal_by_data)(node_t *self, datatype_t datatype, data_t data, size_t data_sz);

    node_t *(*find)(node_t *self, node_t *other); // return found or null
    node_t *(*find_by_data)(node_t *self, datatype_t datatype, data_t data, size_t data_sz);

    node_t *(*delete)(node_t *self, node_t *other);
    node_t *(*delete_by_data)(node_t *self, datatype_t datatype, data_t data, size_t data_sz);

  
};

node_t *node_create(node_data_t *node_data);
node_t *node_create_from_data(datatype_t datatype, data_t data, size_t data_sz);

#endif
