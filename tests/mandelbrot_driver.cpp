#include <immintrin.h>

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "mandelbrot.h"

void mandelbrot_optimized(int width, int height, int* plot);

namespace chrono = std::chrono;

/*
void visualize(int width, int height, int* plot) {
    std::string block_elem = "\u2588";
    std::string white = "\033[01;37m";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (plot[i * width + j] == LOOP)
                std::cerr << " ";
            else
                std::cerr << white << block_elem;
        }
        std::cerr << std::endl;
    }
}
*/

double test_function(std::function<void(int, int, int*)> func, int width,
                     int height, int* plot) {
    auto start = chrono::steady_clock::now();
    func(width, height, plot);
    auto end = chrono::steady_clock::now();

    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

bool compare_plots(int width, int height, int* target, int* ref) {
    for (auto i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int first = target[i * width + j];
            int second = ref[i * width + j];
            if (std::abs(first - second) != 0) {
                fprintf(stderr, "Contents not equal at %d, %d: %d != %d\n", i,
                        j, first, second);
                return false;
            }
        }
    }

    return true;
}

void benchmark() {
    // x/y size
    const int width = WIDTH;
    const int height = HEIGHT;

    // output array
    std::vector<int> plot_opt(width * height, 0);
    std::vector<int> plot_base(width * height, 0);

    // computation
    auto optimized_time =
        test_function(mandelbrot_optimized, width, height, plot_opt.data());
    auto solution_time =
        test_function(mandelbrot, width, height, plot_base.data());

    // compare results
    auto match =
        compare_plots(width, height, plot_opt.data(), plot_base.data());
    if (!match) {
        std::cerr << "Test failed" << std::endl;
        exit(1);
    }
    
    // display plots
    // visualize(width, height, plot_base.data());
    // visualize(width, height, plot_opt.data());

    printf("%lf\n", optimized_time);
    printf("%lf\n", solution_time);
}

int main() {
    benchmark();
    return 0;
}
