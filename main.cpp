/**
 * The main file. Contains the display too.
 *
 * @name mandelbrot
 * @date 12.10.2022
 * @authors Guillaume Gonin and Samuel Roland
 */

//Externals imports
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <string>
//If it's windows (32) we can import that for the color in terminal.
#ifdef _WIN32
#include <windows.h>
#endif

//Internals imports
#include "mandelBrot.h"
#include "env.h"


using namespace std;

/**
 * Used to write a mandelbrot point with color depending of the number of iteration.
 *
 * @param val number of iteration
 */
void color(int val) {
    //an array containing all color to use, the last elements is used for the max_iteration only.
    array<int, 7> colors = {34, 30, 36, 32, 31, 33, 35};

    int color = (val == max_iteration) ? colors.size()-1 : colors.at(val % colors.size()-1);

    //This if will print the color point but only if it's more than a number of iteration (to have only the interesting shape printed).
    if (val > colors.size()-1) {
        cout << "\033[33;" << color << "m"
                  << "@@"
                  << "\033[0m";
    } else {
        cout << "  ";
    }
}

/**
 * Used to print all points of the array
 *
 * @param array The array to print
 */
void displayArray(std::vector<std::vector<int>> array) {
    for (int y = 0; y < array.size(); y++) {
        for (int x = 0; x < array.at(y).size(); x++) {
            color(array.at(x).at(y));
        }
        std::cout << std::endl;
    }
    //we print a little line for explain the control keys.
    std::cout
            << "[+] for zoom in, [-] for zoom out, [a/A] for go to left, [d/D] for "
               "go to right, [w/W] for go up, [s/S] for go down, [q] to quit"
            << std::endl;
}

int main() {
    //if it's windows (32) we can execute this line to change the terminal to UTF8 and as that have a display for ours colors.
	#ifdef _WIN32
    system(("chcp "s + std::to_string(CP_UTF8)).c_str());
	#endif

    //all coords describing the interesting part of the mandelbrot
    const double x1 = -2;
    const double y1 = 1.12;
    const double x2 = 0.47;
    const double y2 = -1.12;

    //the offset allow use to navigate (right/left and up/down) into the mandelbrot, the levelOfZoom allow us to zoom in/out
    double offsetX = -0.761574;
    double offsetY = -0.0847596;
    double levelOfZoom = 1;

    std::array<double, 2> center = {offsetX, offsetY};

    //based on the value we got we can create the mandelbrot and display the array
    displayArray(calcRect(center, x2 - x1, y1 - y2, 60, 60, levelOfZoom));

    //be aware of a user's input
    std::string input;
    std::getline(std::cin, input);

    //depending on the input we do the right action
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
                offsetX += 0.1 / levelOfZoom;
                break;
            case 'a':
            case 'A':
                offsetX -= 0.1 / levelOfZoom;
                break;
            case 'w':
            case 'W':
                offsetY += 0.1 / levelOfZoom;
                break;
            case 's':
            case 'S':
                offsetY -= 0.1 / levelOfZoom;
                break;
            case 'q':
                return EXIT_SUCCESS;
        }
        //we recalculate the center and display the new mandelbrot
        center = {offsetX, offsetY};
        displayArray(calcRect(center, x2 - x1, y1 - y2, 60, 60, levelOfZoom));
        std::cin >> input;
    }

    return EXIT_SUCCESS;
}