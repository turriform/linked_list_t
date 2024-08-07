#if !defined(L_NODE_DATA_H)
#define L_NODE_DATA_H
#include "framework.h"
struct NodeData
{
    datatype_t datatype;
    data_t data;
    size_t data_sz;

    node_data_t *(*invariant)(node_data_t *self);
    node_data_t *(*set)(node_data_t *self, datatype_t datatype, data_t data, size_t data_sz);

    bool (*is_equal)(node_data_t *self, node_data_t *other);
    bool (*is_equal_by_data)(node_data_t *self, datatype_t datatype, data_t data, size_t data_sz);

    
    bool (*is_comparable)(node_data_t *self, node_data_t *other);
    void (*print)(node_data_t *self);

    void (*free)(node_data_t *self);
};

node_data_t *node_data_create(datatype_t datatype, data_t data, size_t data_sz);

#endif // L_NODE_DATA_H
