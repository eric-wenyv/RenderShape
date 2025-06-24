#include "Cube.h"
#include <sstream>
#include <array>
#include <fstream>
#include <iostream>

std::vector<Dot> Cube::readShape(const std::string &filename)
{
    std::vector<Dot> dots;
    std::string line;
    std::ifstream file(filename);

    getline(file, line);

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string value;

        int i{0};
        std::array<double, 3> coordinate{};
        while (getline(ss, value, ','))
        {
            coordinate[i++] = stod(value);
        }

        Dot new_dot(coordinate[0], coordinate[1], coordinate[2]);
        dots.push_back(new_dot);
    }

    return dots;
}

Cube::Cube(const std::vector<Dot>& cube)
{
    this->cube = cube;
}

Cube::~Cube()
=default;

void Cube::rotate(const double rotate_speed)
{
    for (auto& dot : cube)
    {
        dot.rotate(rotate_speed);
    }
}

void Cube::render(const double camera_y[3],const double center[2])
{
    constexpr int width = 100;
    constexpr int height = 30;
    // 分配缓冲区
    auto buffer = new char*[height];
    for (int i = 0; i < height; ++i) {
        buffer[i] = new char[width];
        std::fill_n(buffer[i], width, ' ');
    }
    // 渲染所有点到缓冲区
    for (auto& dot : cube)
    {
        dot.render(camera_y, center, buffer, width, height);
    }
    // 输出缓冲区
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << buffer[i][j];
        }
        std::cout << '\n';
    }

    // 释放缓冲区
    for (int i = 0; i < height; ++i) {
        delete[] buffer[i];
    }
    delete[] buffer;
    std::cout.flush();
}