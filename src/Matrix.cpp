#include "Matrix.h"
#include "Dot.h"
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
Matrix::Matrix(const int rows, const int cols, const double *array)
{
    this->m = rows;
    this->n = cols;
    this->array = new double[m * n];
    for (int i = 0; i < m * n; ++i)
    {
        this->array[i] = array[i];
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

double Matrix::threeDet(const Matrix &matrix)
{
    if (matrix.rows() != 3 || matrix.cols() != 3)
    {
        throw std::invalid_argument("Matrix must be 3x3 for determinant calculation");
    }
    return matrix.at(0, 0) * (matrix.at(1, 1) * matrix.at(2, 2) - matrix.at(1, 2) * matrix.at(2, 1)) -
           matrix.at(0, 1) * (matrix.at(1, 0) * matrix.at(2, 2) - matrix.at(1, 2) * matrix.at(2, 0)) +
           matrix.at(0, 2) * (matrix.at(1, 0) * matrix.at(2, 1) - matrix.at(1, 1) * matrix.at(2, 0));
}

Matrix Matrix::getCoefficients(const Dot& dot1, const Dot& dot2, const Dot& dot3, const Dot& dot4)
{
    //行列式计算方法
    Matrix res(1,3);
    Matrix matrix(3, 3);
    matrix.at(0, 0) = dot1.x();
    matrix.at(0, 1) = dot1.y();
    matrix.at(0, 2) = dot1.z();
    matrix.at(1, 0) = dot2.x();
    matrix.at(1, 1) = dot2.y();
    matrix.at(1, 2) = dot2.z();
    matrix.at(2, 0) = dot3.x();
    matrix.at(2, 1) = dot3.y();
    matrix.at(2, 2) = dot3.z();
    const double detA = threeDet(matrix);
    Matrix matrix1 = matrix;
    matrix1.at(0, 0) = 1.0;
    matrix1.at(0, 1) = 1.0;
    matrix1.at(0, 2) = 1.0;
    const double detX1 = threeDet(matrix1);
    Matrix matrix2 = matrix;
    matrix2.at(1, 0) = 1.0;
    matrix2.at(1, 1) = 1.0;
    matrix2.at(1, 2) = 1.0;
    const double detX2 = threeDet(matrix2);
    Matrix matrix3 = matrix;
    matrix3.at(2, 0) = 1.0;
    matrix3.at(2, 1) = 1.0;
    matrix3.at(2, 2) = 1.0;
    const double detX3 = threeDet(matrix3);

    res.at(0, 0) = detX1 / detA;
    res.at(0, 1) = detX2 / detA;
    res.at(0, 2) = detX3 / detA;

    return res;
}


bool Matrix::operator==(const Matrix& other) const
{
    if (m != other.m || n != other.n)   return false;
    for (int i = 0; i < m * n; ++i)
    {
        if (this->array[i] != other.array[i])
        {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
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