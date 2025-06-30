#pragma once
#include "Matrix.h"

class Dot
{
private:
    Matrix m_coordinate;
    Matrix m_projection;

private:
    [[nodiscard]] Dot project() const;

public:
    Dot(double x, double y, double z);
    explicit Dot(const Matrix &coordinate);
    Dot &operator=(const Dot &other);
    ~Dot();

    double x() { return m_coordinate.at(0, 0); }
    double y() { return m_coordinate.at(1, 0); }
    double z() { return m_coordinate.at(2, 0); }
    double ex() { return m_coordinate.at(3, 0); }

    void rotate(double angle);

    int* getProjectedCoordinates(const double camera[], const double center[2],int width, int height, double scale_x,double scale_y);
};