#pragma once

#include "tests/mandelbrot_params.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates mandelbrot and stores the output in plot
 *
 * @param width  number of pixels available horizontally
 * @param height number of pixels available vertically
 * @param plot   output array
 */
void mandelbrot(int width, int height, int* plot);

#ifdef __cplusplus
}
#endif
