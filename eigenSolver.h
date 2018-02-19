//eigenSolver.h
#ifndef __eigenSolver_included__
#define __eigenSolver_included__

#include <armadillo>
#include <iostream>
#include <math.h>

namespace eigenSolver{
void getIndexVec(arma::vec& indexVec, arma::mat& mask);
  }//namespace

#endif // #ifndef __eigenSolver_included__
