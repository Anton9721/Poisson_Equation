#pragma once

#include <iostream>
#include <vector>
#include <span>
#include <iomanip>  
#include <omp.h>

template <typename T>
class Array2D
{
private:
    size_t rows;
    size_t cols;
    std::vector<T> data;

public:
    Array2D(size_t r, size_t c) : rows(r), cols(c), data(r * c)
    {
        for (size_t i = 0; i < rows * cols; ++i)
        {
            data[i] = 0;
        }
    }

    T &operator()(size_t r, size_t c)
    {
        return data[r * cols + c];
    }

    friend std::ostream &operator<<(std::ostream &os, Array2D<T> &matrix)
    {
        #pragma omp parallel for
        for (size_t i = 0; i < matrix.rows; ++i)
        {
            for (size_t j = 0; j < matrix.cols; ++j)
            {
                os << std::setw(10) << matrix(i, j) << " ";
            }
            os << std::endl;
        }
        return os;
    }
    

    
    Array2D<T> operator+(Array2D<T> &other)
    {
        Array2D<T> result(rows, cols);
        for (size_t i = 0; i < rows * cols; ++i)
        {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    Array2D<T> operator-(Array2D<T> &other)
    {
        Array2D<T> result(rows, cols);
        for (size_t i = 0; i < rows * cols; ++i)
        {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    friend Array2D<T> operator*(const T &scalar, Array2D<T> &matrix)
    {
        Array2D<T> result(matrix.rows, matrix.cols);
        #pragma omp parallel for
        for (size_t i = 0; i < matrix.rows; ++i)
        {
            for (size_t j = 0; j < matrix.cols; ++j)
            {
                result.data[i * matrix.cols + j] = scalar * matrix.data[i * matrix.cols + j];
            }
        }
        return result;
    }

    friend Array2D<T> operator*(Array2D<T> &matrix, const T &scalar)
    {
        return scalar * matrix;
    }

    Array2D<T> operator*(Array2D<T> &other)
    {
        Array2D<T> result(rows, other.cols);

        #pragma omp parallel for
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < other.cols; ++j)
            {
                result(i, j) = 0;
                for (size_t k = 0; k < cols; ++k)
                {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    std::span<T> get_span() { return std::span<T>(data); }

    size_t get_rows() const { return rows; }
    size_t get_cols() const { return cols; }
};
