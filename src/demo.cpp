#include "Cube.h"
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "renderUtils.h"

//镜头位置
constexpr double camera_y[3] = {0.5, 0.5, 8};
//旋转速度
constexpr double rotate_speed = 0.1;
//buffer大小
constexpr int width = 100;
constexpr int height = 30;
//缩放比例，将立方体的坐标缩放到屏幕上
constexpr int scale = 10;


using namespace std;
int main()
{
    constexpr double center[2] = {static_cast<double>(width) / 2, static_cast<double>(height) / 3};
    renderUtils::hide_cursor();
    const std::vector<Dot> cube = Cube::readShape("../cube_edge_points.csv");
    Cube cube_object(cube);

    const auto pre_buffer = new char**[2];
    pre_buffer[0] = renderUtils::createBuffer(width, height);
    pre_buffer[1] = renderUtils::createBuffer(width, height);

    while (true)
    {
        //清除上一帧
        renderUtils::clear_screen();
        //渲染立方体
        cube_object.render(camera_y, center, pre_buffer, width, height, scale);
        //控制帧数
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //旋转图形
        cube_object.rotate(rotate_speed);
    }
}
