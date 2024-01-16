#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <random>

#include "matrix.h"

void optimized_matrix_multiply(float *a, float *b, float *c, int n);

namespace chrono = std::chrono;

float random_float() {
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    std::uniform_real_distribution<float> dist{};
    return dist(gen);
}

void initialize_matrix(float *m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i * n + j] = random_float();
        }
    }
}

void print_matrix(float *m, int n, FILE *fd) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float value = m[i * n + j];
            fprintf(fd, "%5.3f ", value);
        }
        fprintf(fd, "\n");
    }
    fprintf(fd, "\n");
}

double test_function(std::function<void(float *, float *, float *, int)> func,
                     float *a, float *b, float *c, int n) {
    auto start = chrono::steady_clock::now();
    func(a, b, c, n);
    auto end = chrono::steady_clock::now();

    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

void compare_matrices(float *a, float *b, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float first = a[i * n + j];
            float second = b[i * n + j];
            if (std::abs(first - second) > 0.1) {
                fprintf(stderr, "Contents not equal at %d, %d: %f != %f\n", i,
                        j, first, second);
                exit(1);
            }
        }
    }
}

void benchmark() {
    int n = 2700;

    // Input matrices
    std::vector<float> a1(n * n, 0.0f);
    std::vector<float> b1(n * n, 0.0f);

    // Output matrices
    std::vector<float> c_optimized(n * n, 0.0f);
    std::vector<float> c_solution(n * n, 0.0f);

    // Initialize
    initialize_matrix(a1.data(), n);
    initialize_matrix(b1.data(), n);

    // Copy to make sure the second run doesn't use data from the cache
    std::vector<float> a2 = a1;
    std::vector<float> b2 = b1;

    double optimized_time = test_function(optimized_matrix_multiply, a1.data(),
                                          b1.data(), c_optimized.data(), n);
    double solution_time = test_function(matrix_multiply, a2.data(), b2.data(),
                                         c_solution.data(), n);

    compare_matrices(c_optimized.data(), c_solution.data(), n);

    printf("%lf\n", optimized_time);
    printf("%lf\n", solution_time);
}

int main() {
    benchmark();
    return 0;
}