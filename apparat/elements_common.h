#ifndef APPARAT_ELEMENTS_COMMON_H_
#define APPARAT_ELEMENTS_COMMON_H_
#include "structures.h"

ApparatError_E element_getConfig(ElementKind_E kind, ElementConfig_S *cfg);
ApparatError_E pointersNotNull(Element_S *elem, Node_S *inputNode, Node_S *outputNode);
ApparatError_E dimensionsCorrect(size_t dim, Element_S *elem, Node_S *inputNode, Node_S *outputNode);
ApparatError_E node_fluxDiscrepancy(Node_S *node, VQuant_S *fluxDiscrep);

#endif // APPARAT_ELEMENTS_COMMON_H_