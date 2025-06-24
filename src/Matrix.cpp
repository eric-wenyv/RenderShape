#include "Matrix.h"
#include <stdexcept>

Matrix::Matrix(const int rows, const int cols)
{
    this->m = rows;
    this->n = cols;
    this->array = new double[m * n];
    for (int i = 0; i < m * n; ++i)
    {
        this->array[i] = 0.0;
    }
}
Matrix::Matrix(const Matrix &other)
{
    this->m = other.m;
    this->n = other.n;
    this->array = new double[m * n];
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            this->at(i, j) = other.at(i, j);
        }
    }
}
Matrix::~Matrix()
{
    delete[] array;
}
Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        delete[] array;
        this->m = other.m;
        this->n = other.n;
        this->array = new double[m * n];
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                this->at(i, j) = other.at(i, j);
            }
        }
    }
    return *this;
}

double &Matrix::at(int row, int col)
{
    if (row < 0 || row >= this->m || col < 0 || col >= this->n)
    {
        throw std::out_of_range("Index out of range");
    }
    return this->array[row * n + col];
}
const double &Matrix::at(int row, int col) const
{
    if (row < 0 || row >= this->m || col < 0 || col >= this->n)
    {
        throw std::out_of_range("Index out of range");
    }
    return this->array[row * n + col];
}

Matrix Matrix::operator*(const Matrix &other) const
{
    int m = this->rows();
    int n = this->cols();
    if (other.rows() != n)
    {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }
    int k = other.cols();

    Matrix C(m, k);
    for (auto i{0}; i < m; i++)
        for (auto j{0}; j < k; j++)
        {
            for (auto x{0}; x < n; x++)
            {
                C.at(i, j) += this->at(i, x) * other.at(x, j);
            }
        }

    return C;
}

Matrix Matrix::transpose() const
{
    Matrix matrix_T(n, m);

    for (auto i{0}; i < m; i++)
        for (auto j{0}; j < n; j++)
            matrix_T.at(j, i) = this->at(i, j);

    return matrix_T;
}