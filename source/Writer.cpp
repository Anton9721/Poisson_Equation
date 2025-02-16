#include "Writer.hpp"


WriterTXT::WriterTXT(std::string &filename)
{
    file = std::ofstream(filename);
}

void WriterTXT::write(Array2D<double> potential, int rows, int columns)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j){
            file << potential(i, j) << " ";
        }
        file << "\n";
    }
}

