#include "fractalGenerator.h"

double fractalGenerator::getOrientation(double& x0, double& y0, double& x1, double& y1, int R[4]){
  // Get axis conversions for different orientations.
  // Returns distance between points.
  double delta;
  if(x0<x1&&y0==y1){
    delta = (x1-x0)/4;
    R[0]=1;
    R[1]=1;
    R[2]=0;
    R[3]=0;
  }else if(x0>x1&&y0==y1){
    delta = (x0-x1)/4;
    R[0]=-1;
    R[1]=-1;
    R[2]=0;
    R[3]=0;
  }else if(x0==x1&&y0>y1){
    delta = (y0-y1)/4;
    R[0]=0;
    R[1]=0;
    R[2]=-1;
    R[3]=1;
  }else if(x0==x1&&y0<y1){
    delta = (y1-y0)/4;
    R[0]=0;
    R[1]=0;
    R[2]=1;
    R[3]=-1;
  }else{ std::cout << "Bad coordinates sent to fractalGenerator::getOrientation.  (" << x0 << " , " << y0 << "), ("<< x1 << ", " << y1 << ")" << std::endl;}
  return delta;
}

void fractalGenerator::generator(arma::mat& coords, int index0, int index8, int currentLevel, int goalLevel){
  double x0 = coords(index0,0);
  double y0 = coords(index0,1);
  double x8 = coords(index8,0);
  double y8 = coords(index8,1);
  // Getting steplength and orientation factors R.
  int R [4];
  double delta;
  delta = fractalGenerator::getOrientation(x0,y0,x8,y8,R);
  // Inserting new coordinates for corners between point 0 and 8.
  int deltaIndex = (index8-index0)/8;
  coords(index0 +   deltaIndex,0) = x0+  R[0]*delta;
  coords(index0 + 2*deltaIndex,0) = x0+  R[0]*delta+R[3]*delta;
  coords(index0 + 3*deltaIndex,0) = x0+2*R[0]*delta+R[3]*delta;
  coords(index0 + 4*deltaIndex,0) = x0+2*R[0]*delta;
  coords(index0 + 5*deltaIndex,0) = x0+2*R[0]*delta-R[3]*delta;
  coords(index0 + 6*deltaIndex,0) = x0+3*R[0]*delta-R[3]*delta;
  coords(index0 + 7*deltaIndex,0) = x0+3*R[0]*delta;

  coords(index0 +   deltaIndex,1) = y0           +  R[2]*delta;
  coords(index0 + 2*deltaIndex,1) = y0+R[1]*delta+  R[2]*delta;
  coords(index0 + 3*deltaIndex,1) = y0+R[1]*delta+2*R[2]*delta;
  coords(index0 + 4*deltaIndex,1) = y0           +2*R[2]*delta;
  coords(index0 + 5*deltaIndex,1) = y0-R[1]*delta+2*R[2]*delta;
  coords(index0 + 6*deltaIndex,1) = y0-R[1]*delta+3*R[2]*delta;
  coords(index0 + 7*deltaIndex,1) = y0           +3*R[2]*delta;

  //Calling recursively if we want to go deeper.
  if(currentLevel<goalLevel){
    currentLevel++;
    for(int i=index0; i < index8; i+=deltaIndex){
      fractalGenerator::generator(coords,i,i+deltaIndex, currentLevel, goalLevel);
    }//for
  }//if
}//generator

void fractalGenerator::generateCoords(arma::mat& coords, double x0, double y0, double x1, int goalLevel){
  int endIndex = pow(8,goalLevel);
  coords = arma::zeros(endIndex+1, 2);
  coords(0,0)=x0;
  coords(0,1)=y0;
  coords(endIndex,0)=x1;
  coords(endIndex,1)=y0;
  fractalGenerator::generator(coords,0,endIndex,1,goalLevel);
}
