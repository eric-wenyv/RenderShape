#pragma once
class Dot;

class Matrix
{
private:
    double *array;
    int m;
    int n;

public:
    Matrix(int rows, int cols);
    Matrix(const Matrix &other);
    Matrix(int rows, int cols, const double *array);
    ~Matrix();

    static Matrix getCoefficients(const Dot& dot1, const Dot& dot2, const Dot& dot3, const Dot& dot4);
    static double threeDet(const Matrix &matrix);

    double &at(int row, int col);
    [[nodiscard]] const double &at(int row, int col) const;

    // Matrix operations
    Matrix &operator=(const Matrix &other);
    Matrix operator*(const Matrix &other) const;
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    [[nodiscard]] Matrix transpose() const;

    [[nodiscard]] int rows() const { return m; }
    [[nodiscard]] int cols() const { return n; }
};