//eigenSolver.h
#ifndef __eigenSolver_included__
#define __eigenSolver_included__

#include <armadillo>
#include <iostream>
#include <math.h>

namespace eigenSolver{
void getIndexVec(arma::vec& indexVec, arma::mat& mask);
void getIndexVec_Mat(arma::vec& indexVec, arma::mat& mask, arma::mat&indexMat);
  }//namespace

#endif // #ifndef __eigenSolver_included__
