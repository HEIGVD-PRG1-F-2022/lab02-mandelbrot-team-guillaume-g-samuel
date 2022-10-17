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
    //an array containing all color to use, the last elements is used for the MAX_ITERATION only.
    array<int, 7> colors = {34, 30, 36, 32, 31, 33, 35};

    int color = (val == MAX_ITERATION) ? colors.size() - 1 : colors.at(val % (colors.size() - 1));

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
void displayArray(vector<vector<int>> array, string message = "") {
    string rectangle = "";//big rectangle displayed containing all cases as string

    for (int y = 0; y < array.size(); y++) {
        for (int x = 0; x < array.at(y).size(); x++) {
            rectangle += color(array.at(x).at(y));
        }
        rectangle += "\n";
    }

    //Position the output cursor to the top left to visually overwrite the current rectangle
    //Help: https://stackoverflow.com/questions/54250401/how-to-control-a-cursor-position-in-c-console-application
    printf("%c[%d;%df", 0x1B, 0, 0);
    cout << rectangle;

    //Print the message if defined
    cout << message << endl;

    //Print the options legend
    cout
            << "[r] run animation, [+] zoom in, [-] zoom out, [a/A] left, [d/D] "
               "right, [w/W] up, [s/S] down, [q] quit"
            << endl;
}

//Clear the screen (support Windows, Linux and MacOS)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
//if it's windows (32) we can execute this line to change the terminal to UTF8 and as that have a display for ours colors.
#ifdef _WIN32
    system(("chcp "s + to_string(CP_UTF8)).c_str());
#endif

    //Starting coordinates of the mandelbrot set (the X and Y point of the plan where the entire figure is visible)
    const double X1 = -2;
    const double Y1 = 1.12;
    const double X2 = 0.47;
    const double Y2 = -1.12;

    //Visual table sizes (numbers of cases displayed in height and width, each case contains "@@")
    const int ARRAY_WIDTH = 55;
    const int ARRAY_HEIGHT = 55;

    //The offsets to navigate (right/left/up/down) into the mandelbrot, the zoom level allow us to zoom in/out
    double offsetX = -0.761574;
    double offsetY = -0.0847596;
    double zoom = 1;

    array<double, 2> center = {offsetX, offsetY};
    string message;//a message for the user displayed above the options legend
    char option;   //the option given by the user

    clearScreen();

    //Infinite loop with display of array, asking for option, displaying the array again, etc
    do {
        //Calculate the array values to fill the values for each case, and display the array
        displayArray(calcRect(center, X2 - X1, Y1 - Y2, ARRAY_WIDTH, ARRAY_HEIGHT, zoom), message);

        //Read the user option if the last given option wasn't the zoom animation
        if (option != 'r') {
            cout << "Your choice: ";
            cin >> option;
            option = tolower(option);
            clearScreen();
        }

        message = "";//empty the message
        switch (option) {
            case 'r':
                usleep(10000);     //sleep 100ms
                zoom = zoom / 0.97;//increase the zoom level
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
                message = "Option '";
                message.append(1, option);
                message += "' not supported...";
                break;
        }
        //Redefine the center point after the change of offsets values
        center = {offsetX, offsetY};
    } while (true);

    return EXIT_SUCCESS;
}