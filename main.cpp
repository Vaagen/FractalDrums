#include "fractalGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]){
  arma::mat coords;
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
  std::string outputFile = "test.txt";
  if (argc>2){
    outputFile = argv[2];
  }
  // Calculating corners.
  fractalGenerator::generateCoords(coords, -100.0, 2.0, 100.0,goalLevel);
  // Saving output.
  std::ofstream outFile;
  outFile.open(outputFile);
  outFile << coords << std::endl;
  outFile.close();

  return 0;
}
