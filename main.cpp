/*
 * Labo: mandelbrot
 * Release date: october 2022
 * Project: A small mandelbrot implementation in the command line in C++
 * Authors: Guillaume Gonin and Samuel Roland
 */
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

const int max_iteration = 1000;

// Implementation of this pseudocode:
// https://en.wikipedia.org/wiki/Mandelbrot_set#Computer_drawings
int generate(double x0, double y0) {

    double x = 0.0;
    double y = 0.0;

    int iteration = 0;
    double xTemp;
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
    int color = (val == max_iteration) ? 35 : colors.at(val % 6);
    if (val > 6) {
        std::cout << "\033[33;" << color << "m"
                  << "@@"
                  << "\033[0m";
    } else {
        std::cout << "  ";
    }
}

void displayArray(std::vector<std::vector<int>> array) {
    for (int y = 0; y < array.size(); y++) {
        for (int x = 0; x < array.at(y).size(); x++) {
            // std::cout << "[" << ((array[x][y] == 1000) ? 0 : array[x][y])
            //           << "]";
            color(array.at(x).at(y));
        }
        std::cout << std::endl;
    }
    std::cout
        << "[+] for zoom in, [-] for zoom out, [a/A] for go to left, [d/D] for "
           "go to right, [w/W] for go up, [s/S] for go down, [q] to quit"
        << std::endl;
}

double calculateGraphX(int xRef, double x1, double x2, int numberOfX) {
    /* nX,      nY,   levelOfZoom, FocusPoint
     height, width,      0.7,       {0, 0}*/
    double intervaleOfX = (x2 - x1) / numberOfX;

    return x1 + intervaleOfX * xRef;
    /*   double y0 = focusPoint.at(1) + intervaleOfY * pY;

       if (focusPoint.at(0) - x1 > intervaleOfX * pX)
           x0 = x1 + intervaleOfX * pX;*/
}

double calculateGraphY(int yRef, double y1, double y2, int numberOfY) {
    double intervaleOfY = (y2 - y1) / numberOfY;

    return y1 + intervaleOfY * yRef;
}

std::vector<std::vector<int>>
calcRect(std::array<double, 2> p1, std::array<double, 2> p2, int nX, int nY) {

    std::vector<std::vector<int>> array(nX, std::vector<int>(nY, 0));

    for (int x = 0; x < array.size(); x++) {
        for (int y = 0; y < array.at(0).size(); y++) {

            double graphX =
                calculateGraphX(x, p1.at(0), p2.at(0), array.size() - 1);
            double graphY =
                calculateGraphY(y, p1.at(1), p2.at(1), array.at(0).size() - 1);

            array.at(x).at(y) = generate(graphX, graphY);
        }
    }

    return array;
}

std::vector<std::vector<int>> calcRect(std::array<double, 2> pC, double width,
                                       double height, int nX, int nY,
                                       double zoom) {
    std::array<double, 2> p1 = {pC.at(0) - (width / 2) / zoom,
                                pC.at(1) + (height / 2) / zoom},
                          p2 = {pC.at(0) + (width / 2) / zoom,
                                pC.at(1) - (height / 2) / zoom};

    return calcRect(p1, p2, nX, nY);
}

int main() {
    const double x1 = -2;
    const double y1 = 1.12;
    const double x2 = 0.47;
    const double y2 = -1.12;

    double offesetX = -0.761574;
    double offesetY = -0.0847596;
    double levelOfZoom = 1;

    std::array<double, 2> center = {offesetX, offesetY};

    displayArray(calcRect(center, x2 - x1, y1 - y2, 60, 60, levelOfZoom));

    std::string input;
    std::getline(std::cin, input);
    while (true) {
        switch ((char)input.at(0)) {
        case '+':
            levelOfZoom = levelOfZoom == 1 ? pow(levelOfZoom + 1, 2)
                                           : pow(levelOfZoom, 2);
            break;
        case '-':
            levelOfZoom = levelOfZoom == 2 ? 1 : sqrt(levelOfZoom);
            break;
        case 'd':
        case 'D':
            offesetX += 0.1 / levelOfZoom;
            break;
        case 'a':
        case 'A':
            offesetX -= 0.1 / levelOfZoom;
            break;
        case 'w':
        case 'W':
            offesetY += 0.1 / levelOfZoom;
            break;
        case 's':
        case 'S':
            offesetY -= 0.1 / levelOfZoom;
            break;
        case 'q':
            return EXIT_SUCCESS;
        }
        center = {offesetX, offesetY};
        displayArray(calcRect(center, x2 - x1, y1 - y2, 60, 60, levelOfZoom));
        std::cin >> input;
    }

    return EXIT_SUCCESS;
}