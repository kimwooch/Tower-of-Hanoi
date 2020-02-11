#include <stdbool.h>
#include <stdlib.h>
#include "list.h"
#include "stack.h"

struct mstack
{
    list_t* list;
};

// +--------------+---------------------------------------------------
// | Constructors |
// +--------------+

/**
 * Constructs an empty mstack on the heap and returns a pointer to it.
 */
mstack_t *make_mstack(void)
{
    mstack_t *s = (mstack_t*) malloc(sizeof(mstack_t));
    s->list = make_list();
	return s;
}

// +-------------+----------------------------------------------------
// | Destructors |
// +-------------+

/*
 * Frees all the meory of the mstack
 */
void free_stack(mstack_t *s)
{
    free_list(s->list);
    free(s);
}



// +------------+-----------------------------------------------------
// | Operations |
// +------------+

/**
 * Pushes a new value to the top of the mstack
 */
void push(mstack_t *s, int value)
{
    insert_front(s->list, value);
}

/**
 * Returns the number of elements stored in the mstack.
 */
int size_stack(mstack_t *s)
{
    return size(s->list);
}

/**
 * Pops off the top element of the mstack.
 *
 * Returns whether the pop was successful.
 */
bool pop(mstack_t *s)
{
    return delete_at(s->list, 0);
}

/**
 * Peeks at the element at the top of the mstack. The mstack
 * is not changed by this call.
 */
int peek_stack(mstack_t *s)
{
    // return s->list->first->value;
    return get_element_at(s->list, 0);
}


/*
 * Prints the contents of s to stdout. The format
 * of the mstack is [4,5,7] where 4 is the top of
 * the mstack.
 */
void print_stack(mstack_t *s)
{
    print_list(s->list);
}
