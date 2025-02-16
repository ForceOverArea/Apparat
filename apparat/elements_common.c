#include "elements_common.h"

bool pointers_not_null(
    void *elem, 
    void *inputNode, 
    void *outputNode)
{
    return ((NULL != elem) && 
        (NULL != inputNode) &&
        (NULL != outputNode));
}  

bool dimensionsCorrect(
    size_t dim,
    Element_S *elem, 
    Node_S *inputNode, 
    Node_S *outputNode)
{
    if (!pointers_not_null(elem, inputNode, outputNode))
    {
        return false;
    }

    return ((dim == elem->dimension) &&
        (elem->dimension == inputNode->dimension) &&
        (inputNode->dimension == outputNode->dimension));
}