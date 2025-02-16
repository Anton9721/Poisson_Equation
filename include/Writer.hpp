#pragma once
#include <span>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Array2D.hpp"


class Writer
{
public:
    virtual void write(Array2D<double> potential, int rows, int columns) = 0;
    virtual ~Writer() = default;
};


// Вывод в numpy массив
class WriterPyhton
{
public:
    virtual ~WriterPyhton() {}

    std::vector<double> writer_numpy(std::span<double> potential);
};

// Запись в файл txt решения
class WriterTXT : public Writer
{
private:
    std::ofstream file;

public:
    WriterTXT(std::string &filename);
    virtual ~WriterTXT() {}
    void write(Array2D<double> potential, int rows, int columns) override;
};

