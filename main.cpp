#include <iostream>

// Implementation of this pseudocode:
// https://en.wikipedia.org/wiki/Mandelbrot_set#Computer_drawings
void generate(int x0, int y0) {
    double x = 0.0;
    double y = 0.0;
    int iteration = 0;
    int max_iteration = 1000;
    int xtemp;
    while (x * x + y * y <= 2 * 2 && iteration < max_iteration) {
        xtemp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xtemp;
        iteration++;
    }
}

int main() {
    return 0;
}