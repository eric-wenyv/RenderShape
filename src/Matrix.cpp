#include "Matrix.h"

#include <cmath>
#include <iostream>

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
    // 向量 v1 = dot2 - dot1
    double v1x = dot2.x() - dot1.x();
    double v1y = dot2.y() - dot1.y();
    double v1z = dot2.z() - dot1.z();

    // 向量 v2 = dot3 - dot1
    double v2x = dot3.x() - dot1.x();
    double v2y = dot3.y() - dot1.y();
    double v2z = dot3.z() - dot1.z();

    // 法向量 n = v1 × v2 (叉积)
    double nx = v1y * v2z - v1z * v2y;
    double ny = v1z * v2x - v1x * v2z;
    double nz = v1x * v2y - v1y * v2x;

    const double norm = sqrt(nx*nx + ny*ny + nz*nz);
    // 归一化法向量
    nx /= norm;
    ny /= norm;
    nz /= norm;

    // 计算平面方程的常数项 d = -(nx*x1 + ny*y1 + nz*z1)
    const double d = -(nx * dot1.x() + ny * dot1.y() + nz * dot1.z());

    // 返回平面方程系数 [a, b, c] 对应 ax + by + cz = 1
    Matrix res(1, 3);
    res.at(0, 0) = -nx / d;
    res.at(0, 1) = -ny / d;
    res.at(0, 2) = -nz / d;

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