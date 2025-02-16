// File is intentionally included multiple times
#ifndef ARENA_ERROR
#define ARENA_ERROR(name, msg)
#endif
//          name                        message
ARENA_ERROR(Success,                    "the operation was completed successfully")
ARENA_ERROR(ArenaPointerWasNull,        "the given reference to the arena to create was NULL")
ARENA_ERROR(StatPointerWasNull,         "the arena could not report a status because the given status pointer to populate was NULL")
ARENA_ERROR(IndexPointerWasNull,        "the arena could not return the element region start index because the given index reference pointer was NULL")
ARENA_ERROR(NoNodesRequested,           "the arena will not allocate memory for a problem with no nodes")
ARENA_ERROR(NoElementsRequested,        "the arena will not allocate memory for a problem with no elements")
ARENA_ERROR(ArenaAllocationFailed,      "the arena failed to allocate the memory needed to solve the problem")
ARENA_ERROR(FailedToFreeArena,          "the arena failed to free the node and element memory tied up in the arena")
ARENA_ERROR(InsufficientMemory,         "the arena could not allocate an element pointer because it has no free memory left")
ARENA_ERROR(UnknownErrorOccurred,       "the arena experienced an unknown error while allocating or freeing memory")
