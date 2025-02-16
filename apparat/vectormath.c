#include "vectormath.h"

VQuant_S elemwise_add(VQuant_S a, VQuant_S b)
{
    VQuant_S result;

    result.fst = a.fst + b.fst;
    result.snd = a.snd + b.snd;
    result.thd = a.thd + b.thd;
    result.lst = a.lst + b.lst;

    return result;
}

VQuant_S elemwise_subtract(VQuant_S a, VQuant_S b)
{
    VQuant_S result;

    result.fst = a.fst - b.fst;
    result.snd = a.snd - b.snd;
    result.thd = a.thd - b.thd;
    result.lst = a.lst - b.lst;

    return result;
}

VQuant_S elemwise_multiply(VQuant_S a, VQuant_S b)
{
    VQuant_S result;

    result.fst = a.fst * b.fst;
    result.snd = a.snd * b.snd;
    result.thd = a.thd * b.thd;
    result.lst = a.lst * b.lst;

    return result;
}

VQuant_S elemwise_divide(VQuant_S a, VQuant_S b)
{
    VQuant_S result;

    result.fst = a.fst / b.fst;
    result.snd = a.snd / b.snd;
    result.thd = a.thd / b.thd;
    result.lst = a.lst / b.lst;

    return result;
}
