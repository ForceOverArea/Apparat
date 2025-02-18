#include "structures.h"

// for reference:
// typedef RuntimeError_E (*FluxCallback_T)(void *, Node_S *, Node_S *, VQuant_S *);
// typedef StructuresError_E (*ElementConstructor_T)(Problem_S *,Node_S *, Node_S *, VQuant_S);

// resistor functions
RuntimeError_E resistor_fluxcalc(Element_S *elem, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux);
StructuresError_E resistor_new(Problem_S *p, Node_S *n1, Node_S *n2, VQuant_S gain);

// voltage source functions
RuntimeError_E voltage_fluxcalc(Element_S *elem_ptr, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux);
StructuresError_E voltage_new(Problem_S *p, Node_S *n1, Node_S *n2, VQuant_S gain);

// current source functions
RuntimeError_E current_fluxcalc(Element_S *elem_ptr, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux);
StructuresError_E current_new(Problem_S *p, Node_S *n1, Node_S *n2, VQuant_S gain);

const ElementConfig_S RESISTOR_CONFIG = 
{
    .constructor = &resistor_new,
    .flux = &resistor_fluxcalc,
    .dimensionality = 1U,
};

const ElementConfig_S VOLTAGE_CONFIG = 
{
    .constructor = &voltage_new,
    .flux = &voltage_fluxcalc,
    .dimensionality = 1U,
};

const ElementConfig_S CURRENT_CONFIG = 
{
    .constructor = &current_new,
    .flux = &current_fluxcalc,
    .dimensionality = 1U,
};