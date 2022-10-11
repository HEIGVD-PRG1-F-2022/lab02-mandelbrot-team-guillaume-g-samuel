/*
 * Labo: mandelbrot
 * Release date: october 2022
 * Project: A small mandelbrot implementation in the command line in C++
 * Authors: Guillaume Gonin and Samuel Roland
 */
#include <iostream>
#include <vector>
#include <array>

const int max_iteration = 1000;
const double x1 = -2;
const double y1 = 1.12;
const double x2 = 0.47;
const double y2 = -1.12;

// Implementation of this pseudocode:
// https://en.wikipedia.org/wiki/Mandelbrot_set#Computer_drawings
int generate(int pX, int pY, int nX, int nY, double levelOfZoom) {
    double x0 = (x1 + ((((x2 - x1)/levelOfZoom) / nX) * pX));
    double y0 = (y1 + ((((y2 - y1)/levelOfZoom) / nY) * pY));
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

void color(int val) {
    std::array<int, 7> colors = {34, 30, 36, 32, 31, 33, 35};
    int color = (val == max_iteration) ? 35 : colors.at(val%6);
    std::cout << "\033[33;" << color << "m"
              << "@@"
              << "\033[0m";
}

void displayArray(std::vector<std::vector<int>> array) {
    for (int x = 0; x < array.size(); x++) {
        for (int y = 0; y < array[x].size(); y++) {
            // std::cout << "[" << ((array[x][y] == 1000) ? 0 : array[x][y])
            //           << "]";
            color(array[x][y]);
        }
        std::cout << std::endl;
    }
}

int main() {

    int width = 60, height = 60;
    std::vector<std::vector<int>> array(width, std::vector<int>(height, 0));
    for (int x = 0; x < array.size(); x++) {
        for (int y = 0; y < array[x].size(); y++) {

            array[x][y] = generate(y, x, height, width, 0.7);
        }
    }

    displayArray(array);

    return 0;
}