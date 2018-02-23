

eigvec = load('eigvec.dat');
indexVec = load('indexVec.dat');
N=input('N = ');

stateArray = cell(1,size(eigvec,2));
state = zeros(N,N);

for eigenVecNumber = 1:size(eigvec,2)
  for i = 1:size(eigvec,1)
    [l,m] = ind2sub(size(state),indexVec(i));
    state(l,m)=eigvec(i,eigenVecNumber);
  end
  stateArray{eigenVecNumber} = state;

  figure(eigenVecNumber);
  contour3(stateArray{eigenVecNumber},100);
end
