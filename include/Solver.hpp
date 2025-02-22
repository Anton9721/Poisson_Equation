#pragma once

#include "Writer.hpp"
#include "Array2D.hpp"
#include <span>
#include <vector>
#include <cmath>
#include <numbers>



class Solver{
public:
    virtual void solve(Array2D<double> &potential_data, std::span<double> boundary_conditions, Array2D<double> source, const int nod_number, const int iteration, const double precision, const double omega) const = 0;
    virtual ~Solver() = default;          

};

//Решение методом Якоби
class Solver_Jacobi : public Solver
{
    public:
        void solve(Array2D<double> &potential_data, std::span<double> boundary_conditions, Array2D<double> source, const int nod_number, const int iteration, const double precision, const double omega) const override;
};

//Решение методом Гаусса Зейделя
class Solver_Gauss : public Solver
{
    public:
        void solve(Array2D<double> &potential_data, std::span<double> boundary_conditions, Array2D<double> source, const int nod_number, const int iteration, const double precision, const double omega) const override;
};

//Решение методом Сверхрелаксации
class Solver_over_relaxation: public Solver
{
    public:
        void solve(Array2D<double> &potential_data, std::span<double> boundary_conditions, Array2D<double> source, const int nod_number, const int iteration, const double precision, const double omega) const override;
};