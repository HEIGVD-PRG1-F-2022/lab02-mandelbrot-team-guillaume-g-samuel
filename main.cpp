/*
 * Labo: mandelbrot
 * Date: 12.10.2022
 * Description: The main file. Contains the display too.
 * Authors: Guillaume Gonin and Samuel Roland
 */
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <string>

#include "mandelBrot.h"
#include "env.h"

//#include <windows.h>


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

using namespace std;

int main() {
    //system(("chcp "s + std::to_string(CP_UTF8)).c_str());

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
        switch ((char) input.at(0)) {
            case '+':
                levelOfZoom = levelOfZoom == 1 ? levelOfZoom + 1
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