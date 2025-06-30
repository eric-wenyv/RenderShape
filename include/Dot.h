#pragma once
#include "Matrix.h"
#include <memory>

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

    [[nodiscard]] double x() const{ return m_coordinate.at(0, 0); }
    [[nodiscard]] double y() const{ return m_coordinate.at(1, 0); }
    [[nodiscard]] double z() const{ return m_coordinate.at(2, 0); }
    [[nodiscard]] double ex() const{ return m_coordinate.at(3, 0); }

    void rotate(double angle);

    std::unique_ptr<int[]> getProjectedCoordinates(const double camera[], const double center[2],int width, int height, double scale_x,double scale_y);
};