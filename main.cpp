#include "fractalGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]){
  // Getting goalLevel.
  int goalLevel;
  if (argc <2){
    std::cout << "You have to supply a goal level." << std::endl;
    return 0;
  }
  std::istringstream ss(argv[1]);
  if (!(ss >> goalLevel)){
    std::cerr << "Invalid number " << argv[1] << '\n';
  }
  // Getting output file name.
  std::string outputFile = "test.txt";
  if (argc>2){
    outputFile = argv[2];
  }
  // Getting rotated
  bool rotate=false;
  if (argc>3){
    std::istringstream ss(argv[3]);
    if (!(ss >> rotate)){
      std::cerr << "Invalid number " << argv[3] << '\n';
    }
  }
  // Calculating corners.
  arma::mat coords;
  arma::mat mask;
  int stepsPerSide = 8;

  if(rotate){
    // To test rotated system
    fractalGenerator::generateSquareCoords(coords, stepsPerSide*sqrt(2.0)*(pow(4.0,goalLevel)), goalLevel, true);
    fractalGenerator::generateMask(mask,coords, stepsPerSide, goalLevel, true);
  }else if (!rotate){
    // To test non-rotated system
    fractalGenerator::generateSquareCoords(coords, stepsPerSide*(pow(4.0,goalLevel)), goalLevel, false);
    fractalGenerator::generateMask(mask,coords, stepsPerSide, goalLevel, false);
  }

  includeBoundary(mask);


  // Saving output.
  std::ofstream outFile;
  outFile.open(outputFile);
  outFile << coords << std::endl;
  outFile.close();

  mask.save("A_mat.dat", arma::raw_ascii);

  return 0;
}
