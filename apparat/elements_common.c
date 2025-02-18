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

StructuresError_E element_getConfig(ElementKind_E kind, ElementConfig_S *cfg)
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
StructuresError_E pointersNotNull(Element_S *elem, Node_S *inputNode, Node_S *outputNode)
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
 * `pointersNotNull` if a NULL pointer is found.
 */
StructuresError_E dimensionsCorrect(size_t dim, Element_S *elem, Node_S *inputNode, Node_S *outputNode)
{
    StructuresError_E stat = pointersNotNull(elem, inputNode, outputNode);

    if (StructuresError_Success != stat)
    {
        return stat;
    }

    ElementConfig_S cfg;
    stat = element_getConfig(elem->kind, &cfg);
    if (StructuresError_Success != stat)
    {
        return stat;
    }

    if (dim == cfg.dimensionality && 
        (cfg.dimensionality == inputNode->dimension) && 
        (inputNode->dimension == outputNode->dimension))
    {
        return StructuresError_IncorrectDimensions;
    }

    return StructuresError_Success;
}

RuntimeError_E node_fluxDiscrepancy(Node_S *node, VQuant_S *fluxDiscrep)
{
    Element_S *element;
    ElementConfig_S cfg;
    StructuresError_E stat;
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
        stat = element_getConfig(element->kind, &cfg);
        
        if (StructuresError_Success != stat)
        {
            
        }

        zero(&temp);
        cfg.flux(element, element->input, element->output, &temp);
        *fluxDiscrep = elemwise_add(*fluxDiscrep, temp);
    }

    // subtract outputs from "stored flux"
    for (size_t i = 0; i < node->outputs->length; i++)
    {
        element = (Element_S*)(node->outputs->elements[i]);
        stat = element_getConfig(element->kind, &cfg);

        if (StructuresError_Success != stat)
        {
            return translateStructuresErrorToRuntimeError(stat);
        }

        zero(&temp);
        cfg.flux(element, element->input, element->output, &temp);
        *fluxDiscrep = elemwise_subtract(*fluxDiscrep, temp);
    }

    return RuntimeError_Success;
}