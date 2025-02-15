#ifndef APPARAT_STRUCTURES_H_
#define APPARAT_STRUCTURES_H_
#include "pvec.h"
#include "types.h"

#define ELEMENT_TYPE(name, config) ElementKind_ ## name,
typedef enum ElementKind
{
    #include "tables/structures.table.h"
}
ElementKind_E;
#undef ELEMENT_TYPE

#define ARENA_ERROR(name, msg) ArenaError_ ## name,
typedef enum ArenaError
{
    #include "tables/arena_errors.table.h"
}
ArenaError_E;
#undef ARENA_ERROR

#define STRUCTURES_ERROR(name, msg) StructuresError_ ## name,
typedef enum StructuresError
{
    #include "tables/structures_errors.table.h"
}
StructuresError_E;
#undef STRUCTURES_ERROR

typedef struct Node
{
    Vector_S *inputs;   // elements connected to the input of this node 
    Vector_S *outputs;  // elements connected to the output of this node 
    void *lockedBy;     // pointer to element that locks this node. If NULL, then node is unlocked
    size_t dimension;   // dimension of the node's potential quantity
    Real_T *potential;  // Buffer for potential if potential is a vector type
}
Node_S;

typedef struct Element
{
    ElementKind_E kind; // enum value indicating what kind of element this is
    size_t dimension;   // dimension of the element's gain quantity
    Node_S *input;      // node connected to this element's input port
    Node_S *output;     // node connected to this element's output port
    Real_T (*flux)(void *, void *); // callback function pointer for determining the flux through this element
    Real_T *gain;       // Buffer for gain if gain is a vector type
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

typedef struct ElementConfig
{
    size_t dimensions;
    void (*fluxCalc)(Element_S *, Node_S *, Node_S *, Real_T *);
    void (*constructor)(Problem_S *, Node_S *, Node_S *, Real_T *);
}
ElementConfig_S;

// Arena creation functions

// Creates a problem graph's memory region
Problem_S *problem_create(size_t nodes, size_t elements, ArenaError_E *stat);
// Destroys a problem's memory region
ArenaError_E problem_destroy(Problem_S *p);

// Structures creation functions

// Calls an element's constructor callback
StructuresError_E structures_linkElement(
    Problem_S *p,   // A pointer to the problem's memory arena 
    size_t n1,      // 
    size_t n2, 
    ElementKind_E kind, 
    Real_T *gain);

StructuresError_E node_fluxDiscrepancy(Node_S *node, Real_T *flux);

#endif // APPARAT_STRUCTURES_H_