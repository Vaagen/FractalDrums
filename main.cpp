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

  // Test making of sparse matrices needed.
  int N = 7;
  arma::sp_mat testSparse(N,N);
  testSparse.speye();
  testSparse*=4;
  testSparse.print();

  testSparse(0,1)=-1;
  for(int i=1; i<(testSparse.n_rows-1); i++){
    std::cout << i << testSparse.n_rows << std::endl;
    testSparse(i,i-1)=testSparse(i,i+1)=-1;
  }
  testSparse(testSparse.n_rows-1,testSparse.n_rows-2)=-1;
  testSparse.print();

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
