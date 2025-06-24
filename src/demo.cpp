#include <algorithm>
#include "Dot.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <array>
#include <chrono>
#include <thread>

constexpr double camera_y[3] = {0.5, 0.5, 4};
constexpr double center[2] = {50, 10};
constexpr double rotate_speed = 0.2;

void clear_screen();
void render_frame(std::vector<Dot>& cube);
void rotate(std::vector<Dot>& cube);
std::vector<Dot> readShape(const std::string &filename);
void hide_cursor();

using namespace std;
int main()
{
    hide_cursor();
    std::vector<Dot> cube = readShape("../cube_edge_points.csv");
    while (true)
    {
        clear_screen();
        render_frame(cube);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        rotate(cube);
    }
    return 0;
}

void clear_screen()
{
    std::cout << "\033[2J\033[H"; // 清屏并移动到左上角
    std::cout.flush();
}

void render_frame(std::vector<Dot>& cube)
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

void rotate(std::vector<Dot>& cube)
{
    for (auto& dot : cube)
    {
        dot.rotate(rotate_speed);
    }
}

std::vector<Dot> readShape(const std::string &filename)
{
    std::vector<Dot> dots;
    string line;
    ifstream file(filename);

    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string value;

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

void hide_cursor()
{
    std::cout << "\033[?25l"; // 隐藏光标
    std::cout.flush();
}
