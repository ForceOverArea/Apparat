#ifndef APPARAT_PVEC_H_
#define APPARAT_PVEC_H_
#include <stdbool.h>
#include <stddef.h>

typedef struct Vector
{
    size_t length;
    size_t capacity;
    const void *elements[];
}
Vector_S;

Vector_S *vector_new(void);
bool vector_pushBack(Vector_S **v, const void *value);
bool vector_popBack(Vector_S *v, void *const *value);

#endif // APPARAT_PVEC_H_