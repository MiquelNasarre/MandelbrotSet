#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cstring>
#include<direct.h>

#define Iterations 20000
#define X0 -1.2496
#define X1 -1.1879
#define Y0 0.1293
#define Y1 0.1903
#define Xpoints 2000
#define Ypoints 2000
#define OrbitFinder 4
#define GridLenght 3
#define Epsilon 1e-6

#define NumberOfFiles 16
#define IntervalFiles { 0, 2, 5, 10, 25, 50, 100, 150, 250, 450, 800, 1200, 1500, 2000, 3000, 4000 }

#define PlotPrecition "%.8f %.8f\n"
#define DataFilesDirectory "../DataFiles/"
#define DirectoryStringLenght 13

void createMandelbrotFileRecursive(int depth);
bool Iterate(double a, double b);
void fullFILL(FILE* file, double x0, double y0, double x1, double y1, int xpoints, int ypoints);
void PixelFILL(FILE* file, double x0, double y0, double x1, double y1, int xpoints, int ypoints);
void RecursiveGridFiller(FILE* file, double x0, double y0, double x1, double y1, int xpoints, int ypoints, int gridLenght, int depth);

void createMandelbrotFilesColor();