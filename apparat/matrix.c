#include <stdlib.h>
#include "matrix.h"

#define MATRIX_ERROR(name, msg) msg,
const char *MATRIX_ERROR_MESSAGE_TABLE[] =
{
    #include "tables/matrix_errors.table.h"
};
#undef MATRIX_ERROR

const char *matrix_showError(MatrixError_E err)
{
    return MATRIX_ERROR_MESSAGE_TABLE[err];
}

Matrix_S *matrix_new(size_t rows, size_t cols)
{
    if (0 == rows || 0 == cols)
    {
        return NULL;
    }

    size_t n_bytes = sizeof (Matrix_S) + (sizeof (Real_T) * rows * cols);   
    Matrix_S *result = malloc(n_bytes);
    
    if (NULL != result)
    {
        result->rows = rows; 
        result->cols = cols;
        for (size_t i = 0; i < rows * cols; i++)
        {
            result->elements[i] = 0.0;
        }
    }

    return result;
}

