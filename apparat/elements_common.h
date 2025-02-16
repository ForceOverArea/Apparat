#ifndef APPARAT_ELEMENTS_COMMON_H_
#define APPARAT_ELEMENTS_COMMON_H_
#include "structures.h"

bool pointers_not_null(void *elem, void *inputNode, void *outputNode);
bool dimensionsCorrect(size_t dim, Element_S *elem, Node_S *inputNode, Node_S *outputNode);

RuntimeError_E structures_linkElement(Problem_S *p, size_t n1, size_t n2, ElementKind_E kind, VQuant_S gain);
RuntimeError_E node_fluxDiscrepancy(Node_S *node, VQuant_S *fluxDiscrep);


#endif // APPARAT_ELEMENTS_COMMON_H_