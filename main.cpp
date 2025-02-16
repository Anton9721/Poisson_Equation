#include "Solver.hpp"

#include <omp.h>

int main()
{
    // double pi = std::numbers::pi;
    int N = 50;
    std::vector<double> boundary_conditions(4*N, 0.0);
    Array2D<double> source(N, N);
    int iteration = 1000;
    double presision = 0.001;

    Solver_Jacobi solver;
    Array2D<double> data_potential(N, N);
    
    for (int i = 0; i < N; ++i)
    {
        if (i < N){
            boundary_conditions[i] += 1;
        }
    }

    solver.solve(data_potential, boundary_conditions, source, N, iteration, presision);




    return 0;
}