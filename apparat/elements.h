#include "structures.h"

// resistor functions
RuntimeError_E resistor_fluxcalc(void *elem, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux);
RuntimeError_E resistor_new(Problem_S* a, Node_S *inputNode, Node_S *outputNode, VQuant_S gain);

const ElementConfig_S resistor_config = 
{
    .dimension = 1,
    .flux = &resistor_fluxcalc,
    .constructor = &resistor_new,
};