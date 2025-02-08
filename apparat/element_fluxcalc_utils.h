#ifndef APPARAT_ELEMENT_FLUX_CALC_UTILS_H_
#define APPARAT_ELEMENT_FLUX_CALC_UTILS_H_
#include <stdbool.h>
#include "node_element.h"

bool pointers_not_null(void *elem, void *inputNode, void *outputNode, Real_T *flux);
bool dimensionsCorrect(size_t dim, Element_S *elem, Node_S *inputNode, Node_S *outputNode, Real_T *flux);

#endif // APPARAT_ELEMENT_FLUX_CALC_UTILS_H_