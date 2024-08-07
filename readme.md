NodeData node_data_t 

public:
```
node_data_t *node_data_create(datatype_t datatype, data_t data, size_t data_sz);
```
params usage example:

```
int x = 10;
node_data_t *nd = node_data_create(NODE_DATA_PARAMS(x))
```

private:

```
nd->free(node_data_t *)
```
frees node_data_t
```
nd->invariant(node_data_t *)
```
sets node_data_t to the default state

Node


Linked List
```
linked_list_t * ll = linked_list_init();
```
Creates empty linked list. Head can be set in 2 ways:
```
ll->set_head(node_t *);
```
by setting head
```
ll->push(node_t *)
```
by pushing node

Simple usage O(n^2):

```
long int arr[] = {1, 2, 3, 4, 5};
size_t arr_sz = sizeof(arr) / sizeof(*arr);

linked_list_t *ll = linked_list_create();

for (size_t i = 0; i != arr_sz; i++)
    ll->push(ll, node_create_from_data(NODE_DATA_PARAMS(arr[i])));

ll->free(ll);

```

O(n)

```

long int arr[] = {1, 2, 3, 4, 5};
size_t arr_sz = sizeof(arr) / sizeof(*arr);

node_t *tail = node_create_from_data(NODE_DATA_PARAMS(arr[0]));

ll->set_head(ll, tail);

for (size_t i = 1; i != arr_sz; i++)
{
    tail->add_next(tail, node_create_from_data(NODE_DATA_PARAMS(arr[i])));
    tail = tail->next;
}

ll->free(ll);

```    
