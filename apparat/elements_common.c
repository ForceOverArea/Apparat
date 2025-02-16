#include <string.h>
#include "elements.h"
#include "elements_common.h"
#include "vectormath.h"

#define ELEMENT_TYPE(name, config) config,
ElementConfig_S ELEMENT_VTABLES[] = 
{
    #include "tables/structures.table.h"
};
#undef ELEMENT_TYPE

StructuresError_E get_elementConfig(ElementKind_E kind, ElementConfig_S *cfg)
{
    void *stat = NULL;

    if (kind >= NUM_OF_ELEMENT_KINDS)
    {
        return StructuresError_ElementConfigDoesNotExist;
    }

    stat = memcpy(cfg, &(ELEMENT_VTABLES[kind]), sizeof (ElementConfig_S));

    if (NULL == stat)
    {
        return StructuresError_FailedToCopyConfigData;
    } 

    return StructuresError_Success;
}

/**
 * Ensures that the given pointers are not NULL, reporting errors for which kind of 
 * pointer was NULL (i.e. node or element pointer.)
 */
StructuresError_E pointers_not_null(Element_S *elem, Node_S *inputNode, Node_S *outputNode)
{
    if (NULL != elem)
    {
        return StructuresError_ElementPointerWasNull;
    }
    else if (NULL != inputNode && NULL != outputNode)
    {
        return StructuresError_NodePointerWasNull;
    }

    return StructuresError_Success;
}  

/**
 * Ensures that the dimensions of the given nodes and elements are all in agreement to prevent
 * miscalculations down the line. This function also NULL-checks its arguments, behaving like 
 * `pointers_not_null` if a NULL pointer is found.
 */
StructuresError_E dimensionsCorrect(size_t dim, Element_S *elem, Node_S *inputNode, Node_S *outputNode)
{
    StructuresError_E stat = pointers_not_null(elem, inputNode, outputNode);

    if (StructuresError_Success != stat)
    {
        return stat;
    }

    if (dim == elem->dimension && 
        (elem->dimension == inputNode->dimension) && 
        (inputNode->dimension == outputNode->dimension))
    {
        return StructuresError_IncorrectDimensions;
    }

    return StructuresError_Success;
}


RuntimeError_E structures_linkElement(Problem_S *p, size_t n1, size_t n2, ElementKind_E kind, VQuant_S gain)
{
    ArenaError_E stat = ArenaError_Success;
    ElementConfig_S config;
    Element_S *element;
    Node_S *inputNode;
    Node_S *outputNode;

    if (NULL == p)
    {
        return RuntimeError_ProblemPointerWasNull;
    }

    config = ELEMENT_VTABLES[kind];
    element = problem_allocateElement(p, &stat);
    inputNode = &(p->arena[n1].node);
    outputNode = &(p->arena[n2].node);

    if ((ArenaError_Success == stat) && (NULL != element))
    {
        // connect element from n1 to n2
        element->kind       = kind;
        element->dimension  = config.dimension;
        element->flux       = config.flux;
        element->gain       = gain;
        element->input      = inputNode;
        element->output     = outputNode;

        // connect nodes to element where it makes sense
        if (config.connectToOutput)
        {
            if (!vector_pushBack(&(outputNode->inputs), element))
            {
                return RuntimeError_FailedToLinkElement;
            }
        }
        
        if (config.connectToInput)
        {
            if (!vector_pushBack(&(inputNode->outputs), element))
            {
                return RuntimeError_FailedToLinkElement;
            }
        }
    }
    else // error reporting
    {
        switch (stat)
        {
        case ArenaError_InsufficientMemory:
            return RuntimeError_InsufficientMemory;
            break;
        default:
            return RuntimeError_UnknownErrorOccurred;
            break;
        }
    }

    return RuntimeError_Success;
}

RuntimeError_E node_fluxDiscrepancy(Node_S *node, VQuant_S *fluxDiscrep)
{
    Element_S *element;
    Node_S *inputNode;
    Node_S *outputNode;
    VQuant_S temp;

    if (NULL == node)
    {
        return RuntimeError_NodePointerWasNull;
    }
    else if (NULL == fluxDiscrep)
    {
        return RuntimeError_FluxPointerWasNull;
    }

    zero(fluxDiscrep);

    // add inputs to "stored flux"
    for (size_t i = 0; i < node->inputs->length; i++)
    {
        element = (Element_S*)(node->inputs->elements[i]);
        inputNode = element->input;
        outputNode = element->output;
        
        zero(&temp);
        element->flux((void *)element, inputNode, outputNode, &temp);
        *fluxDiscrep = elemwise_add(*fluxDiscrep, temp);
    }

    // subtract outputs from "stored flux"
    for (size_t i = 0; i < node->outputs->length; i++)
    {
        element = (Element_S*)(node->outputs->elements[i]);
        inputNode = element->input;
        outputNode = element->output;
        
        zero(&temp);
        element->flux((void *)element, inputNode, outputNode, &temp);
        *fluxDiscrep = elemwise_subtract(*fluxDiscrep, temp);
    }

    return RuntimeError_Success;
}