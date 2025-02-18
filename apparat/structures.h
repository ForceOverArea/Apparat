#ifndef APPARAT_STRUCTURES_H_
#define APPARAT_STRUCTURES_H_
#include "apparat_errors.h"
#include "pvec.h"
#include "types.h"

#define ELEMENT_TYPE(name, config) ElementKind_ ## name,
typedef enum ElementKind
{
    #include "tables/structures.table.h"
    NUM_OF_ELEMENT_KINDS, // do not move this definition!!!
}
ElementKind_E;
#undef ELEMENT_TYPE

typedef struct Node
{
    Vector_S *inputs;    // elements connected to the input of this node 
    Vector_S *outputs;   // elements connected to the output of this node 
    void *lockedBy;      // pointer to element that locks this node. If NULL, then node is unlocked
    size_t dimension;    // dimension of the node's potential quantity
    VQuant_S potential;  // Buffer for potential if potential is a vector type
}
Node_S;

typedef struct Element
{
    ElementKind_E kind;  // enum value indicating what kind of element this is
    Node_S *input;       // node connected to this element's input port
    Node_S *output;      // node connected to this element's output port
    Node_S *drivenNode;  // indicates which node's potential this element controls
    VQuant_S gain;       // Buffer for gain if gain is a vector type
}
Element_S;

typedef union ProblemObject
{
    Node_S node;
    Element_S element;
}
ProblemObject_U;

typedef struct Problem
{
    size_t n_nodes;         // number of nodes in the node memory region
    size_t n_elements;      // number of elements in the element memory region
    size_t used_elements;   // number of elements that have been allocated within the element memory region
    ProblemObject_U arena[]; // the pointer to the node memory region
}
Problem_S;

typedef ApparatError_E (*FluxCallback_T)(Element_S *, Node_S *, Node_S *, VQuant_S *);

typedef ApparatError_E (*ElementConstructor_T)(Problem_S *,Node_S *, Node_S *, VQuant_S);

typedef struct ElementConfig
{
    ElementConstructor_T constructor;
    FluxCallback_T flux;
    size_t dimensionality;
}
ElementConfig_S;

// Arena functions
Problem_S *problem_create(size_t nodes, size_t elements, ApparatError_E *stat);
ApparatError_E problem_destroy(Problem_S *p);
Element_S *problem_allocateElement(Problem_S *p, ApparatError_E *stat);

#endif // APPARAT_STRUCTURES_H_