#include "elements.h"
#include "elements_common.h"
#include "vectormath.h"

#define ELEMENT_TYPE(name, config) config,
ElementConfig_S ELEMENT_VTABLES[] = 
{
    #include "tables/structures.table.h"
};
#undef ELEMENT_TYPE

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

RuntimeError_E structures_linkElement(
    Problem_S *p,   // A pointer to the problem's memory arena 
    size_t n1,      // the index of the node to connect to the element's input
    size_t n2,      // the index of the node to connect to the element's output
    ElementKind_E kind, // the type of the element to use to connect 
    VQuant_S gain)  // the gain to apply to the element
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

// TODO: this should return a runtime error, not a structures error
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