#include "stdlib.h"
#include "node_element_arena.h"

#define ARENA_ERROR(name, msg) msg,
const char *GLOBAL_ARENA_ERROR_MSG_TABLE[] = 
{
    #include "tables/node_element_arena_errors.table.h"
};
#undef ARENA_ERROR

const char *globalarena_showError(GlobalArenaError_E err)
{
    return GLOBAL_ARENA_ERROR_MSG_TABLE[err];
}

GlobalArenaError_E globalarena_create(GlobalArena_S *arena, size_t nodes, size_t elements)
{
    if (NULL == arena)
    {
        return GlobalArenaError_ArenaPointerWasNull;
    }
    else if (0 == nodes)
    {
        return GlobalArenaError_NoNodesRequested;
    }
    else if (0 == elements)
    {
        return GlobalArenaError_NoElementsRequested;
    }

    GlobalNode_S *nodeArena = malloc((sizeof (GlobalNode_S)) * nodes);
    if (NULL == nodeArena)
    {
        return GlobalArenaError_NodeAllocationFailed;
    }

    GlobalElement_S *elementArena = malloc((sizeof (GlobalElement_S)) * elements);
    if (NULL == elementArena)
    {
        free(nodeArena);
        return GlobalArenaError_ElementAllocationFailed;
    }

    arena->numNodes = nodes;
    arena->numElements = elements;
    arena->nodes = nodeArena;
    arena->elements = elementArena;

    return GlobalArenaError_Success;
}

GlobalArenaError_E globalarena_freeGlobalArena(GlobalArena_S *arena)
{
    GlobalArenaError_E error = GlobalArenaError_Success;
    unsigned int errorBitFlags = 0x00;

    if (NULL == arena)
    {
        error = GlobalArenaError_ArenaPointerWasNull;
    }
    else
    {
        if (NULL == arena->nodes)
        {
            errorBitFlags |= BitField_BitZero;
        }
        else
        {
            free(arena->nodes);
        }
        
        if (NULL == arena->elements)
        {
            errorBitFlags |= BitField_BitOne;
        }
        else
        {
            free(arena->elements);
        }

        switch (errorBitFlags)
        {
        case BitField_None:
            error = GlobalArenaError_Success;
            break;
        case BitField_BitZero:
            error = GlobalArenaError_FailedToFreeNodes;
            break;
        case BitField_BitOne:
            error = GlobalArenaError_FailedToFreeElements;
            break;
        case (BitField_BitZero | BitField_BitOne):
            error = GlobalArenaError_FailedToFreeArena;
            break;
        default:
            error = GlobalArenaError_UnknownErrorOccurred;
            break;
        }
    }

    return error;
}

