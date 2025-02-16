#include <stdlib.h>
#include "structures.h"
#include "elements.h"

#define ELEMENT_TYPE(name, config) config,
ElementConfig_S ELEMENT_VTABLES[] = 
{
    #include "tables/structures.table.h"
};
#undef ELEMENT_TYPE

static inline ArenaError_E problem_getAvailableElementIndex(Problem_S *p, size_t *index)
{
    if (NULL == p)
    {
        return ArenaError_ArenaPointerWasNull;
    }
    if (NULL == index)
    {
        return ArenaError_IndexPointerWasNull;
    }
    
    *index = p->n_nodes;

    return ArenaError_Success;
}

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
    VQuant_S gain)
{
    ArenaError_E stat = ArenaError_Success;
    ElementConfig_S config;
    Element_S *element;
    Node_S *inputNode;
    Node_S *outputNode;

    if (NULL == p)
    {
        return StructuresError_ProblemPointerWasNull;
    }

    config = ELEMENT_VTABLES[kind];
    element = problem_allocateElement(p, &stat);
    inputNode = &(p->arena[n1].node);
    outputNode = &(p->arena[n2].node);

    if ((ArenaError_Success == stat) && (NULL != element))
    {
        // connect element from n1 to n2
        element->kind       = kind;
        element->dimension  = config.dimension;
        element->flux       = config.flux;
        element->gain       = gain;
        element->input      = inputNode;
        element->output     = outputNode;

        // connect nodes to element where it makes sense
        if (config.connectToOutput)
        {
            vector_pushBack(&(outputNode->inputs), element);
        }
        
        if (config.connectToInput)
        {
            vector_pushBack(&(inputNode->outputs), element);
        }
    }
    else // error reporting
    {
        switch (stat)
        {
        case ArenaError_InsufficientMemory:
            return StructuresError_InsufficientMemory;
            break;
        default:
            return StructuresError_UnknownError;
            break;
        }
    }

    return StructuresError_Success;
}

StructuresError_E node_fluxDiscrepancy(Node_S *node, VQuant_S *fluxDiscrep)
{
    
}