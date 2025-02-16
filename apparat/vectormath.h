#ifndef APPARAT_VECTORMATH_H_
#define APPARAT_VECTORMATH_H_
#include "types.h"

void zero(VQuant_S *v);
VQuant_S elemwise_add(VQuant_S a, VQuant_S b);
VQuant_S elemwise_subtract(VQuant_S a, VQuant_S b);
VQuant_S elemwise_multiply(VQuant_S a, VQuant_S b);
VQuant_S elemwise_divide(VQuant_S a, VQuant_S b);

#endif // APPARAT_VECTORMATH_H_