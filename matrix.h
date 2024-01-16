#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates the matrix product of a and b and stores the output in c
 * 
 * @param a n*n matrix
 * @param b n*n matrix
 * @param c n*n matrix (empty)
 * @param n size
 */
void matrix_multiply(float *a, float *b, float *c, int n);

#ifdef __cplusplus
}
#endif