#include "mandelbrot.h"

#include <immintrin.h>

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

int mandelbrot_calc_base(float x, float y) {
    auto re = x;
    auto im = y;

    for (auto i = 0; i < LOOP; i++) {
        float re2 = re * re;
        float im2 = im * im;

        // verify if f(z) diverges to infinity
        if (re2 + im2 > 4.0f) return i;

        im = 2 * re * im + y;
        re = re2 - im2 + x;
    }

    return LOOP;
}

void naive_mandelbrot(int width, int height, int* plot) {
    float dx = (X_END - X_START) / (width - 1);
    float dy = (Y_END - Y_START) / (height - 1);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float x = X_START + j * dx;  // real value
            float y = Y_END - i * dy;    // imaginary value

            auto result = mandelbrot_calc_base(x, y);
            plot[i * width + j] = result;
        }
    }
}

#ifdef __cplusplus
extern "C" {
#endif

void mandelbrot(int width, int height, int* plot) {
    naive_mandelbrot(width, height, plot);
}

#ifdef __cplusplus
}
#endif
