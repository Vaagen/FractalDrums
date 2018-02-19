run: main.cpp fractalGenerator.cpp eigenSolver.cpp
	g++ -O2 -std=c++11 -o run main.cpp fractalGenerator.cpp eigenSolver.cpp -larmadillo
