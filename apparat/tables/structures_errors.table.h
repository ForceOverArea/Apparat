// File is intentionally included multiple times
#ifndef STRUCTURES_ERROR
#define STRUCTURES_ERROR(name, msg)
#endif
//               name                   message
STRUCTURES_ERROR(Success,               "the operation was completed successfully")
STRUCTURES_ERROR(ProblemPointerWasNull, "the modeler failed to connect the specified nodes because the given problem pointer was NULL")
STRUCTURES_ERROR(UnknownErrorOccurred,  "the modeler failed to connect the specified nodes because an error occurred")