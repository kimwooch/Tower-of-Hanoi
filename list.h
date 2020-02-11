#ifndef list_h
#define list_h
#include <stdbool.h>

typedef struct list list_t;
typedef struct node node_t;

list_t *make_list(void);
void free_list(list_t *lst);
void insert_front(list_t *lst, int value);
int size(list_t *lst);
bool delete_at(list_t *lst, int index);
bool delete_front(list_t *lst);
bool delete_last(list_t* lst);
int get_element_at(list_t *lst, int index);
void print_list(list_t *lst);

#endif
