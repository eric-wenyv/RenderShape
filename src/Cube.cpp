#include "Cube.h"
#include <sstream>
#include <array>
#include <fstream>
#include <iostream>
#include "renderUtils.h"

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

void Cube::render(const double camera_y[3],const double center[2], char*** pre_buffer, const int width, const int height)
{
    static int buffer_index = 0;
    int next_index = 1 - buffer_index;

    // 输出当前缓冲区
    std::string screen;
    screen.reserve(width * height + height);
    for (int i = 0; i < height; ++i) {
        screen.append(pre_buffer[buffer_index][i], width);
        screen.push_back('\n');
    }
    std::cout << screen;

    // 清空下一缓冲区
    for (int i = 0; i < height; ++i) {
        std::fill_n(pre_buffer[next_index][i], width, ' ');
    }

    for (auto& dot : cube)
    {
        dot.render(camera_y, center, pre_buffer[next_index], width, height);
    }

    buffer_index = next_index;
    std::cout.flush();
}