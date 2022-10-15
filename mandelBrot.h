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

//internals imports
#include "env.h"

#ifndef MANDELBROT_MANDELBROT_H
#define MANDELBROT_MANDELBROT_H

#endif

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
int mandelbrot(double x0, double y0);

/**
 * Calculate the coordX scaled for the mandelbrot from the array's index
 *
 * @param xRef The array's index
 * @param x1 coordX of the left-top corner
 * @param x2 coordX of the right-bottom
 * @param numberOfX number of point on X (basically the array x size)
 * @return the scaled coordX
 */
double calculateGraphX(int xRef, double x1, double x2, int numberOfX);

/**
 * Calculate the coordY scaled for the mandelbrot from the array's index
 *
 * @param yRef The array's index
 * @param y1 coordY of the left-top corner
 * @param y2 coordY of the right-bottom
 * @param numberOfY number of point on Y (basically the array y size)
 * @return the scaled coordY
 */
double calculateGraphY(int yRef, double y1, double y2, int numberOfY);

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
std::vector<std::vector<int>> calcRect(std::array<double, 2> p1, std::array<double, 2> p2, int nX, int nY);

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
std::vector<std::vector<int>>
calcRect(std::array<double, 2> pC, double width, double height, int nX, int nY, double zoom);