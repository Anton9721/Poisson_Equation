#include "Solver.hpp"
#include <cmath>
#include <vector>
#include <span>

void Solver_Jacobi::solve(Array2D<double> &potential_data, std::span<double> boundary_conditions, Array2D<double> source, const int nod_number, const int iteration, const double precision) const
{
    size_t N = nod_number;
    const double h = 1.0 / (N - 1); 

    Array2D<double> u(N, N);  
    Array2D<double> f(N, N); 

    // Граничные условия
    for (size_t i = 0; i < N; ++i) {
        u(i, N - 1) = boundary_conditions[i + N];  // Правая граница
        u(N - 1, i) = boundary_conditions[i + 2 * N];  // Нижняя граница
        u(i, 0) = boundary_conditions[i + 3 * N]; // Левая граница
        u(0, i) = boundary_conditions[i];  // Верхняя граница

    }

    for (size_t i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            f(i, j) = - 4 * std::numbers::pi * source(j, i);
        }
    }

    Array2D<double> u_new(N, N);  
    int iteration_curr = 0;
    double error;

    do {
        error = 0.0;

        for (size_t i = 0; i < N; ++i) {
            u_new(i, 0) = u(i, 0);  
            u_new(i, N - 1) = u(i, N - 1); 
        }
        for (size_t j = 0; j < N; ++j) {
            u_new(0, j) = u(0, j);  
            u_new(N - 1, j) = u(N - 1, j); 
        }

        #pragma omp parallel for collapse(2)
        for (size_t i = 1; i < N - 1; ++i) {
            for (size_t j = 1; j < N - 1; ++j) {
                u_new(i, j) = 0.25 * (u(i + 1, j) + u(i - 1, j) + u(i, j + 1) + u(i, j - 1) - h * h * f(i, j));
            }
        }

        #pragma omp parallel for reduction(max: error)
        for (size_t i = 1; i < N - 1; ++i) {
            for (size_t j = 1; j < N - 1; ++j) {
                error = std::max(error, std::fabs(u_new(i, j) - u(i, j)));
            }
        }

        u = u_new;
        iteration_curr++;

    } while (error > precision || iteration_curr < iteration);

    potential_data = u_new;
    // std::string file_trajectory = "/home/anton/MEPhI/Progs/Poisson_equation/build/data.txt";
    // WriterTXT writer_trajectory(file_trajectory);
    // writer_trajectory.write(u_new, N, N);


};
