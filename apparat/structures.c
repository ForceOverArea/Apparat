#include <stdlib.h>
#include "structures.h"
#include "elements.h"

Element_S *problem_allocateElement(Problem_S *p, ArenaError_E *stat);

#define ELEMENT_TYPE(name, config) config,
ElementConfig_S ELEMENT_VTABLES[] = 
{
    #include "tables/structures.table.h"
};
#undef ELEMENT_TYPE

Problem_S *problem_create(size_t nodes, size_t elements, ArenaError_E *stat)
{
    if (NULL == stat)
    {
        return NULL;
    }

    if (0 == nodes)
    {
        *stat = ArenaError_NoNodesRequested;
    }
    else if (0 == elements)
    {
        *stat = ArenaError_NoElementsRequested;
    }
    
    Problem_S *arena = malloc(sizeof (Problem_S) + (sizeof (ProblemObject_U) * (nodes + elements)));

    if (NULL == arena)
    {
        *stat = ArenaError_ArenaAllocationFailed;
    }

    arena->n_nodes = nodes;
    arena->n_elements = elements;
    arena->used_nodes = 0U;
    arena->used_elements = 0U;

    *stat = ArenaError_Success;

    return arena;
}

ArenaError_E problem_destroy(Problem_S *p)
{
    if (NULL == p)
    {
        return ArenaError_ArenaPointerWasNull;
    }

    free(p);

    return ArenaError_Success;
}

Element_S *problem_allocateElement(Problem_S *p, ArenaError_E *stat)
{
    if (NULL == p)
    {
        *stat = ArenaError_ArenaPointerWasNull;
    }
    else if (NULL == stat)
    {
        *stat = ArenaError_StatPointerWasNull;
    }
    else if (p->used_elements >= p->n_elements)
    {
        *stat = ArenaError_InsufficientMemory;
    }

    *stat = ArenaError_Success;
    Element_S *result = &(p->arena[p->used_elements].element);
    p->used_elements++;

    return result;
}

StructuresError_E structures_linkElement(
    Problem_S *p,   // A pointer to the problem's memory arena 
    size_t n1,      // 
    size_t n2, 
    ElementKind_E kind, 
    Real_T *gain)
{
    Element_S e;
    
    if (NULL == p)
    {
        return StructuresError_ProblemPointerWasNull;
    }

    

    return StructuresError_Success;
}

StructuresError_E node_fluxDiscrepancy(Node_S *node, Real_T *flux)
{

}