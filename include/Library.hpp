#pragma once

#include "Solver.hpp"
#include "Array2D.hpp"

#include <omp.h>
#include <vector>
#include <string>
#include <span>

std::vector<double> data_potential(std::string solver_name, std::span<double> boundary_conditions, std::vector<double> source, const int nod_number, const int iteration, const double precision);



