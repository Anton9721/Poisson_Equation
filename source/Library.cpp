# include "Library.hpp"



std::vector<double> data_potential(std::string solver_name, std::span<double> boundary_conditions, 
                                std::vector<double> source, const int nod_number, 
                                const int iteration, const double precision)
{

    Array2D<double> potential_data(nod_number, nod_number);
    Array2D<double> source2D(nod_number, nod_number);
    std::vector<double> data_result;

    for (size_t i = 0; i < nod_number; ++i){
        for (size_t j = 0; j < nod_number; ++j){
            source2D(i, j) = source[i * nod_number + j];
        }
    }
    // Решение методом Якоби
    if (solver_name == "Solver_Jacobi")
    {
        Solver_Jacobi solver;
        solver.solve(potential_data, boundary_conditions, source2D, nod_number, iteration, precision);
        for (size_t i = 0; i < nod_number; ++i){
            for (size_t j = 0; j < nod_number; ++j){
                data_result.push_back(potential_data(i, j));
            }
        }
    
        return data_result;
    }
}

