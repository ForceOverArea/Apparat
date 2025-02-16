#include "elements.h"
#include "elements_common.h"
#include "vectormath.h"

static inline RuntimeError_E translateStructuresErrorToRuntimeError(StructuresError_E err)
{
    switch (err)
    {
    case StructuresError_ElementPointerWasNull:
        return RuntimeError_ElementPointerWasNull;
        break;
    case StructuresError_NodePointerWasNull:
        return RuntimeError_NodePointerWasNull;
        break;
    case StructuresError_IncorrectDimensions:
        return RuntimeError_IncorrectDimensions;
        break;
    default:
        return RuntimeError_UnknownErrorOccurred;
        break;
    }
}

RuntimeError_E resistor_fluxcalc(void *elem_ptr, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux)
{
    Element_S *elem = elem_ptr;
    StructuresError_E stat = dimensionsCorrect(1, elem, inputNode, outputNode);

    if (StructuresError_Success != stat)
    {
        return translateStructuresErrorToRuntimeError(stat);   
    }

    *flux = elemwise_subtract(outputNode->potential, inputNode->potential);
    *flux = elemwise_divide(*flux, elem->gain);

    return RuntimeError_Success;
}

RuntimeError_E voltage_fluxcalc(void *elem_ptr, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux)
{
    Element_S *elem = elem_ptr;
    ElementConfig_S config;
    
    StructuresError_E stat = dimensionsCorrect(1, elem, inputNode, outputNode);

    if (StructuresError_Success != stat)
    {
        return translateStructuresErrorToRuntimeError(stat);
    }

    stat = get_elementConfig(elem->kind, &config);

    if (elem->drivesOutput)

    return RuntimeError_Success;
}