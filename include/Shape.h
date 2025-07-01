#pragma once
#include "Dot.h"
#include <vector>
#include <string>

class Shape {
    std::vector<Dot> cube;

    static void fillSurface(std::array<int, 4> vertices_indexes, std::vector<Dot>& vertices, std::vector<Dot>& dots);
public:
    explicit Shape(const std::vector<Dot>& cube);
    ~Shape();

    static std::vector<Dot> readShape(const std::string &filename);
    static std::vector<Dot> readObj(const std::string &filename);

    void rotate(double rotate_speed) const;
    void render(const double camera_y[3], const double center[2], char*** pre_buffer, int width, int height, double scale_x,double scale_y) const;
};