#include <vector>
#include "mandelbrot.h"

/****************/
/* IMPORTANT!!! */
/* DON'T MODIFY */
/****************/

int main() {
    // x/y size
    const int width = 12500;
    const int height = 12500;

    // output array
    std::vector<int> plot(width * height, 0);

    // computation
    mandelbrot(width, height, plot.data());

    return 0;
}
