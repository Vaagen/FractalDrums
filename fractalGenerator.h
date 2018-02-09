//fractalgenerator.h
#ifndef __fractalGenerator_included__
#define __fractalGenerator_included__

#include <armadillo>
#include <iostream>
#include <math.h>


namespace fractalGenerator{
  double getOrientation(double& x0, double& y0, double& x1, double& y1, int R[4]);
  void generator(arma::mat& coords, int index0, int index8, int currentLevel, int goalLevel);
  void generateLineCoords(arma::mat& coords, int startIndex, double x0, double y0, double x1, double y1, int goalLevel);
  void generateSquareCoords(arma::mat& coords, double width, int goalLevel, bool rotate45deg);
}//namespace

#endif // #ifndef __fractalGenerator_included__
