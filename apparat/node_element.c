#include "node_element.h"

// Populate flux calculation table
#define ELEMENT_TYPE(name, dims, func, cons) &func,
void (*const FLUX_CALC_LOOKUP[])(void *, void *, void *, Real_T *) = 
{
    #include "tables/node_element.table.h"
};
#undef ELEMENT_TYPE

// Populate constructor table
#define ELEMENT_TYPE(name, dims, func, cons) &cons,
void (*const ELEM_CONS_LOOKUP[])(void *, void *, Real_T *) = 
{
    #include "tables/node_element.table.h"
};
#undef ELEMENT_TYPE

// Populate dimensions lookup table
#define ELEMENT_TYPE(name, dims, func, cons) dims,
const unsigned int DIMENSIONS_LOOKUP[] = 
{
    #include "tables/node_element.table.h"
};
#undef ELEMENT_TYPE

unsigned int element_getDimensions(ElementKind_E element)
{
    return DIMENSIONS_LOOKUP[element];
}

bool connectNodes(Node_S *n1, Node_S *n2, Real_T *gain, ElementKind_E element)
{
    void (*elementConstructor)(void *, void *, Real_T *) = ELEM_CONS_LOOKUP[element];
    elementConstructor(n1, n2, gain);

    

    return true;
}