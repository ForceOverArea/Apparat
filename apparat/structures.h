#ifndef APPARAT_STRUCTURES_H_
#define APPARAT_STRUCTURES_H_
#include "pvec.h"
#include "types.h"

#define ELEMENT_TYPE(name, dims, func, cons) ElementKind_ ## name,
typedef enum ElementKind
{
    #include "tables/structures.table.h"
}
ElementKind_E;
#undef ELEMENT_TYPE

typedef struct Node
{
    Vector_S *inputs;
    Vector_S *outputs;
    void *lockedBy;
    size_t dimension;
    Real_T *potential; // Buffer for potential if potential is a vector type
}
Node_S;

typedef struct Element
{
    Node_S *input; 
    Node_S *output;
    size_t dimension;
    Real_T *gain; // Buffer for gain if gain is a vector type
    Real_T (*flux)(void *, void *);
    ElementKind_E kind;
}
Element_S;

#endif // APPARAT_STRUCTURES_H_