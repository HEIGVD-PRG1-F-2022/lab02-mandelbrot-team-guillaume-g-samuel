/* Labo: mandelbrot
 * Date: 12.10.2022
* Description: A small mandelbrot implementation in the command line in C++
 * Authors: Guillaume Gonin and Samuel Roland
 */

#include "mandelBrot.h"
#include <vector>
#include <array>


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

std::vector<std::vector<int>> calcRect(std::array<double, 2> p1, std::array<double, 2> p2, int nX, int nY) {

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
