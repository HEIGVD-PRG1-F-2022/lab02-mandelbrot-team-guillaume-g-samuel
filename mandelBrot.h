/* Labo: mandelbrot
 * Date: 12.10.2022
 * Description: A small mandelbrot implementation in the command line in C++
 * Authors: Guillaume Gonin and Samuel Roland
 */

#include <vector>
#include <array>

#include "env.h"

#ifndef MANDELBROT_MANDELBROT_H
#define MANDELBROT_MANDELBROT_H

#endif //MANDELBROT_MANDELBROT_H

int generate(double x0, double y0);

double calculateGraphX(int xRef, double x1, double x2, int numberOfX);

double calculateGraphY(int yRef, double y1, double y2, int numberOfY);

std::vector<std::vector<int>> calcRect(std::array<double, 2> p1, std::array<double, 2> p2, int nX, int nY);

std::vector<std::vector<int>>
calcRect(std::array<double, 2> pC, double width, double height, int nX, int nY, double zoom);