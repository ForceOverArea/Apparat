#ifndef APPARAT_ERRORS_H_
#define APPARAT_ERRORS_H_

#define APPARAT_ERROR(class, name, msg) class ## _ ## name,
typedef enum ApparatError
{
    #include "tables/apparat_errors.table.h"
}
ApparatError_E;
#undef APPARAT_ERROR

#define CHECK_STAT(apparatErrorExpr) if (CommonError_Success != (apparatErrorExpr)) { return (apparatErrorExpr); }

#endif // APPARAT_ERRORS_H_