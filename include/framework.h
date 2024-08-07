#if !defined(L_FRAMEWORK_H)
#define L_FRAMEWORK_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

// for test
void run_tests(void);


enum Typename
{
    TYPENAME_NONE,

    TYPENAME_INT8,
    TYPENAME_INT16,
    TYPENAME_INT32,
    TYPENAME_UINT8,
    TYPENAME_UINT16,
    TYPENAME_UINT32,

    TYPENAME_DOUBLE,
    TYPENAME_LDOUBLE,

    TYPENAME_CHAR,
    TYPENAME_UCHAR,

    TYPENAME_STRING
};

enum DataStatus
{
    DATA_CREATED,
    DATA_FREED,
    DATA_ERR
};

#define TYPENAME(x) _Generic((x), \
    dt_int8: TYPENAME_INT8,       \
    dt_int16: TYPENAME_INT16,     \
    dt_int32: TYPENAME_INT32,     \
    dt_uint8: TYPENAME_UINT8,     \
    dt_uint16: TYPENAME_UINT16,   \
    dt_uint32: TYPENAME_UINT32,   \
    dt_double: TYPENAME_DOUBLE,   \
    dt_ldouble: TYPENAME_LDOUBLE, \
    dt_char: TYPENAME_CHAR,       \
    dt_uchar: TYPENAME_UCHAR)

#define REALTYPE(type, data) (*((TYPENAME(type)) *)&(data))

// #define NODE_DATA_PARAMS(x) TYPENAME((x)), (void *)(&(x))

// #define LL_DATA_PARAMS(x) (TYPENAME((*x))), (void *)(&(x)), (size_t)(sizeof((x)) / sizeof((*x))), (size_t)sizeof((*x))

/* Data types definitions */

typedef struct      NodeData            node_data_t;
typedef enum        Typename            datatype_t;
typedef void *                          data_t;

// Node

typedef struct      Node                node_t;
typedef struct      LinkedList          linked_list_t;


// datatypes for macro

typedef short int                       dt_int8;
typedef int                             dt_int16;
typedef long int                        dt_int32;
typedef long long int                   dt_int64;
typedef unsigned short int              dt_uint8;
typedef unsigned int                    dt_uint16;
typedef unsigned long int               dt_uint32;
typedef unsigned long long int          dt_uint64;

typedef double                          dt_double;
typedef long double                     dt_ldouble;

typedef char                            dt_char;
typedef unsigned char                   dt_uchar;

#define NODE_DATA_PARAMS(x) TYPENAME((x)), (data_t)(&(x)), sizeof((x))

#define LL_DATA_PARAMS(x) (TYPENAME((*x))), (data_t)((x)), (size_t)(sizeof((x)) / sizeof((*x))), (size_t)sizeof((*x))

#define NODE_DATA_TYPE_CONVERT(type, data) (*type *)(data)



#endif // L_FRAMEWORK_H
