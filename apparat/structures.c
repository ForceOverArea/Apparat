#include <stdlib.h>
#include "structures.h"
#include "elements.h"

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
    
    *index = p->n_nodes + p->used_elements;

    return ArenaError_Success;
}

// 
Problem_S *problem_create(size_t nodes, size_t elements, ArenaError_E *stat)
{
    Node_S n;

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
    
    Problem_S *arena = malloc(
        sizeof (Problem_S) + 
        (sizeof (ProblemObject_U) * (nodes + elements))
    );

    if (NULL == arena)
    {
        *stat = ArenaError_ArenaAllocationFailed;
    }

    arena->n_nodes = nodes;
    arena->n_elements = elements;
    arena->used_elements = 0U;

    for (size_t i = 0; i < nodes; i++)
    {
        n = arena->arena[i].node;
        n.inputs = vector_new();
        n.outputs = vector_new();
        
        if (NULL == n.inputs || NULL == n.outputs)
        {
            *stat = ArenaError_ArenaAllocationFailed;
        }
    }

    *stat = ArenaError_Success;

    return arena;
}

ArenaError_E problem_destroy(Problem_S *p)
{
    Node_S n;

    if (NULL == p)
    {
        return ArenaError_ArenaPointerWasNull;
    }

    for (size_t i = 0; i < p->n_nodes; i++)
    {
        n = p->arena[i].node;
        
        if (NULL == n.inputs || NULL == n.outputs)
        {
            return ArenaError_FailedToFreeArena;
        }

        free(n.inputs);
        free(n.outputs);
    }

    free(p);

    return ArenaError_Success;
}

Element_S *problem_allocateElement(Problem_S *p, ArenaError_E *stat)
{
    ArenaError_E stat2;
    size_t elemIndex = 0U;

    if (NULL == p)
    {
        *stat = ArenaError_ArenaPointerWasNull;
        return NULL;
    }
    else if (NULL == stat)
    {
        *stat = ArenaError_StatPointerWasNull;
        return NULL;
    }
    else if (p->used_elements >= p->n_elements)
    {
        *stat = ArenaError_InsufficientMemory;
        return NULL;
    }

    *stat = problem_getAvailableElementIndex(p, &elemIndex);
    if (ArenaError_Success != (*stat))
    {
        return NULL;
    }

    Element_S *result = &(p->arena[elemIndex].element);
    p->used_elements++;

    *stat = ArenaError_Success;
    return result;
}

