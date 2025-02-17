#include "structures.h"

// for reference:
// typedef RuntimeError_E (*FluxCallback_T)(void *, Node_S *, Node_S *, VQuant_S *);
// typedef StructuresError_E (*ElementConstructor_T)(Problem_S *,Node_S *, Node_S *, VQuant_S);

// resistor functions
RuntimeError_E resistor_fluxcalc(void *elem, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux);
StructuresError_E resistor_new(Problem_S *p, Node_S *n1, Node_S *n2, VQuant_S gain);

// voltage source functions
RuntimeError_E voltage_fluxcalc(void *elem_ptr, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux);
StructuresError_E voltage_new(Problem_S *p, Node_S *n1, Node_S *n2, VQuant_S gain);

const ElementConfig_S resistor_config = 
{
    .dimension = 1,
    .constructor = &resistor_new,
};

const ElementConfig_S voltage_config = 
{
    .dimension = 1,
    .constructor = &voltage_new,
};