#include "elements.h"
#include "elements_common.h"
#include "vectormath.h"

RuntimeError_E resistor_fluxcalc(
    void *elem_ptr, 
    Node_S *inputNode, 
    Node_S *outputNode, 
    VQuant_S *flux)
{
    Element_S *elem = elem_ptr;
    if (dimensionsCorrect(1, elem, inputNode, outputNode))
    {
        *flux = elemwise_subtract(outputNode->potential, inputNode->potential);
        *flux = elemwise_divide(*flux, elem->gain);
    }
    else
    {
        return RuntimeError_IncorrectDimensions;
    }

    return RuntimeError_Success;
}