#include "fractalGenerator.h"
#include "eigenSolver.h"
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
  int stepsPerSide = 4;

  if(rotate){
    // To test rotated system
    fractalGenerator::generateSquareCoords(coords, stepsPerSide*sqrt(2.0)*(pow(4.0,goalLevel)), goalLevel, true);
    fractalGenerator::generateMask(mask,coords, stepsPerSide, goalLevel, true);
  }else if (!rotate){
    // To test non-rotated system
    fractalGenerator::generateSquareCoords(coords, stepsPerSide*(pow(4.0,goalLevel)), goalLevel, false);
    fractalGenerator::generateMask(mask,coords, stepsPerSide, goalLevel, false);
  }

  // Vector to store index of elements inside domain.
  arma::vec indexVec;
  int insertedElements=0;
  eigenSolver::getIndexVec(indexVec, mask);

  // Set up sparse matrix A to represent eigensystem.
  arma::sp_mat A(indexVec.n_elem,indexVec.n_elem);
  A.speye();
  A*=4;
  int N = mask.n_cols;
  int col = 0;
  int index =0;
  for(int row=0; row<A.n_rows; row++){
    index = indexVec(row);
    // If point to the right is inside domain, and not on right side, and row<N*N, assign -1 to left value.
    if(row<(N*N-1)){
      if(mask(index+1) && (index%N)!=N-1 ){
        A(row,row+1)=-1;
      }
    }
    // If point to the left is inside domain, and not on left side, and row>0, assign -1 to left value.
    if(row >0){
      if(mask(index-1) && (index%N) ) {
        A(row,row-1)=-1;
      }
    }
  }
  A.print();


  // Saving output.
  std::ofstream outFile;
  outFile.open(outputFile);
  outFile << coords << std::endl;
  outFile.close();

  mask.save("A_mat.dat", arma::raw_ascii);

  return 0;
}
