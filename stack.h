#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>

typedef struct mstack mstack_t;

mstack_t *make_mstack(void);
void free_stack(mstack_t *s);
void push(mstack_t *s, int value);
int size_stack(mstack_t *s);
bool pop(mstack_t *s);
int peek_stack(mstack_t *s);
void print_stack(mstack_t *s);

#endif
