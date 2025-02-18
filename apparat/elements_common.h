#ifndef APPARAT_ELEMENTS_COMMON_H_
#define APPARAT_ELEMENTS_COMMON_H_
#include "structures.h"

StructuresError_E element_getConfig(ElementKind_E kind, ElementConfig_S *cfg);
StructuresError_E pointersNotNull(Element_S *elem, Node_S *inputNode, Node_S *outputNode);
StructuresError_E dimensionsCorrect(size_t dim, Element_S *elem, Node_S *inputNode, Node_S *outputNode);
RuntimeError_E node_fluxDiscrepancy(Node_S *node, VQuant_S *fluxDiscrep);

#endif // APPARAT_ELEMENTS_COMMON_H_