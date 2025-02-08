#include "pvec.h"
#include <stdlib.h>

#define SIZEOF_VECTOR(n) (sizeof (Vector_S) + (sizeof (const void *) * (n)))

Vector_S *vector_new()
{
    return malloc(SIZEOF_VECTOR(1));
}

bool vector_pushBack(Vector_S **v, const void *value)
{
    if (NULL == v)
    {
        return false;
    }

    if ((*v)->length > (*v)->capacity)
    {
        return false;
    }
    else if ((*v)->length == (*v)->capacity)
    {
        size_t n_bytes = SIZEOF_VECTOR((*v)->capacity * 2);
        Vector_S *tmp = realloc((*v), n_bytes);
        if (NULL == tmp)
        {
            return false;
        }
        tmp->capacity *= 2;
        (*v) = tmp;
    }

    (*v)->elements[(*v)->length] = value;
    (*v)->length++;

    return true;
}

bool vector_popBack(Vector_S *v, void *const *value)
{
    if (NULL == v || NULL == value || v->length == 0)
    {
        return false;
    }

    v->length--;
    value = v->elements[v->length];

    return true;
}