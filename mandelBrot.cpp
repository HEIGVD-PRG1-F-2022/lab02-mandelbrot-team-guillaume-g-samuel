/**
 * A small mandelbrot implementation in the command line in C++
 *
 * @name mandelbrot
 * @date 12.10.2022
 * @authors Guillaume Gonin and Samuel Roland
 */

//Externals imports
#include <array>
#include <vector>

//Internals imports
#include "mandelBrot.h"

using namespace std;

/**
 * Generate a point of the mandelbrot
 *
 * Implementation of this pseudocode:
 * https://en.wikipedia.org/wiki/Mandelbrot_set#Computer_drawings
 *
 * @param x0 coordX of the point of the mandelbrot
 * @param y0 coordY of the point of the mandelbrot
 * @return the number of iteration done
 */
int mandelbrot(double x0, double y0) {

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

/**
 * Calculate the coordX scaled for the mandelbrot from the array's index
 *
 * @param xRef The array's index
 * @param X1 coordX of the left-top corner
 * @param X2 coordX of the right-bottom
 * @param numberOfX number of point on X (basically the array x size)
 * @return the scaled coordX
 */
double calculateGraphX(int xRef, double X1, double X2, int numberOfX) {
    double intervaleOfX = (X2 - X1) / numberOfX;

    return X1 + intervaleOfX * xRef;
}

/**
 * Calculate the coordY scaled for the mandelbrot from the array's index
 *
 * @param yRef The array's index
 * @param Y1 coordY of the left-top corner
 * @param Y2 coordY of the right-bottom
 * @param numberOfY number of point on Y (basically the array y size)
 * @return the scaled coordY
 */
double calculateGraphY(int yRef, double Y1, double Y2, int numberOfY) {
    double intervaleOfY = (Y2 - Y1) / numberOfY;

    return Y1 + intervaleOfY * yRef;
}

/**
 * Calculate the number of iteration (the mandelbrot) for each point of an array (created on the method)
 * Using: left-top and right-bottom scaled corner
 *
 * @param p1 left-top corner (x,y)
 * @param p2 right bottom corner (x,y)
 * @param nX size of the array on x
 * @param nY size of the array on y
 * @return return the array
 */
vector<vector<int>> calcRect(array<double, 2> p1, array<double, 2> p2, int nX, int nY) {

    //create a two-dimensional vector based on the parameter given
    vector<vector<int>> array(nX, vector<int>(nY, 0));

    for (int x = 0; x < array.size(); x++) {
        for (int y = 0; y < array.at(0).size(); y++) {
            //for each point, we need to calculate the scaled x,y point and then to assign on the two-dimensional vector the number of iteration.
            double graphX =
                    calculateGraphX(x, p1.at(0), p2.at(0), array.size() - 1);
            double graphY =
                    calculateGraphY(y, p1.at(1), p2.at(1), array.at(0).size() - 1);

            array.at(x).at(y) = mandelbrot(graphX, graphY);
        }
    }

    return array;
}

/**
 * Calculate the number of iteration (the mandelbrot) for each point of an array (created on the method)
 * Using: the center of the array (but scaled)
 *
 * @param pC center (x,y)
 * @param width width of the scaled x (about width/2 = centerX)
 * @param height height of the scaled y (about height/2 = centerY)
 * @param nX size of the array on x
 * @param nY size of the array on y
 * @param zoom the zoom level
 * @return return the array
 */
vector<vector<int>> calcRect(array<double, 2> pC, double width,
                             double height, int nX, int nY,
                             double zoom) {
    //we calculate the two points (left-top and right-bottom corners) based on the width/height, the center and the zoom.
    array<double, 2> p1 = {pC.at(0) - (width / 2) / zoom,
                           pC.at(1) + (height / 2) / zoom},
                     p2 = {pC.at(0) + (width / 2) / zoom,
                           pC.at(1) - (height / 2) / zoom};

    //we can now just use the normal method to generate the array.
    return calcRect(p1, p2, nX, nY);
}
