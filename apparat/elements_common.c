#include "elements_common.h"

bool pointers_not_null(
    void *elem, 
    void *inputNode, 
    void *outputNode, 
    Real_T *flux)
{
    return ((NULL != elem) && 
        (NULL != inputNode) &&
        (NULL != outputNode) &&
        (NULL != flux));
}  

bool dimensionsCorrect(
    size_t dim,
    Element_S *elem, 
    Node_S *inputNode, 
    Node_S *outputNode, 
    Real_T *flux)
{
    if (!pointers_not_null(elem, inputNode, outputNode, flux))
    {
        return false;
    }

    return ((dim == elem->dimension) &&
        (elem->dimension == inputNode->dimension) &&
        (inputNode->dimension == outputNode->dimension));
}