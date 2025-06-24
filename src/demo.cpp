#include "Cube.h"
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "renderUtils.h"

constexpr double camera_y[3] = {0.5, 0.5, 8};
constexpr double center[2] = {50, 10};
constexpr double rotate_speed = 0.1;
constexpr int width = 100;
constexpr int height = 30;

using namespace std;
int main()
{
    renderUtils::hide_cursor();
    const std::vector<Dot> cube = Cube::readShape("../cube_edge_points.csv");
    Cube cube_object(cube);

    auto pre_buffer = new char**[2];
    pre_buffer[0] = renderUtils::createBuffer(width, height);
    pre_buffer[1] = renderUtils::createBuffer(width, height);

    while (true)
    {
        //清除上一帧
        renderUtils::clear_screen();
        //渲染立方体
        cube_object.render(camera_y, center, pre_buffer, width, height);
        //控制帧数
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //旋转图形
        cube_object.rotate(rotate_speed);
    }
}
