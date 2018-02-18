//eigenSolver.h
#ifndef __eigenSolver_included__
#define __eigenSolver_included__

#include <armadillo>
#include <iostream>
#include <math.h>

namespace eigenSolver{
  void getHelmholtzMatrix(arma::sp_mat& sparseA, int N);
  }//namespace

#endif // #ifndef __eigenSolver_included__