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
  int N = goalLevel;
  arma::sp_mat sparseT(N-1,N-1);
  sparseT.speye();
  sparseT*=4;
  //sparseT.print();

  sparseT(0,1)=-1;
  for(int i=1; i<(sparseT.n_rows-1); i++){
    sparseT(i,i-1)=sparseT(i,i+1)=-1;
  }
  sparseT(sparseT.n_rows-1,sparseT.n_rows-2)=-1;
  //sparseT.print();

  arma::sp_mat sparseIdentity(N-1,N-1);
  sparseIdentity.speye();
  //sparseIdentity.print();

  arma::sp_mat sparseA((N-1)*N,(N-1)*N);
  sparseA.rows(0,(N-2)).cols(0,N-2)=sparseT;
  sparseA.rows(0,(N-2)).cols(N-1,2*(N-1)-1)=-sparseIdentity;
  for(int i=1; i<(N-1); i++){
    sparseA.rows(i*(N-1),(i+1)*(N-1)-1).cols((i-1)*(N-1),i*(N-1)-1)=-sparseIdentity;
    sparseA.rows(i*(N-1),(i+1)*(N-1)-1).cols(i*(N-1),(i+1)*(N-1)-1)=sparseT;
    sparseA.rows(i*(N-1),(i+1)*(N-1)-1).cols((i+1)*(N-1),(i+2)*(N-1)-1)=-sparseIdentity;
  }
  sparseA.rows((N-1)*(N-1),N*(N-1)-1).cols((N-2)*(N-1),(N-1)*(N-1)-1)=-sparseIdentity;
  sparseA.rows((N-1)*(N-1),N*(N-1)-1).cols((N-1)*(N-1),N*(N-1)-1)=sparseT;
  //sparseA.print();

  // Now, how to use the grid as a column vector? Note, it's a dense matrix.

  return 0;

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
