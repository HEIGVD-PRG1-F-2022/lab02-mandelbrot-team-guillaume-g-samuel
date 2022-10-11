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
int generate(int x, int y) {

    int iteration = 0;
    int xTemp;
    while (x * x + y * y <= 2 * 2 && iteration < max_iteration) {
        xTemp = x * x - y * y;
        y = 2 * x * y;
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

std::vector<std::vector<int>> calcRect (std::array<double, 2> p1, std::array<double, 2> p2){

    int width = 60, height = 60;
    std::vector<std::vector<int>> array(width, std::vector<int>(height, 0));

    for (int x = 0; x < array.size(); x++) {
        for (int y = 0; y < array[x].size(); y++) {


            array[x][y] = generate(y, x);
        }
    }

    return array;

}

int main() {

//  nX,      nY,   levelOfZoom, FocusPoint
// height, width,      0.7,       {0, 0}
    /*
    double intervaleOfX = (x2 - x1)/levelOfZoom / nX;
    double intervaleOfY = (y2 - y1)/levelOfZoom / nY;

    double x0;
    double y0 = focusPoint.at(1) + intervaleOfY * pY;

    if (focusPoint.at(0) - x1 > intervaleOfX * pX)
        x0 = x1 + intervaleOfX * pX;*/



    std::array<double, 2> p1 = {x1, y1}, p2 = {x2, y2};

    displayArray(calcRect(p1, p2));

    return 0;
}