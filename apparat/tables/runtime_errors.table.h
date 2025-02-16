// File is intentionally included multiple times
#ifndef RUNTIME_ERROR
#define RUNTIME_ERROR(name, msg)
#endif
//            name                      message
RUNTIME_ERROR(Success,                  "the operation was completed successfully")
RUNTIME_ERROR(FailedToLinkElement,      "the modeler failed to connect the specified nodes with the desired element")
RUNTIME_ERROR(ElementPointerWasNull,    "a pointer to an element in a flux calculation was found to be NULL when it should not be")
RUNTIME_ERROR(FluxPointerWasNull,       "the flux discrepancy at the given node could not be calculated because the given reference pointer to the flux discrepancy was NULL")
RUNTIME_ERROR(NodePointerWasNull,       "the flux discrepancy at the given node could not be calculated because the given pointer to the node was NULL")
RUNTIME_ERROR(ProblemPointerWasNull,    "the modeler failed to connect the specified nodes because the given problem pointer was NULL")
RUNTIME_ERROR(InsufficientMemory,       "the modeler did not receive an element pointer because the arena had no free memory left")
RUNTIME_ERROR(IncorrectDimensions,      "the dimensions of the given flux calculation arguments were not all identical")
RUNTIME_ERROR(UnknownErrorOccurred,     "the modeler failed to connect the specified nodes because an error occurred")