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

StructuresError_E resistor_new(Problem_S *p, Node_S *n1, Node_S *n2, VQuant_S gain)
{
    ArenaError_E stat;
    Element_S *elem  = NULL;

    if (NULL == p)
    {
        return StructuresError_ProblemPointerWasNull;
    }
    else if (NULL == n1 || NULL == n2)
    {
        return StructuresError_NodePointerWasNull;
    }

    elem = problem_allocateElement(p, &stat);
    if (ArenaError_Success != stat)
    {
        // we have already NULL-checked both pointers, only return errors for failed allocation
        return StructuresError_InsufficientMemory;
    }

    elem->kind = ElementKind_Resistor;
    elem->dimension = 1U;
    elem->input = n1;
    elem->output = n2;
    elem->drivenNode = NULL;
    elem->flux = &resistor_fluxcalc;
    elem->gain = gain;

    if (!vector_pushBack(&(n1->outputs), elem) ||
        !vector_pushBack(&(n2->inputs), elem))
    {
        return StructuresError_FailedToLinkElement;
    }

    return StructuresError_Success;
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

    stat = element_getConfig(elem->kind, &config);

    

    return RuntimeError_Success;
}

StructuresError_E voltage_new(Problem_S *p, Node_S *n1, Node_S *n2, VQuant_S gain)
{
    ArenaError_E stat;
    Element_S *elem  = NULL;

    if (NULL == p)
    {
        return StructuresError_ProblemPointerWasNull;
    }
    else if (NULL == n1 || NULL == n2)
    {
        return StructuresError_NodePointerWasNull;
    }

    elem = problem_allocateElement(p, &stat);
    if (ArenaError_Success != stat)
    {
        // we have already NULL-checked both pointers, only return errors for failed allocation
        return StructuresError_InsufficientMemory;
    }

    elem->kind = ElementKind_Voltage;
    elem->dimension = 1U;
    elem->input = n1;
    elem->output = n2;
    elem->drivenNode = NULL;
    elem->flux = &voltage_fluxcalc;
    elem->gain = gain;

    if (NULL != n2->lockedBy)
    {
        n2->lockedBy = elem;
        if (!vector_pushBack(&(n1->outputs), (void *)elem))
        {
            return StructuresError_FailedToLinkElement;
        }
    }
    else if (NULL != n1->lockedBy)
    {
        n1->lockedBy = elem;
        if (!vector_pushBack(&(n2->inputs), (void *)elem))
        {
            return StructuresError_FailedToLinkElement;
        }
    }
    else 
    {
        return StructuresError_NodePointerWasNull
    }

    return StructuresError_Success;
}