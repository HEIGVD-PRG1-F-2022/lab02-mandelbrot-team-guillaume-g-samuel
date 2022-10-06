/*
 * Labo: mandelbrot
 * Release date: october 2022
 * Project: A small mandelbrot implementation in the command line in C++
 * Authors: Guillaume Gonin and Samuel Roland
 */
#include <iostream>
#include <vector>

const int max_iteration = 1000;

// Implementation of this pseudocode:
// https://en.wikipedia.org/wiki/Mandelbrot_set#Computer_drawings
int generate(int x0, int y0) {
    double x = 0.0;
    double y = 0.0;
    int iteration = 0;
    int xTemp;
    while (x * x + y * y <= 2 * 2 && iteration < max_iteration) {
        xTemp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xTemp;
        iteration++;
    }
    return iteration;
}

void displayArray(std::vector<std::vector<int>> array) {
    for (int x = 0; x < array.size(); x++) {
        for (int y = 0; y < array[x].size(); y++) {
            std::cout << "["<< array[x][y] << "]";
        }
        std::cout << std::endl;
    }
}

int main() {
    int width = 100, height = 100;
    std::vector<std::vector<int>> array(width, std::vector<int>(height, 0));
    for (int x = 0; x < array.size(); x++) {
        for (int y = 0; y < array[x].size(); y++) {
            array[x][y] = generate(x, y);
        }
    }

    displayArray(array);

    return 0;
}