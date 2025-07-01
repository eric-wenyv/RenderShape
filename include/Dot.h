#pragma once
#include <memory>

class Matrix;

class Dot
{
private:
    std::unique_ptr<Matrix> m_coordinate;
    std::unique_ptr<Matrix> m_projection;

private:
    [[nodiscard]] Dot project() const;

public:
    Dot(double x, double y, double z);
    explicit Dot(const Matrix &coordinate);
    Dot(const Dot& other);  // 添加拷贝构造函数
    Dot &operator=(const Dot &other);
    ~Dot();

    [[nodiscard]] double x() const;
    [[nodiscard]] double y() const;
    [[nodiscard]] double z() const;
    [[nodiscard]] double ex() const;

    void rotate(double angle) const;

    std::unique_ptr<int[]> getProjectedCoordinates(const double camera[], const double center[2],int width, int height, double scale_x,double scale_y) const;
};