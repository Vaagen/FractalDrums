#include "fractalGenerator.h"
#include "eigenSolver.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>


void printTime(double start_s){
  double stop_s=clock();
  std::cout << "    Seconds since start: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << std::endl;
}

int main(int argc, char *argv[]){
  // Starting timer.
  double start_s=clock();
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
  int stepsPerSide = 10;
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
  arma::mat indexMat;
  eigenSolver::getIndexVec_Mat(indexVec, mask, indexMat);

  // Set up sparse matrix A to represent eigensystem.
  arma::sp_mat A(indexVec.n_elem,indexVec.n_elem);
  A.speye();
  A*=4;
  int N = mask.n_cols;
  std::cout << " Value of N: " << N << std::endl;
  int col = 0;
  int index =0;
  for(int row=0; row<A.n_rows; row++){
    index = indexVec(row);
    // If point to the right is inside domain, and not outside outer boarder, assign -1 to right value.
    if(mask.in_range(index+N)){
      if(mask(index+N)){
        A(row,indexMat(index+N))=-1;
      }
    }
    // If point to the left is inside domain, and not outside outer boarder, assign -1 to left value.
    if(mask.in_range(index-N)){
      if(mask(index-N)) {
        A(row,indexMat(index-N))=-1;
      }
    }
    // If point above is inside domain, and not above outer boarder, assign -1 to above value.
    if(mask.in_range(index-1) && (index%N)!= 0 ){
      if(mask(index-1)){
        A(row,indexMat(index-1))=-1;
      }
    }
    // If point under is inside domain, and not below outer boarder, assign -1 to value below.
    if(mask.in_range(index+1) && (index%N)!=(N-1) ){
      if(mask(index+1)) {
        A(row,indexMat(index+1))=-1;
      }
    }
  }
  
  // Don't need the indexVec or indexMat any more.
  indexMat.clear();
  // Need indexvec to save the state in matrix mode later.
  indexVec.save("indexVec.dat", arma::raw_ascii);
  //indexVec.clear();

  // Don't need mask anymore.
  //mask.save("mask_mat.dat", arma::raw_ascii);
  mask.clear();

  // Calculating eigenvalues and vectors.
  int numberOfEigenvalues=10;
  std::cout << " Calculating "<< numberOfEigenvalues << " first eigenvalues and vectors." << std::endl;
  printTime(start_s);
  arma::vec eigval;
  arma::mat eigvec;



  if(!arma::eigs_sym(eigval, eigvec, A, numberOfEigenvalues, "sa")){
    std::cout << " Eigenvectors and values not found." << std::endl;
    printTime(start_s);
    return 0;
  }
  std::cout << " Finished calculating eigenvalues and vectors." << std::endl;
  printTime(start_s);

  // Output eigenstate
  arma::mat state(N,N);
  state.zeros();
  for(int i=0; i<eigvec.col(0).n_elem-1; i++){
    state(indexVec(i))=eigvec(i,9);
  }
  state.save("state.dat", arma::raw_ascii);

  // Saving output.
  eigval.save("eigval.dat", arma::raw_ascii);
  eigvec.save("eigvec.dat", arma::raw_ascii);

  std::ofstream outFile;
  outFile.open(outputFile);
  outFile << coords << std::endl;
  outFile.close();


  return 0;
}
