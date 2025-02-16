#include "structures.h"


// resistor functions
RuntimeError_E resistor_fluxcalc(void *elem, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux);
RuntimeError_E voltage_fluxcalc(void *elem_ptr, Node_S *inputNode, Node_S *outputNode, VQuant_S *flux);

const ElementConfig_S resistor_config = 
{
    .connectToInput = true,
    .connectToOutput = true,
    .dimension = 1,
    .flux = &resistor_fluxcalc,
    .constructor = &resistor_new,
};

const ElementConfig_S voltage_config = 
{
    .connectToInput = true,
    .connectToOutput = false,
    .dimension = 1,
    .flux = &voltage_fluxcalc,
    .constructor = &voltage_new,
};