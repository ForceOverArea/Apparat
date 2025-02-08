#ifndef APPARAT_NODE_ELEMENT_H_
#define APPARAT_NODE_ELEMENT_H_
#include <stddef.h>
#include <stdbool.h>
#include "element_fluxcalcs.h"
#include "types.h"
#include "pvec.h"

#define ELEMENT_TYPE(name, dims, func, cons) ElementKind_ ## name,
typedef enum ElementKind
{
    #include "tables/node_element.table.h"
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

unsigned int element_getDimensions(ElementKind_E element);

bool connectNodes(Node_S *n1, Node_S *n2, Real_T *gain, ElementKind_E element);

#endif // APPARAT_NODE_ELEMENT_H_