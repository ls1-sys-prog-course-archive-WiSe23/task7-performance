#include <cstdlib>
#include <cstring>
#include <random>

#include "matrix.h"

/*****************/
/* IMPORTANT!!!  */
/* DON'T MODIFY  */
/*****************/

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

int main() {
    int n = 1600;

    // Input matrices
    std::vector<float> a(n * n, 0.0f);
    std::vector<float> b(n * n, 0.0f);

    // Output matrices
    std::vector<float> c_solution(n * n, 0.0f);

    // Initialize
    initialize_matrix(a.data(), n);
    initialize_matrix(b.data(), n);

    matrix_multiply(a.data(),b.data(), c_solution.data(), n);

    return 0;
}
