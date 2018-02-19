#include "eigenSolver.h"


void eigenSolver::getIndexVec(arma::vec& indexVec, arma::mat& mask){
  // Vector to store index of elements inside domain.
  indexVec = arma::zeros(arma::accu(mask));
  // Insert index of elements inside domain
  int insertedElements=0;
  for(int i=0; i<mask.n_elem; i++){
    if(mask(i)){
      indexVec(insertedElements)=i;
      insertedElements ++;
    }
  }
}

void eigenSolver::getIndexVec_Mat(arma::vec& indexVec, arma::mat& mask, arma::mat& indexMat){
  // Vector to store index of elements inside domain.
  indexVec = arma::zeros(arma::accu(mask));
  indexMat.zeros(mask.n_rows,mask.n_cols);
  indexMat --;
  // Insert index of elements inside domain
  int insertedElements=0;
  for(int i=0; i<mask.n_elem; i++){
    if(mask(i)){
      indexVec(insertedElements)=i;
      indexMat(i)=insertedElements;
      insertedElements ++;
    }
  }
}




//
//
// void eigenSolver::getHelmholtzMatrix(arma::sp_mat& sparseA, int N){
//   arma::sp_mat sparseT(N,N);
//   sparseT.speye();
//   sparseT*=4;
//
//   sparseT(0,1)=-1;
//   for(int i=1; i<(sparseT.n_rows-1); i++){
//     sparseT(i,i-1)=sparseT(i,i+1)=-1;
//   }
//   sparseT(sparseT.n_rows-1,sparseT.n_rows-2)=-1;
//
//   arma::sp_mat sparseIdentity(N,N);
//   sparseIdentity.speye();
//
//   sparseA = arma::resize(sparseA,N*N,N*N);
//   sparseA.rows(0,(N-1)).cols(0,N-1)=sparseT;
//   sparseA.rows(0,(N-1)).cols(N,2*N-1)=-sparseIdentity;
//   for(int i=1; i<(N-1); i++){
//     sparseA.rows(i*N,(i+1)*N-1).cols((i-1)*N,i*N-1)=-sparseIdentity;
//     sparseA.rows(i*N,(i+1)*N-1).cols(i*N,(i+1)*N-1)=sparseT;
//     sparseA.rows(i*N,(i+1)*N-1).cols((i+1)*N,(i+2)*N-1)=-sparseIdentity;
//   }
//   sparseA.rows(N*(N-1),N*N-1).cols(N*(N-2),N*(N-1)-1)=-sparseIdentity;
//   sparseA.rows(N*(N-1),N*N-1).cols(N*(N-1),N*N-1)=sparseT;
// }
//
// void eigenSolver::removeColumns(arma::sp_mat& sparseA, arma::mat& domain){
//   for(int i=0; i<domain.n_elem; i++){
//     if( ! domain(i)){
//       sparseA.col(i).zeros();
//     }
//   }
// }
