#include "eigenSolver.h"

void eigenSolver::getHelmholtzMatrix(arma::sp_mat& sparseA, int N){
  arma::sp_mat sparseT(N-1,N-1);
  sparseT.speye();
  sparseT*=4;

  sparseT(0,1)=-1;
  for(int i=1; i<(sparseT.n_rows-1); i++){
    sparseT(i,i-1)=sparseT(i,i+1)=-1;
  }
  sparseT(sparseT.n_rows-1,sparseT.n_rows-2)=-1;

  arma::sp_mat sparseIdentity(N-1,N-1);
  sparseIdentity.speye();

  sparseA = arma::resize(sparseA,(N-1)*N,(N-1)*N);
  sparseA.rows(0,(N-2)).cols(0,N-2)=sparseT;
  sparseA.rows(0,(N-2)).cols(N-1,2*(N-1)-1)=-sparseIdentity;
  for(int i=1; i<(N-1); i++){
    sparseA.rows(i*(N-1),(i+1)*(N-1)-1).cols((i-1)*(N-1),i*(N-1)-1)=-sparseIdentity;
    sparseA.rows(i*(N-1),(i+1)*(N-1)-1).cols(i*(N-1),(i+1)*(N-1)-1)=sparseT;
    sparseA.rows(i*(N-1),(i+1)*(N-1)-1).cols((i+1)*(N-1),(i+2)*(N-1)-1)=-sparseIdentity;
  }
  sparseA.rows((N-1)*(N-1),N*(N-1)-1).cols((N-2)*(N-1),(N-1)*(N-1)-1)=-sparseIdentity;
  sparseA.rows((N-1)*(N-1),N*(N-1)-1).cols((N-1)*(N-1),N*(N-1)-1)=sparseT;
}
