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
  // Calculating corners.
  arma::mat coords;
  fractalGenerator::generateSquareCoords(coords, 100, goalLevel, false);
  // Saving output.
  std::ofstream outFile;
  outFile.open(outputFile);
  outFile << coords << std::endl;
  outFile.close();

  return 0;
}
