#ifndef APPARAT_MATRIX_H_
#define APPARAT_MATRIX_H_
#include <stddef.h>
#include "types.h"

#define MATRIX_ERROR(name, msg) MatrixError_ ## name,
typedef enum MatrixError
{
    #include "tables/matrix_errors.table.h"
}
MatrixError_E;
#undef MATRIX_ERROR

typedef struct Matrix
{
    size_t rows;
    size_t cols;
    Real_T elements[];
}
Matrix_S;

const char *matrix_showError(MatrixError_E err);

Matrix_S *matrix_new(size_t rows, size_t cols);

static inline void matrix_set(Matrix_S *m, size_t i, size_t j, Real_T value)
{
    if (m != NULL)
    {
        m->elements[(m->rows * i) + j] = value;
    }
}

static inline void matrix_get(Matrix_S *m, size_t i, size_t j, Real_T *value)
{
    if (m != NULL && value != NULL)
    {
        *value = m->elements[(m->rows * i) + j];
    }
}

#endif // APPARAT_MATRIX_H_