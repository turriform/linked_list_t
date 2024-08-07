#if !defined(LOCAL_TESTS_H)
#define LOCAL_TESTS_H
#include "framework.h"
#include "linked_list.h"

void test_node_data_init()
{
    long int a = 4;
    int b = 4;
    double c = 10;
    long double d = 20;

    node_data_t *nd = node_data_create(NODE_DATA_PARAMS(a));
    assert(nd->datatype == TYPENAME_INT32);
    nd->free(nd);

    nd = node_data_create(NODE_DATA_PARAMS(b));
    assert(nd->datatype == TYPENAME_INT16);
    nd->free(nd);

    nd = node_data_create(NODE_DATA_PARAMS(c));
    assert(nd->datatype == TYPENAME_DOUBLE);
    nd->free(nd);

    nd = node_data_create(NODE_DATA_PARAMS(d));
    assert(nd->datatype == TYPENAME_LDOUBLE);
    nd->free(nd);

    // TODO: add more checks
    printf("\nData creation: PASSED\n");
}

void test_node_data_general()
{

    int a = 1, b = 2, d = 1;
    double c = 1;
    node_data_t *nd = node_data_create(NODE_DATA_PARAMS(a));
    node_data_t *ndb = node_data_create(NODE_DATA_PARAMS(b));
    node_data_t *ndc = node_data_create(NODE_DATA_PARAMS(c));
    node_data_t *ndd = node_data_create(NODE_DATA_PARAMS(d));

    assert((nd->datatype == TYPENAME_INT16 && ndb->datatype == TYPENAME_INT16));

    assert(nd->is_comparable(nd, ndb));

    assert(nd->is_comparable(nd, ndd));
    assert(nd->is_equal(nd, ndd));
    nd->is_equal(nd, ndd);

    nd->invariant(nd);
    assert(nd->datatype == TYPENAME_NONE);
    assert(nd->data == NULL);

    nd->set(nd, NODE_DATA_PARAMS(c));
    assert(nd->datatype == TYPENAME(c));

    nd->free(nd);
    ndb->free(ndb);
    ndc->free(ndc);
    ndd->free(ndd);

    printf("\nData updates: PASSED\n");
}

void test_node_init()
{
    int a = 10;
    int b = 20;
    double c = 100;
    node_t *na = node_create_from_data(NODE_DATA_PARAMS(a));
    node_t *nb = node_create_from_data(NODE_DATA_PARAMS(b));
    node_t *nc = node_create_from_data(NODE_DATA_PARAMS(c));

    assert(na->node_data->datatype == TYPENAME(a));
    na->set_from_data(na, NODE_DATA_PARAMS(c));
    assert(na->node_data->datatype == TYPENAME(c));

    na->free(na);
    nc->free(nc);
    nb->free(nb);

    printf("\nNode updates: PASSED\n");
}

void test_node_addition()
{
    int a = 10;
    int b = 20;
    double c = 100;
    node_t *na = node_create_from_data(NODE_DATA_PARAMS(a));
    node_t *nb = node_create_from_data(NODE_DATA_PARAMS(b));
    node_t *nc = node_create_from_data(NODE_DATA_PARAMS(c));

    na->add_next(na, nb);
    assert(na->chain_length(na) == 2);

    na->add_next(na, nc);
    assert(na->chain_length(na) == 2);

    // freeing all nodes
    na->chain_free(na);

    na = node_create_from_data(NODE_DATA_PARAMS(a));

    nb = na->add_next_from_data(na, NODE_DATA_PARAMS(b));

    nb->add_next_from_data(nb, NODE_DATA_PARAMS(c));

    assert(na->chain_length(na) == 3);

    na->chain_free(na);

    printf("\nNode addition: PASSED\n");
}

void test_node_actions()
{
    /*  1)equality check
        2)search
    */

    long int a = 10, b = 100, c = 2;

    node_t *na = node_create_from_data(NODE_DATA_PARAMS(a));
    node_t *nb = node_create_from_data(NODE_DATA_PARAMS(b));
    node_t *nc = node_create_from_data(NODE_DATA_PARAMS(c));

    assert(na->is_equal_by_data(na, NODE_DATA_PARAMS(a)));
    assert(!na->is_equal(na, nb));

    na->free(na);
    nb->free(nb);
    nc->free(nc);

    long double x = 10, y = 100, z = 2;

    na = node_create_from_data(NODE_DATA_PARAMS(x));
    nb = node_create_from_data(NODE_DATA_PARAMS(y));
    nc = node_create_from_data(NODE_DATA_PARAMS(z));

    na->add_next(na, nb);
    nb->add_next(nb, nc);

    assert(na->chain_length(na) == 3);

    node_t *found_node = na->find(na, nb);

    assert(nb->is_equal(nb, found_node));

    node_t *found_node_by_data = na->find_by_data(na, NODE_DATA_PARAMS(z));
    assert(nc->is_equal(nc, found_node_by_data));
    assert(nc->is_equal_by_data(nc, NODE_DATA_PARAMS(z)));

    na->chain_free(na);
    printf("\nNode search: PASSED\n");
}

void test_node_deletion()
{
    int nums[] = {1, 2, 3, 4, 5};
    size_t nums_sz = 5;
    node_t *head = node_create_from_data(NODE_DATA_PARAMS(nums[0]));
    node_t *head_tmp = head;
    for (size_t i = 1; i != nums_sz; i++)
    {
        head_tmp->add_next_from_data(head_tmp, NODE_DATA_PARAMS(nums[i]));
        head_tmp = head_tmp->next;
    }

    assert(head->chain_length(head) == nums_sz);

    node_t *new_head = head->delete_by_data(head, NODE_DATA_PARAMS(nums[0]));

    // deleting first element in chain -- head doesn't exist anymore

    assert(new_head->chain_length(new_head) == (nums_sz - 1));

    if (new_head)
        new_head->chain_free(new_head);

    double nums2[] = {1, 1, 1, 1, 1, 1, 2};
    size_t i = 1;
    size_t mums2_sz = sizeof(nums2) / sizeof(*nums2);
    head = node_create_from_data(NODE_DATA_PARAMS(nums2[0]));
    head_tmp = head;
    while (i++ != (mums2_sz - 1))
    {
        head_tmp->add_next_from_data(head_tmp, NODE_DATA_PARAMS(nums2[i]));
        head_tmp = head_tmp->next;
    }

    double tail_val = *(double *)head->get_tail(head)->node_data->data;
    assert(tail_val == 2);

    new_head = head->delete_by_data(head, NODE_DATA_PARAMS(nums2[0]));
    assert(new_head->chain_length(new_head) == 1);

    if (new_head)
        new_head->chain_free(new_head);

    double nums3[] = {1, 1, 1, 1, 1, 1};
    size_t mums3_sz = sizeof(nums3) / sizeof(*nums3);

    head = node_create_from_data(NODE_DATA_PARAMS(nums3[0]));
    i = 1;
    head_tmp = head;
    while (i++ != (mums3_sz - 1))
    {
        head_tmp->add_next_from_data(head_tmp, NODE_DATA_PARAMS(nums3[i]));
        head_tmp = head_tmp->next;
    }
    // this should find and delete all elements in a chain
    new_head = head->delete_by_data(head, NODE_DATA_PARAMS(nums3[0]));

    printf("\nNode deletion: PASSED\n");
}

void test_linked_list_init()
{
    long double nums[] = {1, 2, 1, 4};

    linked_list_t *ll = linked_list_create();
    ll->set_head(ll, node_create_from_data(NODE_DATA_PARAMS(nums[0])));
    assert(ll->nmem == 1);
    ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(nums[3])));
    assert(ll->nmem == 2);

    // ll->head->chain_print(ll->head);
    ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(nums[1])));
    assert(ll->nmem == 3);

    ll->pop(ll);
    assert(ll->nmem == 2);

    ll->free(ll);

    printf("\nLinked List pop: PASSED\n");
}

void test_linked_list_push()
{
    long double nums[] = {1, 2, 1, 4};
    linked_list_t *ll = linked_list_create();
    ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(nums[0])));

    // head is now updated
    ll->set_head(ll, node_create_from_data(NODE_DATA_PARAMS(nums[1])));
    assert(ll->nmem == 1);

    long int nums_i[] = {1, 3, 4, 6, 7};
    size_t n_sz = sizeof(nums_i) / sizeof(*nums_i);
    for (size_t i = 0; i != n_sz; i++)
    {
        ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(nums_i[i])));
    }

    assert(ll->nmem == (n_sz + 1));

    // ll->head->chain_print(ll->head);

    ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(nums[2])));
    ll->free(ll);

    printf("\nLinked List push: PASSED\n");
}

void test_linked_list_delete()
{
    // deleting first 3
    char arr[] = {'a', 'a', 'a', 'd', 'e'};
    linked_list_t *ll = linked_list_create();
    ll->set_head(ll, node_create_from_data(NODE_DATA_PARAMS(arr[0])));
    size_t arr_sz = sizeof(arr) / sizeof(*arr);
    for (size_t i = 1; i != arr_sz; i++)
        ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(arr[i])));
    assert(ll->nmem == 5);
    ll->delete_by_data(ll, NODE_DATA_PARAMS(arr[0]));
    assert(ll->nmem == 2);
    ll->free(ll);

    // deleting all
    char arr2[] = {'a', 'a', 'a', 'a'};
    ll = linked_list_create();
    ll->set_head(ll, node_create_from_data(NODE_DATA_PARAMS(arr2[0])));
    arr_sz = sizeof(arr2) / sizeof(*arr2);

    for (size_t i = 1; i != arr_sz; i++)
        ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(arr2[i])));

    ll->delete_by_data(ll, NODE_DATA_PARAMS(arr2[0]));
    assert(ll->nmem == 0);

    ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(arr2[0])));
    assert(ll->nmem == 1);

    ll->pop(ll);
    assert(ll->nmem == 0);

    ll->delete_by_data(ll, NODE_DATA_PARAMS(arr2[0]));

    ll->free(ll);

    printf("\nLinked List delete: PASSED\n");
}

inline static bool is_even(node_t *a) { return *(int *)(a->node_data->data) % 2; }

void test_linked_list_filter()
{
    int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t nums_sz = sizeof(nums) / sizeof(*nums);
    linked_list_t *ll = linked_list_create();
    ll->set_head(ll, node_create_from_data(NODE_DATA_PARAMS(nums[0])));
    for (size_t i = 1; i != nums_sz; i++)
        ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(nums[i])));

    assert(ll->nmem == nums_sz);
    ll->filter(ll, is_even);
    assert(ll->nmem == (size_t)nums_sz / 2);

    ll->free(ll);

    // removing all
    int nums2[] = {1, 1, 1, 1};
    nums_sz = sizeof(nums2) / sizeof(*nums2);
    ll = linked_list_create();
    ll->set_head(ll, node_create_from_data(NODE_DATA_PARAMS(nums2[0])));
    for (size_t i = 1; i != nums_sz; i++)
        ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(nums2[i])));
    assert(ll->nmem == 4);
    ll->filter(ll, is_even);
    assert(ll->nmem == 0);

    ll->free(ll);

    printf("\nLinked List filter: PASSED\n");
}

void test_init()
{
    /*
        1) initializes linked list
        2) fills linked list
        3) filters linked list
        4) frees linked list

    */

    long int data[] = {4, 8, 15, 16, 23, 42};
    size_t data_length = sizeof(data) / sizeof(*data);

    linked_list_t *ll = linked_list_create();
    // 1 -- adding initial elements to the linked_list
    // ll->push is add_element equivelent from asm code
    
    // O(n^2)
    //  for (size_t i = 0; i != data_length; i++)
    //      ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(data[i])));

    // 0(n)
    node_t *tail = node_create_from_data(NODE_DATA_PARAMS(data[0]));
    ll->set_head(ll, tail);
    for (size_t i = 1; i != data_length; i++)
    {
        tail->add_next(tail, node_create_from_data(NODE_DATA_PARAMS(data[i])));
        tail = tail->next;
    }

    // m - takes print_int to display int
    // chain_print is print equivelent from asm code

    ll->head->chain_print(ll->head);
    /*
        f - filter function equivelent
        p - is_even function equivelent
        long int p(long int value) {
        return value & 1;}
    */
    ll->filter(ll, is_even);

    ll->head->chain_print(ll->head);

    // frees linked list
    ll->free(ll);
}

void run_tests()
{
    test_node_data_init();
    test_node_data_general();
    test_node_init();
    test_node_addition();
    test_node_actions();
    test_node_deletion();
    test_linked_list_init();
    test_linked_list_push();
    test_linked_list_delete();
    test_linked_list_filter();
    test_init();
    printf("\nAll Tests: PASSED\n");
}

#endif // LOCAL_TESTS_H
