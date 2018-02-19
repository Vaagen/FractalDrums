#include "fractalGenerator.h"
#include "eigenSolver.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>


void printTime(int start_s){
  int stop_s=clock();
  std::cout << "    Seconds since start: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << std::endl;
}

int main(int argc, char *argv[]){
  // Starting timer.
  int start_s=clock();
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

  std::cout << " Calculating corners, with " << stepsPerSide << " steps per side." << std::endl;
  printTime(start_s);
  if(rotate){
    // To test rotated system
    fractalGenerator::generateSquareCoords(coords, stepsPerSide*sqrt(2.0)*(pow(4.0,goalLevel)), goalLevel, true);
    fractalGenerator::generateMask(mask,coords, stepsPerSide, goalLevel, true);
  }else if (!rotate){
    // To test non-rotated system
    fractalGenerator::generateSquareCoords(coords, stepsPerSide*(pow(4.0,goalLevel)), goalLevel, false);
    fractalGenerator::generateMask(mask,coords, stepsPerSide, goalLevel, false);
  }

  std::cout << " Setting up sparse matrix." << std::endl;
  printTime(start_s);
  // Vector to store index of elements inside domain.
  arma::vec indexVec;
  int insertedElements=0;
  arma::mat indexMat;
  eigenSolver::getIndexVec_Mat(indexVec, mask, indexMat);

  // Set up sparse matrix A to represent eigensystem.
  arma::sp_mat A(indexVec.n_elem,indexVec.n_elem);
  A.speye();
  A*=4;
  int N = mask.n_cols;
  int col = 0;
  int index =0;
  for(int row=0; row<A.n_rows; row++){
    index = indexVec(row);
    // If point to the right is inside domain, assign -1 to right value.
    if(mask.in_range(index+N)){
      if(mask(index+N)){
        A(row,indexMat(index+N))=-1;
      }
    }
    // If point to the left is inside domain, assign -1 to left value.
    if(mask.in_range(index-N)){
      if(mask(index-N)) {
        A(row,indexMat(index-N))=-1;
      }
    }
    // If point above is inside domain, assign -1 to above value.
    if(mask.in_range(index-1)){
      if(mask(index-1)){
        A(row,indexMat(index-1))=-1;
      }
    }
    // If point under is inside domain, assign -1 to value below.
    if(mask.in_range(index+1)){
      if(mask(index+1)) {
        A(row,indexMat(index+1))=-1;
      }
    }
  }

  // Calculating eigenvalues and vectors.
  int numberOfEigenvalues=10;
  std::cout << " Calculating "<< numberOfEigenvalues << " first eigenvalues and vectors." << std::endl;
  printTime(start_s);
  arma::cx_vec eigval;
  arma::cx_mat eigvec;

  arma::eigs_gen(eigval, eigvec, A, numberOfEigenvalues, "sm");
  std::cout << " Finished calculating eigenvalues and vectors." << std::endl;
  printTime(start_s);

  // Saving output.
  eigval.save("eigval.dat", arma::raw_ascii);
  eigvec.save("eigvec.dat", arma::raw_ascii);

  std::ofstream outFile;
  outFile.open(outputFile);
  outFile << coords << std::endl;
  outFile.close();

  mask.save("A_mat.dat", arma::raw_ascii);

  return 0;
}
