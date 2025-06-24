#pragma once

class Matrix
{
private:
    double *array;
    int m;
    int n;

public:
    Matrix(int rows, int cols);
    Matrix(const Matrix &other);
    Matrix &operator=(const Matrix &other);
    ~Matrix();

    double &at(int row, int col);
    [[nodiscard]] const double &at(int row, int col) const;

    // Matrix operations
    Matrix operator*(const Matrix &other) const;
    [[nodiscard]] Matrix transpose() const;

    [[nodiscard]] int rows() const { return m; }
    [[nodiscard]] int cols() const { return n; }
};