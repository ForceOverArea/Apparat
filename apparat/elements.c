#include "elements.h"
#include "elements_common.h"

void resistor_fluxcalc(
    Element_S *elem, 
    Node_S *inputNode, 
    Node_S *outputNode, 
    Real_T *flux)
{
    if (dimensionsCorrect(1, elem, inputNode, outputNode, flux))
    {
        *flux = (outputNode->potential[0] - inputNode->potential[0]) / elem->gain[0];
    }
}
