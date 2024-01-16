#include "matrix.h"

#include <immintrin.h>

#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <random>
#include <thread>

namespace chrono = std::chrono;

void naive_matrix_multiply(float *a, float *b, float *c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i * n + j] = 0.0f;
            for (int k = 0; k < n; k++) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}

#ifdef __cplusplus
extern "C" {
#endif

void matrix_multiply(float *a, float *b, float *c, int n) {
    naive_matrix_multiply(a, b, c, n);
}

#ifdef __cplusplus
}
#endif