#include "Shape.h"
#include <algorithm>
#include <sstream>
#include <array>
#include <fstream>
#include <iostream>
#include <cmath>
#include "RenderConfig.h"

std::vector<Dot> Shape::readShape(const std::string &filename)
{
    std::vector<Dot> dots;
    std::string line;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return dots; // 返回空向量
    }
    //跳过第一行标题
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

Shape::Shape(const std::vector<Dot>& cube)
{
    this->cube = cube;
}

Shape::~Shape()
=default;

void Shape::rotate(const double rotate_speed)
{
    for (auto& dot : cube)
    {
        dot.rotate(rotate_speed);
    }
}

void Shape::render(const double camera[3],const double center[2], char*** pre_buffer
    , const int width, const int height, const double scale_x,const double scale_y)
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

    //获得投影坐标及距离
    std::unique_ptr<int[]> pro_dot_tmp = nullptr;
    double distance = 0.0;
    auto* pro_dots_with_distance = new std::pair<std::unique_ptr<int[]>, double>[cube.size()];
    for (size_t i = 0; i < cube.size(); ++i)
    {
        pro_dot_tmp = cube[i].getProjectedCoordinates(camera, center, width, height, scale_x,scale_y);
        distance = RenderConfig::getDistanceToCamera(cube[i] ,camera);
        if (pro_dot_tmp != nullptr)
        {
            pro_dots_with_distance[i] = {std::move(pro_dot_tmp), distance};
        }
        else
        {
            pro_dots_with_distance[i] = {nullptr, 0.0};
        }
    }

    // 按照距离排序
    std::sort(pro_dots_with_distance, pro_dots_with_distance + cube.size(),
        [](const std::pair<std::unique_ptr<int[]>, double>& a, const std::pair<std::unique_ptr<int[]>, double>& b) {
        return a.second > b.second;
    });

    //归一化处理
    for (size_t i = 0; i < cube.size(); ++i)
    {
        constexpr double max_possible_distance = 10;
        constexpr double min_possible_distance = 0;
        double normalized_distance = (pro_dots_with_distance[i].second - min_possible_distance) /
                                    (max_possible_distance - min_possible_distance);

        normalized_distance = std::max(0.0, std::min(1.0, normalized_distance));
        pro_dots_with_distance[i].second = normalized_distance;
    }

    //写入缓冲区
    for (size_t i = 0; i < cube.size(); ++i)
    {
        auto& pro_dot = pro_dots_with_distance[i].first;
        if (pro_dot != nullptr)
        {
            const int xi = pro_dot[0];
            const int yi = pro_dot[1];
            if (xi >= 0 && xi < width && yi >= 0 && yi < height)
            {
                pre_buffer[next_index][yi][xi] = RenderConfig::getSymbol(pro_dots_with_distance[i].second);
            }
        }
    }
    delete[] pro_dots_with_distance;

    buffer_index = next_index;
    std::cout.flush();
}