#include <stddef.h>
#include "element_fluxcalcs.h"
#include "element_fluxcalc_utils.h"
#include "node_element.h"
#include "types.h"

// 1D resistor element
static void resistor_fluxcalcHelper(
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

void resistor_fluxcalc(void *elem, void *inputNode, void *outputNode, Real_T *flux)
{
    resistor_fluxcalcHelper(
        (Element_S *)elem, 
        (Node_S *)inputNode, 
        (Node_S *)outputNode, 
        flux);
}



// 1D voltage source element
static void voltage_fluxcalcHelper(
    Element_S *elem, 
    Node_S *inputNode, 
    Node_S *outputNode, 
    Real_T *flux)
{
    if (dimensionsCorrect(1, elem, inputNode, outputNode, flux))
    {

    }
}

void voltage_fluxcalc(void *elem, void *inputNode, void *outputNode, Real_T *flux)
{
    voltage_fluxcalcHelper(elem, inputNode, outputNode, flux);
}

// 1D current source element
static void current_fluxcalcHelper(
    Element_S *elem, 
    Node_S *inputNode, 
    Node_S *outputNode, 
    Real_T *flux)
{
    if (dimensionsCorrect(1, elem, inputNode, outputNode, flux))
    {

    }
}

void current_fluxcalc(void *elem, void *inputNode, void *outputNode, Real_T *flux)
{
    current_fluxcalcHelper(elem, inputNode, outputNode, flux);
}