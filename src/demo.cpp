#include "Shape.h"
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "renderUtils.h"

//镜头位置
constexpr double camera[3] = {1.0, 1.0, 5.0};
//旋转速度
constexpr double rotate_speed = 0.05;
//buffer大小
constexpr int width = 100;
constexpr int height = 30;
//缩放比例，将立方体的坐标缩放到屏幕上
constexpr int scale_x = 15;
constexpr int scale_y = 7;


using namespace std;
int main()
{
    constexpr double center[2] = {static_cast<double>(width) / 2, static_cast<double>(height) / 3};
    renderUtils::hide_cursor();
    const std::vector<Dot> cube = Shape::readShape("../shape_edge_points.csv");
    Shape cube_object(cube);

    const auto pre_buffer = new char**[2];
    pre_buffer[0] = renderUtils::createBuffer(width, height);
    pre_buffer[1] = renderUtils::createBuffer(width, height);

    while (true)
    {
        //清除上一帧
        renderUtils::clear_screen();
        //渲染立方体
        cube_object.render(camera, center, pre_buffer, width, height, scale_x,scale_y);
        //控制帧数
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //旋转图形
        cube_object.rotate(rotate_speed);
    }
}
