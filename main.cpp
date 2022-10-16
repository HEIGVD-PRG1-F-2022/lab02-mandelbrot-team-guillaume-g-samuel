/**
 * The main file. Contains the display too.
 *
 * @name mandelbrot
 * @date 12.10.2022
 * @authors Guillaume Gonin and Samuel Roland
 */

//Externals imports
#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "unistd.h"

//If it's windows (32) we can import that for the color in terminal.
#ifdef _WIN32
#include <windows.h>
#endif

//Internals imports
#include "env.h"
#include "mandelBrot.h"


using namespace std;

/**
 * Used to write a mandelbrot point with color depending of the number of iteration.
 *
 * @param val number of iteration
 * @return the string to print with a color
 */
string color(int val) {
    //an array containing all color to use, the last elements is used for the max_iteration only.
    array<int, 7> colors = {34, 30, 36, 32, 31, 33, 35};

    int color = (val == max_iteration) ? colors.size() - 1 : colors.at(val % (colors.size() - 1));

    //This if will print the color point but only if it's more than a number of iteration (to have only the interesting shape printed).
    string coloredText = "  ";
    if (val > colors.size() - 1) {
        coloredText = "\033[33;" + to_string(color) + "m" + "@@" + "\033[0m";
    }
    return coloredText;
}

/**
 * Used to print all points of the array
 *
 * @param array The array to print
 */
void displayArray(std::vector<std::vector<int>> array, string message = "") {
    string rectangle = "";//big rectangle displayed containing all cases as string

    for (int y = 0; y < array.size(); y++) {
        for (int x = 0; x < array.at(y).size(); x++) {
            rectangle += color(array.at(x).at(y));
        }
        rectangle += "\n";
    }
    cout << rectangle;

    //Print the message if defined
    cout << message << endl;

    //Print the options legend
    std::cout
            << "[r] run animation, [+] zoom in, [-] zoom out, [a/A] go left, [d/D] "
               "go right, [w/W] go up, [s/S] go down, [q] quit"
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

    //the offset allow use to navigate (right/left and up/down) into the mandelbrot, the zoom allow us to zoom in/out
    double offsetX = -0.761574;
    double offsetY = -0.0847596;
    double zoom = 1;

    std::array<double, 2> center = {offsetX, offsetY};
    string message;//a message for the user displayed above the options legend

    //based on the value we got we can create the mandelbrot and display the array
    displayArray(calcRect(center, x2 - x1, y1 - y2, 55, 55, zoom));

    //be aware of a user's input
    string input;
    char option;

    //depending on the input we do the right action
    do {
        if (option != 'r') {
            std::cin >> input;
            option = tolower((char) input.at(0));
        }
        message = "";//empty the message
        switch (option) {
            case 'r':
                usleep(50000);//sleep 100ms
                zoom = zoom / 0.95;
                break;
            case '+':
                zoom = zoom == 1 ? zoom + 1
                                 : pow(zoom, 2);
                break;
            case '-':
                zoom = zoom == 2 ? 1 : sqrt(zoom);
                break;
            case 'd':
                offsetX += 0.1 / zoom;
                break;
            case 'a':
                offsetX -= 0.1 / zoom;
                break;
            case 'w':
                offsetY += 0.1 / zoom;
                break;
            case 's':
                offsetY -= 0.1 / zoom;
                break;
            case 'q':
                return EXIT_SUCCESS;
            default:
                message = "Option '" + input + "' not supported...";
                break;
        }
        //we recalculate the center and display the new mandelbrot
        center = {offsetX, offsetY};
        system("clear");
        displayArray(calcRect(center, x2 - x1, y1 - y2, 60, 60, zoom), message);
    } while (true);

    return EXIT_SUCCESS;
}