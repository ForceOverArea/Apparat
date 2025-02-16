// File is intentionally included multiple times
#ifndef ELEMENT_TYPE
#define ELEMENT_TYPE(name, config)
#endif
// NOTE: the function names specified for the 'flux callback' and 'constructor' 
//       arguments must be defined in a header file, ideally element_fluxcalcs
//
//           name       config
ELEMENT_TYPE(Resistor,  resistor_config)
// ELEMENT_TYPE(Voltage,   )
// ELEMENT_TYPE(Current,   )