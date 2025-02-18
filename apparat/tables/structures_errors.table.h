// File is intentionally included multiple times
#ifndef STRUCTURES_ERROR
#define STRUCTURES_ERROR(name, msg)
#endif
//               name                       message
STRUCTURES_ERROR(Success,                   "the operation was completed successfully")
STRUCTURES_ERROR(ProblemPointerWasNull,     "the modeler failed to connect the specified nodes because the given problem pointer was NULL")
STRUCTURES_ERROR(NodePointerWasNull,        "a pointer to a node was found to be NULL when it should not be")
STRUCTURES_ERROR(ElementPointerWasNull,     "a pointer to a element was found to be NULL when it should not be")
STRUCTURES_ERROR(FailedToLinkElement,       "the modeler failed to connect the specified nodes with the desired element")
STRUCTURES_ERROR(FailedToDriveNode,         "the modeler failed to connect the specified node-driving element to nodes because both nodes were locked by another element")
STRUCTURES_ERROR(ElementConfigDoesNotExist, "config data for the given element kind could not be found because the given element type was invalid")
STRUCTURES_ERROR(FailedToCopyConfigData,    "config data was found for the given element type, but 'memcpy' failed")
STRUCTURES_ERROR(IncorrectDimensions,       "the dimensions of the element and node pointers given were not all identical")
STRUCTURES_ERROR(InsufficientMemory,        "the arena could not allocate an element pointer because it has no free memory left")
STRUCTURES_ERROR(UnknownErrorOccurred,      "the modeler failed to connect the specified nodes because an error occurred")