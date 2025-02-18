#include "elements.h"
#include "elements_common.h"
#include "vectormath.h"

ApparatError_E resistor_fluxcalc(Element_S *elem, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux)
{
    ApparatError_E stat = dimensionsCorrect(1, elem, inputNode, outputNode);

    if (CommonError_Success != stat)
    {
        return stat;
    }

    *flux = elemwise_subtract(outputNode->potential, inputNode->potential);
    *flux = elemwise_divide(*flux, elem->gain);

    return CommonError_Success;
}

ApparatError_E resistor_new(Problem_S *p, Node_S *n1, Node_S *n2, VQuant_S gain)
{
    ApparatError_E stat;
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
    if (CommonError_Success != stat)
    {
        // we have already NULL-checked both pointers, only return errors for failed allocation
        return StructuresError_InsufficientMemory;
    }

    elem->kind = ElementKind_Resistor;
    elem->input = n1;
    elem->output = n2;
    elem->drivenNode = NULL;
    elem->gain = gain;

    if (!vector_pushBack(&(n1->outputs), elem) ||
        !vector_pushBack(&(n2->inputs), elem))
    {
        return StructuresError_FailedToLinkElement;
    }

    return CommonError_Success;
}

ApparatError_E voltage_fluxcalc(Element_S *elem, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux)
{
    ElementConfig_S config;
    ApparatError_E stat = dimensionsCorrect(1, elem, inputNode, outputNode);
    CHECK_STAT(stat)

    if (outputNode == elem->drivenNode)
    {
        outputNode->potential = elemwise_add(inputNode->potential, elem->gain);
        stat = node_fluxDiscrepancy(outputNode, flux);
        CHECK_STAT(stat)
    }
    else if (inputNode == elem->drivenNode)
    {
        inputNode->potential = elemwise_subtract(outputNode->potential, elem->gain);
        stat = node_fluxDiscrepancy(inputNode, flux);
        CHECK_STAT(stat)
    }
    else
    {
        return RuntimeError_FailedToDriveNode;
    }

    return CommonError_Success;
}

ApparatError_E voltage_new(Problem_S *p, Node_S *n1, Node_S *n2, VQuant_S gain)
{
    ApparatError_E stat;
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
    CHECK_STAT(stat)

    elem->kind = ElementKind_Voltage;
    elem->input = n1;
    elem->output = n2;
    elem->drivenNode = NULL;
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
        return StructuresError_NodePointerWasNull;
    }

    return CommonError_Success;
}