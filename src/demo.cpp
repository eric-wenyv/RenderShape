#include <algorithm>
#include "Cube.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

constexpr double camera_y[3] = {0.5, 0.5, 4};
constexpr double center[2] = {50, 10};
constexpr double rotate_speed = 0.2;

void clear_screen()
{
    std::cout << "\033[2J\033[H"; // 清屏并移动到左上角
    std::cout.flush();
}
void hide_cursor()
{
    std::cout << "\033[?25l"; // 隐藏光标
    std::cout.flush();
}

using namespace std;
int main()
{
    hide_cursor();
    std::vector<Dot> cube = Cube::readShape("../cube_edge_points.csv");
    Cube cube_object(cube);
    while (true)
    {
        clear_screen();
        cube_object.render(camera_y, center);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        cube_object.rotate(rotate_speed);
    }
}


