// File is intentionally included multiple times
#ifndef ELEMENT_TYPE
#define ELEMENT_TYPE(name, dims, func, cons)
#endif
// NOTE: the function names specified for the 'flux callback' and 'constructor' 
//       arguments must be defined in a header file, ideally element_fluxcalcs
//
//           name       dimensions      flux callback       constructor
ELEMENT_TYPE(Resistor,  1,              resistor_fluxcalc,  resistor_new)
ELEMENT_TYPE(Voltage,   1,              voltage_fluxcalc,   voltage_new)
ELEMENT_TYPE(Current,   1,              current_fluxcalc,   current_new)