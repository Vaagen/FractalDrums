run: main.cpp fractalGenerator.cpp eigenSolver.cpp
	g++ -O2 -std=c++11 -o run main.cpp fractalGenerator.cpp eigenSolver.cpp  -L/usr/local/opt/openblas/lib -larmadillo -framework Accelerate

# run: main.cpp fractalGenerator.cpp eigenSolver.cpp
# 	 g++ -O2 -std=c++11 -o run main.cpp fractalGenerator.cpp eigenSolver.cpp  -L/usr/local/opt/openblas/lib -larmadillo  -lopenblas -llapack
# export OPENBLAS_NUM_THREADS=4
