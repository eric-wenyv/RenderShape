#pragma once
#include "Dot.h"
#include <vector>
#include <string>

class Cube {
private:
    std::vector<Dot> cube;
public:
    explicit Cube(const std::vector<Dot>& cube);
    ~Cube();

    static std::vector<Dot> readShape(const std::string &filename);

    void rotate(double rotate_speed);
    void render(const double camera_y[3], const double center[2], char*** pre_buffer, int width, int height, double scale);
};