#ifndef APPARAT_NODE_ELEMENT_ARENA_H_
#define  APPARAT_NODE_ELEMENT_ARENA_H_
#include "node_element.h"

#define ARENA_ERROR(name, msg) GlobalArenaError_ ## name,
typedef enum GlobalArenaError
{
    #include "tables/node_element_arena_errors.table.h"
}
GlobalArenaError_E;
#undef ARENA_ERROR

typedef struct GlobalNode
{
    const char *name;
    Node_S node;
}
GlobalNode_S;

typedef struct GlobalElement
{
    const char *name;
    Element_S element;
}
GlobalElement_S;

typedef struct GlobalArena
{
    size_t numNodes;
    size_t numElements;
    GlobalNode_S *nodes;
    GlobalElement_S *elements;
}
GlobalArena_S;

// Yields the null-terminated string representation of the given error code.
const char *globalarena_showError(GlobalArenaError_E err);

// Creates a new node in the global node arena. These nodes will live until
// they are deallocated with `globalnode_cleanGlobalNodeArena`.
GlobalArenaError_E globalarena_create(GlobalArena_S *arena, size_t nodes, size_t elements);

// Deallocates the memory tied up in the global node arena
GlobalArenaError_E globalarena_freeGlobalArena(GlobalArena_S *arena);

#endif // APPARAT_NODE_ELEMENT_ARENA_H_