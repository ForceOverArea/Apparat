// File is intentionally included multiple times
#ifndef APPARAT_ERROR
#define APPARAT_ERROR(class ,name, msg)
#endif
//            class             name                        message
APPARAT_ERROR(CommonError,      Success,                    "the operation was completed successfully")

APPARAT_ERROR(ArenaError,       ArenaPointerWasNull,        "the given reference to the arena to create was NULL")
APPARAT_ERROR(ArenaError,       StatPointerWasNull,         "the arena could not report a status because the given status pointer to populate was NULL")
APPARAT_ERROR(ArenaError,       IndexPointerWasNull,        "the arena could not return the element region start index because the given index reference pointer was NULL")
APPARAT_ERROR(ArenaError,       NoNodesRequested,           "the arena will not allocate memory for a problem with no nodes")
APPARAT_ERROR(ArenaError,       NoElementsRequested,        "the arena will not allocate memory for a problem with no elements")
APPARAT_ERROR(ArenaError,       ArenaAllocationFailed,      "the arena failed to allocate the memory needed to solve the problem")
APPARAT_ERROR(ArenaError,       FailedToFreeArena,          "the arena failed to free the node and element memory tied up in the arena")
APPARAT_ERROR(ArenaError,       InsufficientMemory,         "the arena could not allocate an element pointer because it has no free memory left")
APPARAT_ERROR(ArenaError,       UnknownErrorOccurred,       "the arena experienced an unknown error while allocating or freeing memory")

APPARAT_ERROR(StructuresError,  ProblemPointerWasNull,      "the modeler failed to connect the specified nodes because the given problem pointer was NULL")
APPARAT_ERROR(StructuresError,  NodePointerWasNull,         "a pointer to a node was found to be NULL when it should not be")
APPARAT_ERROR(StructuresError,  ElementPointerWasNull,      "a pointer to a element was found to be NULL when it should not be")
APPARAT_ERROR(StructuresError,  FailedToLinkElement,        "the modeler failed to connect the specified nodes with the desired element")
APPARAT_ERROR(StructuresError,  FailedToDriveNode,          "the modeler failed to connect the specified node-driving element to nodes because both nodes were locked by another element")
APPARAT_ERROR(StructuresError,  ElementConfigDoesNotExist,  "config data for the given element kind could not be found because the given element type was invalid")
APPARAT_ERROR(StructuresError,  FailedToCopyConfigData,     "config data was found for the given element type, but 'memcpy' failed")
APPARAT_ERROR(StructuresError,  IncorrectDimensions,        "the dimensions of the element and node pointers given were not all identical")
APPARAT_ERROR(StructuresError,  InsufficientMemory,         "the arena could not allocate an element pointer because it has no free memory left")
APPARAT_ERROR(StructuresError,  UnknownErrorOccurred,       "the modeler failed to connect the specified nodes because an error occurred")

APPARAT_ERROR(RuntimeError,     ElementPointerWasNull,      "a pointer to an element in a flux calculation was found to be NULL when it should not be")
APPARAT_ERROR(RuntimeError,     FluxPointerWasNull,         "the flux discrepancy at the given node could not be calculated because the given reference pointer to the flux discrepancy was NULL")
APPARAT_ERROR(RuntimeError,     NodePointerWasNull,         "the flux discrepancy at the given node could not be calculated because the given pointer to the node was NULL")
APPARAT_ERROR(RuntimeError,     ProblemPointerWasNull,      "the modeler failed to connect the specified nodes because the given problem pointer was NULL")
APPARAT_ERROR(RuntimeError,     InsufficientMemory,         "the modeler did not receive an element pointer because the arena had no free memory left")
APPARAT_ERROR(RuntimeError,     IncorrectDimensions,        "the dimensions of the given flux calculation arguments were not all identical")
APPARAT_ERROR(RuntimeError,     UnknownErrorOccurred,       "the modeler failed to connect the specified nodes because an error occurred")
APPARAT_ERROR(RuntimeError,     FailedToDriveNode,          "a flux calculation failed because the element (which drives a node) could not determine which node it was driving")