#include "node_data/node_data.h"

/*
    to mantain additional datatypes edit:
    "node_data/node_data.h"

    fn      node_data_value_equality()
    fn      node_data_print()

    "framework.h"

    enum    Typename
    macro   TYPENAME(x)

    TODO: think of something better later

*/

void node_data_free(node_data_t *self)
{
    if (self != NULL)
    {
        if (self->data != NULL)
            free(self->data);

        free(self);
    }
    self = NULL;
}

node_data_t *node_data_set(node_data_t *self, datatype_t datatype, data_t data, size_t data_sz)
{

    if (self != NULL)
    {
        self->invariant(self);
    }
    self->data = malloc(data_sz);
    memcpy(self->data, data, data_sz);

    self->data_sz = data_sz;
    self->datatype = datatype;
    return self;
}

bool node_data_comparable(node_data_t *self, node_data_t *other)
{
    return (self->datatype == other->datatype);
}

static bool node_data_value_equality(datatype_t datatype, data_t first, data_t second)
{
    switch (datatype)
    {
    case TYPENAME_INT8:
        return *(dt_int8 *)first == *(dt_int8 *)second;
    case TYPENAME_INT16:
        return *(dt_int16 *)first == *(dt_int16 *)second;
    case TYPENAME_INT32:
        return *(dt_int32 *)first == *(dt_int32 *)second;
    case TYPENAME_UINT8:
        return *(dt_uint8 *)first == *(dt_uint8 *)second;
    case TYPENAME_UINT16:
        return *(dt_uint16 *)first == *(dt_uint16 *)second;
    case TYPENAME_UINT32:
        return *(dt_uint32 *)first == *(dt_uint32 *)second;
    case TYPENAME_DOUBLE:
        return *(dt_double *)first == *(dt_double *)second;
    case TYPENAME_LDOUBLE:
        return *(dt_ldouble *)first == *(dt_ldouble *)second;
    case TYPENAME_CHAR:
        return *(dt_char *)first == *(dt_char *)second;
    case TYPENAME_UCHAR:
        return *(dt_uchar *)first == *(dt_uchar *)second;
    default:
        return false;
    }
    return false;
}

bool node_data_is_equal(node_data_t *self, node_data_t *other)
{

    if (self->is_comparable(self, other))
    {

        return node_data_value_equality(self->datatype, self->data, other->data);
    }

    return false;
}

bool node_data_is_equal_by_data(node_data_t *self, datatype_t datatype, data_t data, size_t data_sz)
{
    if (self->datatype != datatype)
        return false;

    if (self->data_sz == data_sz)
        return node_data_value_equality(self->datatype, self->data, data);
    return false;
}

node_data_t *node_data_invariant(node_data_t *self)
{
    /* set data to the default state*/
    if (NULL != self)
    {
        if (self->data != NULL)
        {
            free(self->data);
        }
        self->data = NULL;
        self->datatype = TYPENAME_NONE;
        self->data_sz = 0;
    }
    return self;
}

void node_data_print(node_data_t *self)
{
    printf("\nNodeData at address: %p, \n\tValue is: ", (void *)self);
    switch (self->datatype)
    {
    case TYPENAME_INT8:
        printf("%d\n", *(dt_int8 *)self->data);
        break;
    case TYPENAME_INT16:
        printf("%d\n", *(dt_int16 *)self->data);
        break;
    case TYPENAME_INT32:
        printf("%ld\n", *(dt_int32 *)self->data);
        break;
    case TYPENAME_UINT8:
        printf("%d\n", *(dt_uint8 *)self->data);
        break;
    case TYPENAME_UINT16:
        printf("%d\n", *(dt_uint16 *)self->data);
        break;
    case TYPENAME_UINT32:
        printf("%ld\n", *(dt_uint32 *)self->data);
        break;

    case TYPENAME_DOUBLE:
        printf("%.2f\n", *(dt_double *)self->data);
        break;
    case TYPENAME_LDOUBLE:
        printf("%.2Lf\n", *(dt_ldouble *)self->data);
        break;
    case TYPENAME_CHAR:
        printf("%c\n", *(dt_char *)self->data);
        break;
    case TYPENAME_UCHAR:
        printf("%c\n", *(dt_uchar *)self->data);
        break;

    default:
        printf("NONE\n");
        break;
    }
    printf("\tThe type is %d\n", self->datatype);
    printf("\tThe size is %ld\n", self->data_sz);
}

node_data_t *node_data_create(datatype_t datatype, data_t data, size_t data_sz)
{
    node_data_t *node_data = (node_data_t *)malloc(sizeof(node_data_t));
    if (NULL == node_data)
        return NULL;

    node_data->data = malloc(data_sz);
    if (NULL == node_data->data)
        return NULL;

    memcpy(node_data->data, data, data_sz);

    node_data->data_sz = data_sz;
    node_data->datatype = datatype;

    node_data->invariant = node_data_invariant;
    node_data->set = node_data_set;

    node_data->is_equal = node_data_is_equal;
    node_data->is_equal_by_data = node_data_is_equal_by_data;

    node_data->print = node_data_print;
    node_data->is_comparable = node_data_comparable;

    node_data->free = node_data_free;
    return node_data;
}

// static bool node_data_compare(node_data_t *self, node_data_t *other, bool (*comparator)(node_data_t *, node_data_t *))
// {
//     if (node_data_comparable(self, other))
//     {
//         return comparator(self, other);
//     }
//     return false;
// }
