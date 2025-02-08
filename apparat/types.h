#ifndef APPARAT_TYPES_H_
#define APPARAT_TYPES_H_

typedef double Real_T;

typedef enum BitField
{
    BitField_None     =  0, // 0b 00 00 00
    BitField_BitZero  =  1, // 0b 00 00 01
    BitField_BitOne   =  2, // 0b 00 00 10
    BitField_BitTwo   =  4, // 0b 00 01 00
    BitField_BitThree =  8, // 0b 00 10 00
    BitField_BitFour  = 16, // 0b 01 00 00
    BitField_BitFive  = 32, // 0b 10 00 00
}
BitField_E;

#endif // APPARAT_TYPES_H_