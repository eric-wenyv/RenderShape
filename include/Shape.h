#pragma once
#include "Dot.h"
#include <vector>
#include <string>

class Shape {
private:
    std::vector<Dot> cube;
public:
    explicit Shape(const std::vector<Dot>& cube);
    ~Shape();

    static std::vector<Dot> readShape(const std::string &filename);

    void rotate(double rotate_speed);
    void render(const double camera_y[3], const double center[2], char*** pre_buffer, int width, int height, double scale_x,double scale_y);
};