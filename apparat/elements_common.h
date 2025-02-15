#ifndef APPARAT_ELEMENTS_COMMON_H_
#define APPARAT_ELEMENTS_COMMON_H_
#include "structures.h"

bool pointers_not_null(void *elem, void *inputNode, void *outputNode, Real_T *flux);
bool dimensionsCorrect(size_t dim, Element_S *elem, Node_S *inputNode, Node_S *outputNode, Real_T *flux);

#endif // APPARAT_ELEMENTS_COMMON_H_