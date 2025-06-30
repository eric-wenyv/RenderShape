#include "Shape.h"
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "renderUtils.h"
#include "RenderConfig.h"

using namespace std;
int main()
{
    const double center[2] = {static_cast<double>(RenderConfig::width) / 2, static_cast<double>(RenderConfig::height) / 3};
    renderUtils::hide_cursor();
    const std::vector<Dot> cube = Shape::readShape("../shape_edge_points.csv");
    Shape cube_object(cube);

    const auto pre_buffer = new char**[2];
    pre_buffer[0] = renderUtils::createBuffer(RenderConfig::width, RenderConfig::height);
    pre_buffer[1] = renderUtils::createBuffer(RenderConfig::width, RenderConfig::height);

    while (true)
    {
        //清除上一帧
        renderUtils::clear_screen();
        //渲染立方体
        cube_object.render(RenderConfig::camera, center, pre_buffer, RenderConfig::width, RenderConfig::height, RenderConfig::scale_x,RenderConfig::scale_y);
        //控制帧数
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //旋转图形
        cube_object.rotate(RenderConfig::rotate_speed);
    }
}
