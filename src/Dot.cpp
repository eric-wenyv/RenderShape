#include "Matrix.h"
#include "Dot.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

Dot::Dot(const double x, const double y, const double z)
    : m_coordinate(4, 1), m_projection(4, 4)
{
    m_coordinate.at(0, 0) = x;
    m_coordinate.at(1, 0) = y;
    m_coordinate.at(2, 0) = z;
    m_coordinate.at(3, 0) = 1;
}
Dot::Dot(const Matrix &coordinate)
    : m_coordinate(coordinate), m_projection(4, 4)
{
    if (coordinate.rows() != 4 || coordinate.cols() != 1)
    {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }
}
Dot::~Dot()
= default;

Dot &Dot::operator=(const Dot &other)
{
    if (this != &other)
    {
        m_coordinate = other.m_coordinate;
        m_projection = other.m_projection;
    }
    return *this;
}

Dot Dot::project() const
{
    Dot pro_dot(this->m_projection * this->m_coordinate);
    return pro_dot;
}

void Dot::render(const double camera[], const double center[2], char** buffer,
    const int width, const int height, const double scale)
{
    const double cx = camera[0];
    const double cy = camera[1];
    const double cz = camera[2];
    m_projection.at(0, 0) = 1;
    m_projection.at(0, 1) = 0;
    m_projection.at(0, 2) = - cx / cz;
    m_projection.at(0, 3) = 0;

    m_projection.at(1, 0) = 0;
    m_projection.at(1, 1) = 1;
    m_projection.at(1, 2) = - cy / cz;
    m_projection.at(1, 3) = 0;

    m_projection.at(2, 0) = 0;
    m_projection.at(2, 1) = 0;
    m_projection.at(2, 2) = 0;
    m_projection.at(2, 3) = 0;

    m_projection.at(3, 0) = 0;
    m_projection.at(3, 1) = 0;
    m_projection.at(3, 2) = -1 / cz;
    m_projection.at(3, 3) = 1;

    Dot pro_dot = this->project();
    const double x = pro_dot.x() / pro_dot.ex() * scale + center[0];
    const double y = pro_dot.y() / pro_dot.ex() * scale + center[1];
    const int xi = static_cast<int>(x);
    const int yi = static_cast<int>(y);
    if (xi >= 0 && xi < width && yi >= 0 && yi < height)
        buffer[yi][xi] = '*';
}

void Dot::rotate(const double angle)
{
    Matrix m_rotate(4, 4);
    m_rotate.at(0, 0) = cos(angle);
    m_rotate.at(0, 1) = 0;
    m_rotate.at(0, 2) = sin(angle);
    m_rotate.at(0, 3) = 0;

    m_rotate.at(1, 0) = 0;
    m_rotate.at(1, 1) = 1;
    m_rotate.at(1, 2) = 0;
    m_rotate.at(1, 3) = 0;

    m_rotate.at(2, 0) = - sin(angle);
    m_rotate.at(2, 1) = 0;
    m_rotate.at(2, 2) = cos(angle);
    m_rotate.at(2, 3) = 0;

    m_rotate.at(3, 0) = 0;
    m_rotate.at(3, 1) = 0;
    m_rotate.at(3, 2) = 0;
    m_rotate.at(3, 3) = 1;

    m_coordinate = m_rotate * m_coordinate;
}