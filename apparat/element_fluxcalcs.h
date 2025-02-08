#ifndef APPARAT_ELEMENT_FLUX_CALCS_H_
#define APPARAT_ELEMENT_FLUX_CALCS_H_
#include "types.h"

void resistor_fluxcalc(void *elem, void *inputNode, void *outputNode, Real_T *flux);
void resistor_new(void *inputNode, void *outputNode, Real_T *gain);

void voltage_fluxcalc(void *elem, void *inputNode, void *outputNode, Real_T *flux);
void voltage_new(void *inputNode, void *outputNode, Real_T *gain);

void current_fluxcalc(void *elem, void *inputNode, void *outputNode, Real_T *flux);
void current_new(void *inputNode, void *outputNode, Real_T *gain);

#endif // APPARAT_ELEMENT_FLUX_CALCS_H_